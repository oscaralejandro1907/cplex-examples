//
//  Solution.hpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 15/11/21.
//

#ifndef Solution_hpp
#define Solution_hpp

#include "Header.h"
#include "TSP.hpp"

class Solution: public list<long> {
private:
    TSP *_data;
    double _fitness;
    
public:
    Solution(TSP *I);
    
    Solution(Solution *S);//Constructor when receiving a Solution
    
    TSP *getData() {return _data;}
    double getFitness() {return _fitness;}
    
    double calculateFitness();
    bool isFeasible();
    
    void printSolution();
};

#endif /* Solution_hpp */
