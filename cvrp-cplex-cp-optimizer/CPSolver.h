#pragma once
#include "Solver.h"


class CPSolver : public Solver{
    IloEnv _env;
    IloCP _cp;
    IloModel _model;
    IloObjective _obj;
    
    IloIntervalVarArray _operations;    //The visits
    IloIntervalVarArray2 _opalternatives;   //The alternatives of vehicles to perform the visits
    
    IloTransitionDistance _M;           //Distance matrix
    
    IloIntervalSequenceVarArray _R;     //Sequence of a route
    IloIntervalVarArray _routespans;    //Span of a route
    

    void solvemethod(Solution* S);

public:
    CPSolver(Instance* I);
    ~CPSolver();

    double gap() { return _cp.getObjGap(); }

    Solution* recoversolution();
};

