#include "CPSolver.h"

void CPSolver::solvemethod(Solution* S)
{
	_cp.setParameter(IloCP::TimeLimit, _timlim);
	_cp.setParameter(IloCP::FailLimit, IloIntMax);
	_cp.setParameter(IloCP::Workers, 1);
	_cp.setParameter(IloCP::SearchType, IloCP::Restart);
	_cp.solve();
    
    const char* colours[] = {"blue", "red", "yellow", "green"};
    
    if (_cp.solve()) {
        _cp.out() << "Solution Status: " << _cp.getStatus() << endl;
        
        _env.out() << "Belgium:     "<<colours[_cp.getValue(_Belgium)]<<endl;
        _env.out() << "Denmark:     "<<colours[_cp.getValue(_Denmark)]<<endl;
        _env.out() << "France:      "<<colours[_cp.getValue(_France)]<<endl;
        _env.out() << "Germany:     "<<colours[_cp.getValue(_Germany)]<<endl;
        _env.out() << "Luxembourg:  "<<colours[_cp.getValue(_Luxembourg)]<<endl;
        _env.out() << "Netherlands: "<<colours[_cp.getValue(_Netherlands)]<<endl;
    }
    
    
    
}

CPSolver::CPSolver(Instance* I) : Solver(I,"CPSolver"){
	//TODO
    _model=IloModel(_env);
    _cp=IloCP(_model);
    
    //Variables will be integer from 0 to 3
    //because one value for each color
    //Initializing variables
    
    _Belgium = IloIntVar(_env, 0, 3, "B");
    _Denmark = IloIntVar(_env, 0, 3, "DK");
    _France = IloIntVar(_env, 0, 3, "F");
    _Germany = IloIntVar(_env, 0, 3, "D");
    _Luxembourg = IloIntVar(_env, 0, 3, "L");
    _Netherlands = IloIntVar(_env, 0, 3, "NE");

    
    //Border Countries Constraints
    _model.add(_Belgium != _France);
    _model.add(_Belgium != _Germany);
    _model.add(_Belgium != _Netherlands);
    
    _model.add(_Denmark != _Germany);
    
    _model.add(_France != _Germany);
    _model.add(_France != _Luxembourg);
    
    _model.add(_Germany != _Luxembourg);
    _model.add(_Germany != _Netherlands);
    
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
