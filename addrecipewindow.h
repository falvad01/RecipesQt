#ifndef ADDRECIPEWINDOW_H
#define ADDRECIPEWINDOW_H

#include <QWidget>

#include <QGridLayout>
#include <Ingredient.h>

#include<Recipe.h>

namespace Ui {
class AddRecipeWindow;
}

class AddRecipeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddRecipeWindow(vector<Recipe> allRecipes,QWidget *parent = nullptr);
    explicit AddRecipeWindow(Recipe recipeToEdit,vector<Recipe> allRecipes,QWidget *parent = nullptr);

    ~AddRecipeWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_deleteIngredientBtn_clicked();

    void on_deleteStepBtn_clicked();

    void on_pushButton_4_clicked();

private:

    bool isEditing;
    QGridLayout *lay;
    QBoxLayout *lay2;

    Ui::AddRecipeWindow *ui;

    int pos;
    int pos2;
    string name;
    vector<Ingredient> ingredinetArray;
    vector<string> stepsArray;
    Recipe recipeToEdit;
    vector<Recipe> allRecipes;
    void deleteRecipe(string recipeName);
    void showErroMessage(QString error);
    void addRecipeToFile();

};

#endif // ADDRECIPEWINDOW_H
