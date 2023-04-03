#include "MILPSolver.h"

void MILPSolver::solvemethod(Solution* S)
{
	_cplex.setParam(IloCplex::TiLim, _timlim);
	_cplex.setParam(IloCplex::EpGap, _mingap);
	_cplex.setParam(IloCplex::Threads, 1);
	_cplex.solve();
}

MILPSolver::MILPSolver(Instance* I) : Solver(I,"MILPSolver")
{
	//TODO
}

MILPSolver::~MILPSolver()
{
	//TODO
}

Solution* MILPSolver::recoversolution()
{
	//TODO
	return nullptr;
}
