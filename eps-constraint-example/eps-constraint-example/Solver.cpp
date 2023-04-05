//
//  Solver.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#include "Solver.hpp"

Solver::Solver(Instance *I, string name, ObjType obj){
    _I = I;
    _name = name;
    _objtype = obj;
}

Solver::~Solver()
{
    
}

void Solver::solve(Solution *S){
    solvemethod(S);
}
