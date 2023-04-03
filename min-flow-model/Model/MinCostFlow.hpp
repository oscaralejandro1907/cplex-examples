//
//  MinCostFlow.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 16/01/21.
//

#ifndef MinCostFlow_hpp
#define MinCostFlow_hpp

#include "Header.h"

//Based on ilolpex3.cpp, example of adding constraints to solve a problem.

//  The idea is to solve the simple problem first, and then add the
//  constraints for the complicating constraints, and solve with dual.
//  CPLEX can re-optimize and re-use any information available from previous optimizations.

class InstanceFlow {
    int _nnodes;
    vector <int> _costs;
    
    
public:
    InstanceFlow();
    
    int getnodes(){return _nnodes;}
    vector<int> getCosts(){return _costs;}
};

class CplexFlow {
    IloEnv _env;    //Enviroment
    
    IloModel _IP;   //Model
    IloCplex _cplexIP;  //Solver
    IloObjective _objIP;    //Objective
    IloNumVarArray _x; //Variable
    IloRangeArray _Constraints; //Constraints
    
public:
    CplexFlow(InstanceFlow *data);
    
    void solve();
};

#endif /* MinCostFlow_hpp */
