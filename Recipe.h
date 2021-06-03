#ifndef RECIPE_H
#define RECIPE_H

#include<Ingredient.h>

#include<iostream>
#include <list>
#include <vector>
using namespace std;

class Recipe
{
private:
    string name;
    vector<Ingredient> ingredients;
    vector<string> steps;
    int positionJson;

public:
    Recipe(string name,vector<Ingredient> ingredients,vector<string> steps,int positionJson);
    Recipe(Recipe const &c);
    Recipe();


    string getName() const;
    void setName(const string &value);
    vector<Ingredient> getIngredients() const;
    void setIngredients(const vector<Ingredient> &value);
    vector<string> getSteps() const;
    void setSteps(const vector<string> &value);
    string toString();
    int getPositionJson() const;
    void setPositionJson(int value);
};

#endif // RECIPE_H
