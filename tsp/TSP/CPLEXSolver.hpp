//
//  CPLEXSolver.hpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 13/08/21.
//

#ifndef CPLEXSolver_hpp
#define CPLEXSolver_hpp

#include "Algorithm.hpp"

#include <ilconcert/iloenv.h>
#include <ilcplex/ilocplex.h>

class CplexModel:public Algorithm {
private:
    IloEnv _env;
    IloModel _model;
    IloCplex _cplex;
    IloObjective _obj;
    
    IloArray<IloNumVarArray> _x;
    IloNumVarArray _u;
    
    IloRangeArray _Constraints;
    
public:
    CplexModel(TSP *data);
    ~CplexModel(){}
    
    Solution *solve(Solution *);
};

#endif /* CPLEXSolver_hpp */
