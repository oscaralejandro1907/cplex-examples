#pragma once
#include "Solver.h"


class CPSolver : public Solver{
    IloEnv _env;
    IloCP _cp;
    IloModel _model;
    IloObjective _obj;
    
    IloIntervalVarArray _t; //for Tasks

    void solvemethod(Solution* S);

public:
    CPSolver(Instance* I);
    ~CPSolver();

    double gap() { return _cp.getObjGap(); }
    void print();

    Solution* recoversolution();
};

