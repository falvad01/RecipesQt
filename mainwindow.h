#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Recipe.h>
#include <QMainWindow>
#include <iostream>
#include<QGridLayout>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void paintWindow(Ui::MainWindow *ui,QGridLayout *lay,QJsonObject jsonObject);
    QJsonObject readJsonFile();
    vector <string> getStepsList(QJsonObject jsonObject,QString recipe);
    vector <Ingredient> getIngredients(QJsonObject jsonObject,QString recipe);

    void showlist(list<string> g);


signals:
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_actionShoping_list_triggered();

private:
    vector<Recipe> recipes;
    Ui::MainWindow *ui;
    QGridLayout *lay;
    void showErroMessage(QString error);
};
#endif // MAINWINDOW_H
