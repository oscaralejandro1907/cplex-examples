#pragma once
#include "Solver.h"

class MILPSolver : public Solver{
    
    void solvemethod(Solution* S);
    
    IloEnv _env;
    IloCplex _cplex;
    IloModel _model;
    IloObjective _obj;
    
    IloArray< IloArray< IloNumVarArray > > _Y;
    IloArray < IloNumVarArray > _U;
        
    IloRangeArray _Constraints;

public:

    MILPSolver(Instance* I);
    ~MILPSolver();

    Solution* recoversolution();
};

