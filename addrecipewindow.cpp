#include "addrecipewindow.h"
#include "ui_addrecipewindow.h"


#include <QMessageBox>
#include <iostream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <fstream>
#include <json.hpp>
#include <iomanip>

#include <Ingredient.h>
#include <Recipe.h>
using namespace std;
using json = nlohmann::json;


AddRecipeWindow::AddRecipeWindow(vector<Recipe> allRecipes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRecipeWindow)
{
    ui->setupUi(this);
    lay = new QGridLayout();
    lay2 = new QVBoxLayout();
    pos = 0;
    pos2 = 1;
    this->recipeToEdit = Recipe();
    isEditing = false;
    this->allRecipes = allRecipes;
}

AddRecipeWindow::AddRecipeWindow(Recipe recipeToEdit,vector<Recipe> allRecipes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRecipeWindow)
{
    this->recipeToEdit = recipeToEdit;
    ui->setupUi(this);
    lay = new QGridLayout();
    lay2 = new QVBoxLayout();

    isEditing = true;
    this->allRecipes = allRecipes;
    ingredinetArray = this->recipeToEdit.getIngredients();
    stepsArray = this->recipeToEdit.getSteps();
    pos = ingredinetArray.size();
    pos2 = stepsArray.size()+1;


    for(unsigned long i = 0; i < recipeToEdit.getIngredients().size(); i++){

        Ingredient ing = recipeToEdit.getIngredients()[i];

        QLabel *index = new QLabel(QString::number(i+1));
        QLabel *ingredientName = new QLabel(QString::fromStdString(ing.getName()));
        QLabel *ingredienAmount = new QLabel(QString::number(ing.getQuantity()));
        QLabel *ingredientUnit = new QLabel(QString::fromStdString(ing.getUnit()));

        lay->addWidget(index,i,0);
        lay->addWidget(ingredientName,i,1);
        lay->addWidget(ingredienAmount,i,2);
        lay->addWidget(ingredientUnit,i,3);


    }
    ui->ingredientsScroll->setLayout(lay);

    for(unsigned long i = 0; i < recipeToEdit.getSteps().size();i++){


        QLabel *ingredientName = new QLabel(QString::number(i+1)+"-" +QString::fromStdString(recipeToEdit.getSteps()[i]));

        lay2->addWidget(ingredientName,i);

    }
    ui->stepsScroll->setLayout(lay2);


    ui->recipeName->setText(QString::fromStdString(recipeToEdit.getName()));
    ui->recipeName->setDisabled(true);
}

AddRecipeWindow::~AddRecipeWindow()
{
    delete ui;
}


/**
 * @brief AddRecipeWindow::on_pushButton_2_clicked
 *
 * Add ingredients handler
 */
void AddRecipeWindow::on_pushButton_2_clicked()
{


    QString ingName = ui->ingreName->text();
    QString ingValue = ui->ingreAmount->text();
    QString ingUnit = ui->ingreUnit->text();

    if(ingName == "" || ingUnit == "" || ingValue == ""){

        showErroMessage("FIELD EMPTY");

    }else{




        float value = ingValue.toFloat();

        if(value <= 0){
            showErroMessage("VALUE CANT BE 0(OR LESS) OR A WORD");
        }else{

            QLabel *num = new QLabel(QString::number(pos+1) + "-");
            QLabel *nameLabel = new QLabel(ingName);
            QLabel *amountLabel = new QLabel(QString::number(value));

            QLabel *unitLabel = new QLabel(ingUnit);

            lay->addWidget(num,pos,0);

            lay->addWidget(nameLabel,pos,1);
            lay->addWidget(amountLabel,pos,2);

            lay->addWidget(unitLabel,pos,3);

            ui->ingredientsScrollContents->setLayout(lay);
            /**
              stepsScrollContents
              */

            pos++;

            Ingredient ing (ingName.toStdString(),value,ingUnit.toStdString());
            ingredinetArray.push_back(ing);




        }
    }
}

void AddRecipeWindow::on_pushButton_clicked()
{

    QString stepQ = ui->step->text();

    if(stepQ == ""){
        showErroMessage("FIELD EMPTY");
    }else{

        QLabel *stepLabel = new QLabel( QString::number(pos2) +"-" +stepQ);

        lay2->addWidget(stepLabel);

        ui->stepsScrollContents->setLayout(lay2);
        pos2++;
        stepsArray.push_back(stepQ.toStdString());

        cout<<endl;

    }


}
/**
 * @brief AddRecipeWindow::on_pushButton_3_clicked
 *
 *
 * Confirm button
 */
void AddRecipeWindow::on_pushButton_3_clicked()
{
    QString nameQ = ui->recipeName->text();


    if(isEditing){

        deleteRecipe(nameQ.toStdString());
        addRecipeToFile();
        this->close();
    }else{

        if(nameQ == "" || ingredinetArray.size() == 0 || stepsArray.size() == 0){
            showErroMessage("FIELD EMPTY");
        }else{
            bool recipeExixt = true;
            for(unsigned long i = 0; i < allRecipes.size(); i++){

                if(allRecipes[i].getName() == nameQ.toStdString()){
                    recipeExixt = true;
                }else{
                    recipeExixt = false;
                }

            }

            if(recipeExixt){
                showErroMessage("THE RECIPE ALREADY EXIST");
            }else{
                addRecipeToFile();

                this->close();

            }//else
        }//else
    }
}

/**
 * @brief AddRecipeWindow::addRecipeToFile
 *
 * Add the recipe to the file
 */
void AddRecipeWindow::addRecipeToFile(){

    QString nameQ = ui->recipeName->text();


    std::ifstream file("../lab1/recipes.json");
    json fullJson;
    file >> fullJson;

    json steps;
    Recipe newRecipe (nameQ.toStdString(),ingredinetArray,stepsArray,0);
    fullJson[nameQ.toStdString()]["recipe"] = stepsArray;

    for(unsigned long i = 0; i < this->ingredinetArray.size(); i++){

        json ingredient;
        QString amountAndUnit;
        amountAndUnit.append(QString::number(this->ingredinetArray[i].getQuantity()));
        amountAndUnit.append(" ");
        amountAndUnit.append(QString::fromStdString(this->ingredinetArray[i].getUnit()));//Creating the QString

        fullJson[nameQ.toStdString()][this->ingredinetArray[i].getName()] = amountAndUnit.toStdString();

    }


    ofstream o("../lab1/recipes.json");
    o << setw(3) << fullJson << endl;

}

/**
 * @brief AddRecipeWindow::deleteRecipe
 * @param recipeName
 *
 * Delete a recipe
 */
void AddRecipeWindow::deleteRecipe(string recipeName){
    //The best way to delete in a json is geting the data inside it, delenting with the key(int this case the recipe) and write it again

    QFile file("../lab1/recipes.json");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    QJsonObject jsonObject = doc.object();

    jsonObject.remove(QString::fromStdString(recipeName));

    doc = QJsonDocument(jsonObject);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}


/**
 * @brief AddRecipeWindow::on_deleteIngredientBtn_clicked
 *
 * Delete last ingredient
 */
void AddRecipeWindow::on_deleteIngredientBtn_clicked()
{

    ingredinetArray.pop_back();

    this->pos = ingredinetArray.size();


    QList<QLabel *> labels = ui->ingredientsScroll->findChildren<QLabel *>();

    cout<<labels.size()<<endl;

    delete labels.at(labels.size()-1);
    delete labels.at(labels.size()-2);
    delete labels.at(labels.size()-3);
    delete labels.at(labels.size()-4);




}
/**
 * @brief AddRecipeWindow::on_deleteStepBtn_clicked
 *
 * Delete last step
 */
void AddRecipeWindow::on_deleteStepBtn_clicked()
{

    stepsArray.pop_back();

    this->pos2 = stepsArray.size()+1;

    QList<QLabel *> labels = ui->stepsScroll->findChildren<QLabel *>();

    delete labels.at(labels.size()-1);


}

/**
 * @brief AddRecipeWindow::showErroMessage
 * @param error
 *
 * Displaying an error message
 */
void AddRecipeWindow::showErroMessage(QString error)
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("ERROR");
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

}

void AddRecipeWindow::on_pushButton_4_clicked()
{
    this->close();
}
