#ifndef INGREDIENT_H
#define INGREDIENT_H
#include<iostream>
using namespace std;
class Ingredient
{

private:
    string name;
    float quantity;
    string unit;
public:



    Ingredient(string name,float quantity,string unit);
    Ingredient(Ingredient const &c);


    string getName() const;
    void setName(const string &value);
    float getQuantity() const;
    void setQuantity(float value);
    string getUnit() const;
    void setUnit(const string &value);
    void addQuantity(float quantityToAdd);
    string toString();
    bool equals(Ingredient ing);


};
#endif // INGREDIENT_H
