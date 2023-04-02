//
//  Instance.hpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#ifndef Instance_hpp
#define Instance_hpp

#include "Header.h"

class Instance {
private:
    int _nIngredients;
    int _nNutrients;
    int _nTypesAnimals;
    
    vector<double> _costs;
    vector<int> _demands;
    vector<int> _capacities;
    
    vector<vector<int>> _contents;
    
    vector<vector<int>> _lb;
    vector<vector<float>> _ub;
    
public:
    Instance();
    ~Instance();
    
    int getNingredients() {return _nIngredients;}
    int getNnutrients() {return _nNutrients;}
    int getNTypesOfAnimals() {return _nTypesAnimals;}
    
    vector<double> getCosts() {return _costs;}
    vector<int> getDemands() {return _demands;}
    vector<int> getCapacities() {return _capacities;}
    vector<vector<int>> getContents() {return _contents;}
    vector<vector<int>> getLB() {return _lb;}
    vector<vector<float>> getUB() {return _ub;}
    
};

#endif /* Instance_hpp */
