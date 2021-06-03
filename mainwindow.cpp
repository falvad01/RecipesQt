#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>

#include <iostream>
#include <fstream>
#include <QString>
#include <QFile>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QPainter>


#include <Recipe.h>
#include <addrecipewindow.h>
#include <shopinglist.h>


using namespace std;


/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);










    lay = new QGridLayout(this);


    QJsonObject jsonObject = readJsonFile();

    paintWindow(ui,lay,jsonObject);

}


/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::paintWindow
 * @param ui
 * @param lay
 * @param jsonObject
 */
void MainWindow::paintWindow(Ui::MainWindow *ui,QGridLayout *lay,QJsonObject jsonObject){

    QStringList recipesList = jsonObject.keys();

    for (int i = 0;i < jsonObject.size() ;i++ ) {

        QString element=recipesList.at(i);

        Recipe recipe(element.toStdString(),getIngredients(jsonObject,element),getStepsList(jsonObject,element),i);


        recipes.push_back(recipe);

        QLabel *label = new QLabel(element);
        //   QRadioButton *radio = new QRadioButton();
        QCheckBox *check = new QCheckBox();


        lay->addWidget(label,i+1,0);
        //lay->addWidget(radio,i+1,1);
        lay->addWidget(check,i+1,2);

    }

    ui->scrollContent->setLayout(lay);

    cout<<recipes.size()<<endl;
}


/**
 * @brief MainWindow::readJsonFile
 * @return
 */
QJsonObject MainWindow::readJsonFile()
{
    qDebug() << "Read Json File:";


    //Open Qfile and transform it to a byte array(parsing the errors)
    QFile file;
    file.setFileName("../lab1/recipes.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";

    }
    QByteArray byteArray;
    byteArray = file.readAll();
    file.close(); //close the file


    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();

    }

    //Puting the byte array content into a QJsonObjest to work with it
    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();


    QTextStream textStream(stdout);

    return jsonObj;
}


/**
 * @brief MainWindow::getIngredients
 * @param jsonObject
 * @param recipe
 * @return
 *
 * The ingredients are childres of the recipe name(exception the children "recipe". it is the key for the steps)
 */

vector <Ingredient> MainWindow::getIngredients(QJsonObject jsonObject,QString recipe){


    QJsonValue jsonVal;
    QJsonObject jsonItemObj;
    QJsonValue quantityAndUnitJson;


    jsonVal = jsonObject.value(recipe);
    jsonItemObj = jsonVal.toObject();
    QStringList ingredientsNames = jsonItemObj.keys(); //geting ingredients

    vector<Ingredient> ingredientsList;

    for (int i = 0; i < ingredientsNames.size() ;i++ ) {


        if(ingredientsNames.at(i).toStdString() != "recipe"){ //discarting recipe key

            quantityAndUnitJson = jsonItemObj[ingredientsNames.at(i)];


            string quantityAndUnit = quantityAndUnitJson.toString().toStdString(); //separating the filds and creating the Ingredient object

            float quantity = QString::fromStdString(quantityAndUnit.substr(0, quantityAndUnit.find(" "))).toFloat();
            string unit = quantityAndUnit.substr(2, quantityAndUnit.find(" "));

            size_t pos = 0;
            string token;
            while ((pos = quantityAndUnit.find(" ")) != std::string::npos) {
                token = quantityAndUnit.substr(0, pos);

                quantityAndUnit.erase(0, pos + string(" ").length());
            }



            Ingredient ingredient(ingredientsNames.at(i).toStdString(),quantity,quantityAndUnit);

            ingredientsList.push_back(ingredient);

        }
    }

    return ingredientsList;

}

/**
 * @brief MainWindow::getStepsList
 * @param jsonObject
 * @param recipe
 * @return
 *
 * Steps are the children of the children recipe, so i only need to find the key recipe and all his childrens.
 */
vector <string> MainWindow::getStepsList(QJsonObject jsonObject,QString recipe){

    QJsonValue jsonVal;
    QJsonObject jsonItemObj;
    QJsonValue jsonSubVal;

    jsonVal = jsonObject.value(recipe);
    jsonItemObj = jsonVal.toObject();

    jsonSubVal = jsonItemObj["recipe"]; //geting childrens of recipe
    QJsonArray steps = jsonSubVal.toArray();


    vector<string> stepsList;
    for(int i = 0; i < steps.size(); i++){

        QString as =steps.at(i).toString();
        stepsList.push_back(as.toStdString());



    }

    return stepsList;


}
/**
 * @brief MainWindow::on_pushButton_clicked
 *   Handler of the edit button
 */
void MainWindow::on_pushButton_clicked()
{

    QList<QCheckBox *> chekedBoxes = ui->mainScroll->findChildren<QCheckBox *>();


    int numCheked = 0;

    int indexToEdit;
    for (int i = 0;i < chekedBoxes.size() ;i++ ) {

        if(chekedBoxes[i]->isChecked()){
            numCheked++;
            indexToEdit = i;
        }
    }

    //The user can only edit one recipe at the same time, so i put some if to chek
    if(numCheked == 0){


          showErroMessage("NOT RECIPE SELECTED");



    }else if(numCheked > 1){


        showErroMessage("YOU CAN ONLY SELECT A RECIPE TO EDIT");



    }else{
        Recipe recipeToEdit = recipes[indexToEdit];

        AddRecipeWindow *add = new AddRecipeWindow(recipeToEdit,recipes);

        add->show();
    }
}

/**
 * @brief MainWindow::on_pushButton_3_clicked
 *
 * Handler of the delete button
 */
void MainWindow::on_pushButton_3_clicked()
{
    QList<QCheckBox *> chekedBoxes = ui->mainScroll->findChildren<QCheckBox *>();
    QList<QLabel *> labels = ui->mainScroll->findChildren<QLabel *>();

    int numCheked = 0;
    for (int i = 0;i < chekedBoxes.size() ;i++ ) {

        if(chekedBoxes[i]->isChecked()){
            numCheked++;

        }
    }

    if(numCheked == 0){

        showErroMessage("NOT RECIPE(S) SELECTED");

    }else{


        //The best way to delete in a json is geting the data inside it, delenting with the key(int this case the recipe) and write it again

        QFile file("../lab1/recipes.json");
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        file.close();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        QJsonObject jsonObject = doc.object();


        for (int i = 0;i < chekedBoxes.size() ;i++ ) {


            if(chekedBoxes[i]->isChecked()){

                Recipe recipeToDelete = recipes[i];

                cout<<recipeToDelete.getName()<<endl;

                jsonObject.remove(QString::fromStdString(recipeToDelete.getName()));

                doc = QJsonDocument(jsonObject);
                file.open(QIODevice::WriteOnly);
                file.write(doc.toJson());
                file.close();

                delete chekedBoxes.at(i);
                delete labels.at(i);

            }
        }






    }


}



/**
 * @brief MainWindow::on_pushButton_2_clicked
 *
 * Add recipe handler
 */
void MainWindow::on_pushButton_2_clicked()
{

    AddRecipeWindow *add = new AddRecipeWindow(recipes);

    add->show();

}
/**
 * @brief MainWindow::on_actionShoping_list_triggered
 *
 * Create the shoping list
 */
void MainWindow::on_actionShoping_list_triggered()
{

    QList<QCheckBox *> chekedBoxes = ui->mainScroll->findChildren<QCheckBox *>();

    int numCheked = 0;
    for (int i = 0;i < chekedBoxes.size() ;i++ ) {

        if(chekedBoxes[i]->isChecked()){
            numCheked++;

        }
    }

    if(numCheked == 0){

        showErroMessage("NOT RECIPE(S) SELECTED");

    }else{

        vector<Recipe> recipesToBuy;
        for (int i = 0;i < chekedBoxes.size() ;i++ ) {


            if(chekedBoxes[i]->isChecked()){

                recipesToBuy.push_back(recipes[i]);
            }

        }
        ShopingList *shop = new ShopingList(recipesToBuy);
        shop->show();

    }



}


void MainWindow::showErroMessage(QString error)
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("ERROR");
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

}
