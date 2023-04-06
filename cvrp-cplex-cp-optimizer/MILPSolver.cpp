#include "MILPSolver.h"

void MILPSolver::solvemethod(Solution* S)
{
	//_cplex.setParam(IloCplex::TiLim, _timlim);
	//_cplex.setParam(IloCplex::EpGap, _mingap);
	//_cplex.setParam(IloCplex::Threads, 1);
	//_cplex.solve();
}

MILPSolver::MILPSolver(Instance* I) : Solver(I,"MILPSolver")
{
	//TODO: MILP Model
    try{
        _model = IloModel(_env);
        _cplex=IloCplex(_model);
        _obj = IloAdd(_model, IloMinimize(_env, 0) );
           
        _Constraints=IloRangeArray(_env);

        _cplex.exportModel("Model.lp");

       }
       catch (IloException& e) {
           cout << e << endl;
           exit(1000);
       }
    
}

MILPSolver::~MILPSolver(){
	//TODO: Nothing to add - No pointers created
}

Solution* MILPSolver::recoversolution()
{
	//TODO
	return nullptr;
}
