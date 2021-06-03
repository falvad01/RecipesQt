#include "shopinglist.h"
#include "ui_shopinglist.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

ShopingList::ShopingList(vector<Recipe> recipes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopingList)
{
    this->recipes = recipes;
    ui->setupUi(this);

    QGridLayout *lay= new QGridLayout();


    for(unsigned int i = 0; i< recipes.size(); i++){

        QLabel *recipeName = new QLabel(QString::fromStdString(recipes[i].getName()));
        QSpinBox *number = new QSpinBox();
        number->setMinimum(1);

        lay->addWidget(recipeName,i,0);
        lay->addWidget(number,i,1);


    }

    ui->selectedRecipes->setLayout(lay);
}


void ShopingList::printIngredients(){

}

ShopingList::~ShopingList()
{
    delete ui;
}
/**
 * @brief ShopingList::on_pushButton_2_clicked
 *
 * Cancel handler
 */
void ShopingList::on_pushButton_2_clicked()
{
    this->close();
}

/**
 * @brief ShopingList::on_pushButton_clicked
 *
 * Create list handler
 */
void ShopingList::on_pushButton_clicked()
{

    QList<QSpinBox *> spined = ui->selectedRecipes->findChildren<QSpinBox *>();
    vector<Ingredient> ingredients;

    for(int i = 0; i < spined.size();i++){


        for(int j = 0; j < spined[i]->value(); j++){

            for(unsigned long k = 0; k< recipes[i].getIngredients().size();k++){
                ingredients.push_back(recipes[i].getIngredients()[k]);

            }


        }
    }


    for(unsigned long i = 0; i < ingredients.size(); i++){

        cout<<ingredients[i].toString()<<endl;

    }


    vector<Ingredient> ingredientsAssemble;
    int pocho=0;
    for(unsigned long i = 0; i < ingredients.size(); i++){

        if(ingredientsAssemble.empty()){
            ingredientsAssemble.push_back(ingredients[0]);

        }else{

            bool flag = true;
            for(unsigned long j = 0; j < ingredientsAssemble.size(); j++){

                if(ingredients[i].equals(ingredientsAssemble[j])){
                    ingredientsAssemble[j].addQuantity(ingredients[i].getQuantity());
                    flag = false;

                }
            }
            if(flag){

                ingredientsAssemble.push_back(ingredients[i]);
                pocho++;

            }
        }
    }

    QString shopList;
    for(unsigned long i = 0; i < ingredientsAssemble.size(); i++){


        shopList.append(QString::fromStdString(ingredientsAssemble[i].toString()));
        shopList.append("\n");


    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("ERROR");
    msgBox.setText(shopList);
    msgBox.setStandardButtons(QMessageBox::Ok);

    QPushButton* myButton = new QPushButton("Ok");
    msgBox.addButton(myButton ,QMessageBox::AcceptRole);
    msgBox.exec();



}
