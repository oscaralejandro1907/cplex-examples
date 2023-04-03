#include "CPSolver.h"

void CPSolver::solvemethod(Solution* S)
{
	_cp.setParameter(IloCP::TimeLimit, _timlim);
	_cp.setParameter(IloCP::FailLimit, IloIntMax);
	_cp.setParameter(IloCP::Workers, 1);
	_cp.setParameter(IloCP::SearchType, IloCP::Restart);
	_cp.solve();
    
    print();
    
}

CPSolver::CPSolver(Instance* I) : Solver(I,"CPSolver"){
	//TODO
    _I = I;
    
    _model=IloModel(_env);
    _cp=IloCP(_model);
    
    //Variables t
    _t=IloIntervalVarArray(_env);   //An array of interval variables for each task
    for (int i=0; i<_I->getnTasks();i++ ) {
        string label="t_"+to_string(i)+_I->getTask(i)->getTaskName();
        _t.add(IloIntervalVar (_env,_I->getTask(i)->getDuration(),label.c_str())); //The lengths will be durations
    }
    
    //Precedence (Temporal) Constraints
    for (int task=0; task<_I->getnTasks(); task++) {
        for (auto prec:_I->getTask(task)->getPrecedingTasks()) {
            _model.add(IloEndBeforeStart(_env, _t[prec], _t[task]));
        }
    }
    
    //Export model
    _cp.exportModel("ModelBasicHouse.cpo");
}

CPSolver::~CPSolver(){
	//TODO
}


void CPSolver::print(){
    if (_cp.solve()) {
        for (int i=0; i<_I->getnTasks(); i++) {
            _cp.out() << _cp.domain(_t[i]) << endl;
        }
    }
}


Solution* CPSolver::recoversolution()
{
	//TODO
    
	return nullptr;
}
