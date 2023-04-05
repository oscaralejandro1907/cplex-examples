#pragma once
#include "Solver.h"


class CPSolver : public Solver{
    IloEnv _env;
    IloCP _cp;
    IloModel _model;
    IloObjective _obj;
    
    IloIntervalVarArray2 _m;
    IloIntExprArray _ends;

    void solvemethod(Solution* S);

public:
    CPSolver(Instance* I);
    ~CPSolver();

    double gap() { return _cp.getObjGap(); }

    Solution* recoversolution();
};

