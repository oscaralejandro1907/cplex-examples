//
//  main.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/01/21.
//
//

/*
 Maximize         x1 + 2x2 + 3x3 +   x4
 
 subject to    -  x1 +  x2 +  x3 + 10x4 ≤ 20
                  x1 - 3x2 +  x3        ≤ 30
                        x2 -      3.5x4 =  0
 
 with these bounds         0    ≤    x1    ≤    40
                           0    ≤    x2    ≤    +∞
                           0    ≤    x3    ≤    +∞
                           2    ≤    x4    ≤    3
                                     x4    integer
 */

#include "Header.h"

int main(int argc, const char * argv[]) {
    
    IloEnv _env;
    IloCplex _cplex;
    IloModel _model;
    IloObjective _obj;
    IloNumVarArray _x;
    IloRangeArray _Constraints;
    
    
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    _obj = IloAdd(_model, IloMaximize(_env,0));
    
    _Constraints = IloRangeArray(_env);

    
    //Variables x
    _x=IloNumVarArray(_env);
    
    //Bounds of x variables
    _x.add(IloNumVar(_env,0.0, 40.0));
    _x.add(IloNumVar(_env));
    _x.add(IloNumVar(_env));
    _x.add(IloNumVar(_env, 2.0, 3.0, ILOINT));
    
    //Objective
    IloExpr z(_env);
    z = _x[0] + 2*_x[1] + 3*_x[2] + _x[3];
    _obj.setExpr(z);
    
    z.end();

    //Constraints
    IloExpr expr1(_env);
    expr1 = -_x[0] + _x[1] + _x[2] + 10*_x[3];
    _Constraints.add(IloRange(_env,-IloInfinity, expr1, 20));
    expr1.end();

    IloExpr expr2(_env);
    expr2 = _x[0] - 3*_x[1] + _x[2];
    _Constraints.add(IloRange(_env,-IloInfinity,expr2,30));
    expr2.end();

    IloExpr expr3(_env);
    expr3 = _x[1] - 3.5*_x[3];
    _Constraints.add(IloRange(_env,0,expr3,0));
    expr3.end();
        
    _model.add(_Constraints);  //Add Constraints to the Model
    
    //Solver Results
      
    _cplex.exportModel("model.lp"); //Export Model to an external file
    
    _cplex.solve(); //Solve the Cplex Model
    
    
    _env.out() << "Solution status = " << _cplex.getStatus() << endl; //Show in console if the status of a solution is optimal
    _env.out() << "Solution value  = " << _cplex.getObjValue() << endl;  //Print in console the objective value
    
    //Get the value of variables
    IloNumArray vals(_env);

    _cplex.getValues(vals, _x);
    _env.out() << "Values        = " << vals << endl;
    
    _cplex.getSlacks(vals, _Constraints);
    _env.out() << "Slacks        = " << vals << endl;

    return 0;

}  // END main
