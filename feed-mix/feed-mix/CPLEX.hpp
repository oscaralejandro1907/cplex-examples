//
//  CPLEX.hpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#ifndef CPLEX_hpp
#define CPLEX_hpp

#include "Instance.hpp"


class CPLEX{
private:
    IloEnv _env;
    IloModel _model;
    IloCplex _cplex;
    IloObjective _obj;
    
    IloArray< IloNumVarArray > _x;
    
    IloRangeArray _Constraints;
    
public:
    CPLEX(Instance *data);
    ~CPLEX(){}
    
};


#endif /* CPLEX_hpp */
