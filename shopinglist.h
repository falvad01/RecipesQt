#ifndef SHOPINGLIST_H
#define SHOPINGLIST_H

#include <QWidget>
#include<Recipe.h>

namespace Ui {
class ShopingList;
}

class ShopingList : public QWidget
{
    Q_OBJECT

public:
    explicit ShopingList(vector<Recipe> recipes,QWidget *parent = nullptr);
    ~ShopingList();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ShopingList *ui;

    vector<Recipe> recipes;

    void printIngredients();
};

#endif // SHOPINGLIST_H
