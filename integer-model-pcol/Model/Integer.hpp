//
//  Integer.hpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 05/03/21.
//

#ifndef Integer_hpp
#define Integer_hpp

#include "Header.h"

class CplexIntegerModel {
    
private:
    IloEnv _env; //Enviroment
    IloModel _IPModel; //Model
    IloCplex _cplexIP; //Solver
    IloObjective _obj; //Objective
    IloRangeArray _Constraints; //Constraints
    IloIntVarArray _x; //Variables x
    IloIntVarArray _y; //variables y
    
    //Another model (relaxed problem)
    IloModel _relax;
    
public:
    
    CplexIntegerModel();
    void solve();
    void getSolution();
    void relaxModel();
    
};

#endif /* Integer_hpp */
