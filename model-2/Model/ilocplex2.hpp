//
//  ilocplex2.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 05/03/21.
//

#ifndef ilocplex2_hpp
#define ilocplex2_hpp

#include "Header.h"

#endif /* ilocplex2_hpp */

class CplexModel {
    IloEnv _env;
    IloCplex _cplex;
    IloModel _model;
    IloObjective _obj;
    IloNumVarArray _x;
    IloNumVarArray _y;
    IloRangeArray _Constraints;
    
public:
    CplexModel();
};
