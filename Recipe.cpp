#include "Recipe.h"



string Recipe::getName() const
{
    return name;
}

void Recipe::setName(const string &value)
{
    name = value;
}

vector<Ingredient> Recipe::getIngredients() const
{
    return ingredients;
}

void Recipe::setIngredients(const vector<Ingredient> &value)
{
    ingredients = value;
}

vector<string> Recipe::getSteps() const
{
    return steps;
}

void Recipe::setSteps(const vector<string> &value)
{
    steps = value;
}

int Recipe::getPositionJson() const
{
    return positionJson;
}

void Recipe::setPositionJson(int value)
{
    positionJson = value;
}

Recipe::Recipe(string name, vector<Ingredient> ingredients, vector<string> steps,int positionJson)
{
    this->setName(name);
    this->setIngredients(ingredients);
    this->setSteps(steps);
    this->setPositionJson(positionJson);
}

Recipe::Recipe(const Recipe &c)
{
    this->name = c.getName();
    this->ingredients = c.getIngredients();
    this->steps = c.getSteps();
    this->positionJson = c.getPositionJson();
}

Recipe::Recipe()
{

}


string Recipe::toString(){




    return this->getName() + ":  " + getIngredients()[1].getName()+  " " + getSteps()[1] + " " + to_string(getPositionJson());
}

