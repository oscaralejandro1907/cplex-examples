#pragma once
#include "Solver.h"


class CPSolver : public Solver{
    IloEnv _env;
    IloCP _cp;
    IloModel _model;
    IloObjective _obj;
    
    IloIntVar _Belgium;
    IloIntVar _Denmark;
    IloIntVar _France;
    IloIntVar _Germany;
    IloIntVar _Luxembourg;
    IloIntVar _Netherlands;

    void solvemethod(Solution* S);

public:
    CPSolver(Instance* I);
    ~CPSolver();

    double gap() { return _cp.getObjGap(); }

    Solution* recoversolution();
};

