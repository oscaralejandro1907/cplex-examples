#include "CPSolver.h"

void CPSolver::solvemethod(Solution* S)
{
	_cp.setParameter(IloCP::TimeLimit, _timlim);
	_cp.setParameter(IloCP::FailLimit, IloIntMax);
	_cp.setParameter(IloCP::Workers, 1);
	_cp.setParameter(IloCP::SearchType, IloCP::Restart);
	_cp.solve();
    
    if (_cp.solve()) {
        _cp.out() << "Makespan \t: " << _cp.getObjValue() << endl;
    }
    
    for (int i=0; i<_I->getNmachines(); i++) {
        for (int j=0; j<_m[i].getSize(); j++) {
            _cp.out() << _cp.domain(_m[i][j]) << " ";
        } cout <<endl;
    }
    
}

CPSolver::CPSolver(Instance* I) : Solver(I,"CPSolver"){
	//TODO
    _model=IloModel(_env);
    _cp=IloCP(_model);
    
    //Initializing variables
    _m = IloIntervalVarArray2(_env,_I->getNmachines());
    for (int i=0; i<_I->getNmachines(); i++) {
        _m[i]=IloIntervalVarArray(_env);
    }
    
    _ends = IloIntExprArray(_env);
    
    //Adding Values to variables _m
    for (int j=0; j<_I->getNjobs(); j++) {
        IloIntervalVar precedent;
        for (auto op:*_I->getJob(j)) {
            IloIntervalVar pt(_env,op->getprocessingtime());
            _m[op->getmachineid()].add(pt);
            if (0 != precedent.getImpl()) { //getImpl() returns a pointer to the implementation object of the invoking handle.
                _model.add(IloEndBeforeStart(_env, precedent, pt)); //  Precedence Constraint
            }
            precedent=pt;
        }
        _ends.add(IloEndOf(precedent));
    }
    //No Overlap and Same Sequence Constraints
    _seqs = IloIntervalSequenceVarArray(_env,_I->getNmachines());
    for (int i=0; i<_I->getNmachines(); i++) {
        _seqs[i] = IloIntervalSequenceVar(_env,_m[i]);
        _model.add(IloNoOverlap(_env,_seqs[i]));
        if (i>0) {
            _model.add(IloSameSequence(_env, _seqs[0], _seqs[i]));
        }
    }
    
    /* OBJECTIVE */
    IloNumExpr makespan(_env);
    makespan = IloMax(_ends);   //IloMax returns the max of numeric values
    
    _obj = IloMinimize(_env,makespan);
    _model.add(_obj);
    
}

CPSolver::~CPSolver()
{
	//TODO
}

Solution* CPSolver::recoversolution()
{
	//TODO
	return nullptr;
}
