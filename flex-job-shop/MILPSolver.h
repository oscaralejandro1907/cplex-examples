#pragma once
#include "Solver.h"

class MILPSolver : public Solver{
    IloEnv _env;
    IloCplex _cplex;
    IloModel _model;
    IloObjective _obj;

    void solvemethod(Solution* S);

public:

    MILPSolver(Instance* I);
    ~MILPSolver();

    double gap() { return _cplex.getMIPRelativeGap(); }

    Solution* recoversolution();
};

