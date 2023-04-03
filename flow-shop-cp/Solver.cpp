#include "Solver.h"

Solver::Solver(Instance* I, string name)
{
	_I = I;
	_name = name;
	_start=_end= chrono::system_clock::now();
	_timlim = 60;
	_mingap = 0.01;
}

void Solver::setparam(param_t PARAM, double value)
{
	if (PARAM == TimLim) _timlim = value;
	else if (PARAM == Gap) _mingap = value;
}

void Solver::solve(Solution* S)
{
	startTimer();

	solvemethod(S);

	stopTimer();
}
