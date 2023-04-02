//
//  Instance.cpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#include "Instance.hpp"

Instance::Instance(){
    
    _nIngredients=4;
    _nNutrients=4;
    _nTypesAnimals=3;
    
    _costs = {0.2, 0.12, 0.24, 0.12};       //costs of ingredients
    _demands = {12000, 8000, 9000};         //demand of products for each type of animal (in kg)
    _capacities = {9000, 12000, 5000, 6000};        //availability of ingredients (in kg)
    
    _contents = {{8,10,6,8},
                {6,5,10,6},
                {10,12,6,6},
                {4,8,6,9}};
    
    _lb = { {6,6,4},
            {6,6,6},
            {7,6,6},
            {4,4,4} };
    
    _ub = { {IloInfinity,IloInfinity,6},
            {IloInfinity,IloInfinity,IloInfinity},
            {IloInfinity,IloInfinity,IloInfinity},
            {8,6,5} };
    
}
