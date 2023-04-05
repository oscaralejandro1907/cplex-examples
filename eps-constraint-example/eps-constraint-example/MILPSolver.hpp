//
//  MILPSolver.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#ifndef MILPSolver_hpp
#define MILPSolver_hpp

#include "Solver.hpp"

class MILPSolver : public Solver {
    IloEnv _env;
    IloCplex _cplex;
    IloModel _model;
    IloObjective _obj;
    
    IloNumVarArray _x; //Variable
    IloRangeArray _Constraints; //Constraints
        
    void solvemethod(Solution *S);
    
    IloExpr _exprToConstraint;
    IloConstraint _objConst;
    
public:
    MILPSolver(Instance *I, ObjType obj);
    ~MILPSolver();
    
    Solution *getSolution();
    
    void exportModel();
    
    //Functions for handling Epsilon Constraint
    void setObjExprAsConstraint(IloExpr objexpr, int bound);
    IloExpr getObjExprAsConstraint(){return _exprToConstraint;}
    
    IloConstraint getObjectiveParsedConstraint(){return _objConst;}
    void removeConstraint(IloConstraint cons);
    
};

#endif /* MILPSolver_hpp */
