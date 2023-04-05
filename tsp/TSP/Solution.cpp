//
//  Solution.cpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 15/11/21.
//

#include "Solution.hpp"

Solution::Solution(TSP *I) : list<long>(){
    _data=I;
    _fitness=INFINITY;
}

Solution::Solution(Solution *S):list<long>(){
    _data=S->getData();
    _fitness=S->getFitness();
}

double Solution::calculateFitness(){
    _fitness=_data->distanceTo(front(), back());
    
    long i=front();
    for (auto j : *this) {
        _fitness+=_data->distanceTo(i, j);
        i=j;
    }
    
    return _fitness;
}

bool Solution::isFeasible(){
    
    if (size()!=_data->getnnodes()) {
        return false;
    }
    
    for (int i=0; i<_data->getnnodes(); i++) {
        if (find(begin(), end(), i)==end()) {
            return false;
        }
    }
    
    return true;
}

void Solution::printSolution(){
    cout<<setw(15)<<_fitness<<setw(15)<<": ";
    
    for (auto i:*this) {
        cout<<setw(5)<<i;
    } cout<<endl;
}
