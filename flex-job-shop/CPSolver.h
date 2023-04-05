#pragma once
#include "Solver.h"


class CPSolver : public Solver{
    IloEnv _env;
    IloCP _cp;
    IloModel _model;
    IloObjective _obj;
    
    IloIntervalVarArray _operations;
    IloIntervalVarArray2 _opalts;
    
    IloIntExprArray _ends;

    void solvemethod(Solution* S);

public:
    CPSolver(Instance* I);
    ~CPSolver();

    void initModel();
    double gap() { return _cp.getObjGap(); }

    Solution* recoversolution();
};

