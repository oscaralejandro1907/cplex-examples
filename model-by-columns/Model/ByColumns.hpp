//
//  ByColumns.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/03/21.
//

#ifndef ByColumns_hpp
#define ByColumns_hpp

#include <stdio.h>
#include "Header.h"

/*
 https://www.tu-chemnitz.de/mathematik/discrete/manuals/cplex/doc/getstart/html/ilocplex13.html
*/

class CplexbyCols {
    IloEnv _env; //Enviroment
    IloModel _model; //Model
    IloCplex _cplex; //Solver
    IloObjective _obj; //Objective
    IloRangeArray _Constraints; //Constraints
    IloNumVarArray _x; //Variables
    
public:
    CplexbyCols();
};

#endif /* ByColumns_hpp */
