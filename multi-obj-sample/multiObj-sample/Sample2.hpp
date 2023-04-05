//
//  Sample2.hpp
//  multiObj-sample
//
//  Created by Oscar Alejandro Hernández López on 24/06/22.
//

#ifndef Sample2_hpp
#define Sample2_hpp

#include "Header.h"

class Sample2{
private:
    IloEnv _env;
    IloModel _model;
    IloCplex _cplex;
    
    //IloObjective _totalcost;
    //IloObjective _co2emission;
    
    IloNumVarArray  _x;
    
    IloRangeArray _Constraints;
    
public:
    Sample2();
    ~Sample2(){}
    
};

#endif /* Sample2_hpp */
