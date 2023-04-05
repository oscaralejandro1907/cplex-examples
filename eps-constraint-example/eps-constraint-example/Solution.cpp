//
//  Solution.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#include "Solution.hpp"

Solution::Solution(Instance *I)
{
    _I = I;
    //TODO
}

Solution::Solution(Solution *S){
    copy(S);
}

Solution::~Solution()
{
    //TODO
}

void Solution::addProductAmount(int p){
    _product_amounts.push_back(p);
}

int Solution::fitness(ObjType obj){
    int fitness = 0;
    
    assert(_product_amounts.size()==2);
    
    if (obj == ObjType::Benefit) {
        fitness = 2*_product_amounts[0] + 5*_product_amounts[1];
    } else {
        fitness = _product_amounts[0] + _product_amounts[1];
    }
    
    return fitness;
}

void Solution::print(){
    cout << "Benefit: " << fitness(ObjType::Benefit) << endl;
    cout << "Production: "<< fitness(ObjType::Production) << endl;
    
    cout << "Values of the products: " << endl;
    
    for (auto p: _product_amounts) {
        cout<< p << " ";
    } cout << endl;
    
}

void Solution::copy(Solution *S){
    assert(S != NULL);
    
    for (int p=0; p<_product_amounts.size(); p++) {
        _product_amounts[p] = S->_product_amounts[p];
    }
}
