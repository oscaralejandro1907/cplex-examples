//
//  Glasses.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 29/11/21.
//

#ifndef Glasses_hpp
#define Glasses_hpp

#include "Header.h"

class CplexGlasses {
    IloEnv _env;    //Enviroment
    IloModel _model;   //Model
    IloCplex _cplex;  //Solver
    IloObjective _obj;    //Objective
    IloNumVarArray _x; //Variable
    IloRangeArray _Constraints; //Constraints
    
public:
    CplexGlasses();
    
    void solve();
    void print();
    
};

#endif /* Glasses_hpp */
