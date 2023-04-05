//
//  Sample1.hpp
//  multiObj-samples
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#ifndef Sample1_hpp
#define Sample1_hpp

#include "Header.h"

class Sample1{
private:
    IloEnv _env;
    IloModel _model;
    IloCplex _cplex;
    
    IloObjective _objf1;
    IloObjective _objf2;
    
    IloNumVarArray  _x;
    
    IloRangeArray _Constraints;
    
public:
    Sample1();
    ~Sample1(){}
    
};


#endif /* CPLEX_hpp */
