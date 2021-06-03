#include "Ingredient.h"



Ingredient::Ingredient(string name,float quantity,string unit)
{
    this->setName(name);
    this->setQuantity(quantity);
    this->setUnit(unit);
}

Ingredient::Ingredient(Ingredient const &c){

    this->name = c.getName();
    this->quantity = c.getQuantity();
    this->unit = c.getUnit();
}

string Ingredient::getName() const
{
    return name;
}

void Ingredient::setName(const string &value)
{
    name = value;
}

float Ingredient::getQuantity() const
{
    return quantity;
}

void Ingredient::setQuantity(float value)
{
    quantity = value;
}

string Ingredient::getUnit() const
{
    return unit;
}

void Ingredient::setUnit(const string &value)
{
    unit = value;
}



void Ingredient::addQuantity(float quantityToAdd){


    this->setQuantity(this->getQuantity() + quantityToAdd);
}

string Ingredient::toString(){

    return this->getName() + ": " + to_string(this->getQuantity()) + " " + this->getUnit();
}

bool Ingredient::equals(Ingredient ing){

    bool ret;
    if(this->getName() == ing.getName() && this->getUnit() == ing.getUnit()){
        ret = true;
    }else{
        ret = false;
    }

    return ret;
}



