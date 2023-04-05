//
//  cutstock_cplex.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 25/04/21.
//

/* Example Input file:
115                         <- Width of a roll of stock (rollWidth)
[25, 40, 50, 55, 70]        <- Widths of the ordered strips
[50, 36, 24, 8, 30]         <- Number of rolls ordered of each width (demands)
*/


#ifndef cutstock_cplex_hpp
#define cutstock_cplex_hpp

#include "Header.h"

#define RC_EPS 1.0e-6   //0.000001 (a tiny number)

class CplexCutstock {
    IloEnv _env;
    
    IloModel _model;  
    IloCplex _cplex; //cutSolver
    IloObjective _obj; //Objective
    IloRangeArray _Constraints; //Constraints
    IloNumVarArray _x; //Variables
    
    
    IloModel _subproblemModel; //patGen
    IloObjective _subproblemObj; //ReducedCost
    IloNumVarArray _a; //Used
    IloRangeArray _subproblemConstraints;
    IloCplex _subproblemCplex; //patSolver
    
    
    
public:
    CplexCutstock();
    void reportMasterProblem(); //report1
    void reportSubProblem(); //report2
};

#endif /* cutstock_cplex_hpp */
