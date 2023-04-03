//
//  Glasses.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 29/11/21.
//

#include "Glasses.hpp"

CplexGlasses::CplexGlasses(){
    
    //Initialization
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    _obj = IloAdd(_model, IloMaximize(_env,0));
    _Constraints = IloRangeArray(_env);
    _x=IloNumVarArray(_env);
    
    //Bounds of x variables
    _x.add(IloNumVar(_env));
    _x.add(IloNumVar(_env));
    _x.add(IloNumVar(_env));
    
    //Objective
    IloExpr Z(_env);
    Z = 5*_x[0] + 4.5*_x[1] + 6*_x[2];
    _obj.setExpr(Z);
    
    Z.end();
    
    //Constraints
    IloExpr c1(_env);
    c1 = 6*_x[0] + 5*_x[1] + 8*_x[2];
    _Constraints.add(IloRange(_env,-IloInfinity,c1,60));
    c1.end();
    
    IloExpr c2(_env);
    c2 = 10*_x[0] + 20*_x[1] + 10*_x[2];
    _Constraints.add(IloRange(_env,-IloInfinity,c2,150));
    c2.end();
    
    IloExpr c3(_env);
    c3 = _x[0];
    _Constraints.add(IloRange(_env,-IloInfinity,c3,8));
    
    _model.add(_Constraints);
    
    _cplex.exportModel("glasses_model.lp");

}

void CplexGlasses::solve(){
    
    _cplex.solve();
    
    print();
}

void CplexGlasses::print(){
    
    _env.out() << "\nSolution status = " << _cplex.getStatus() << endl; //Show in console if the status of a solution is optimal
    _env.out() << "Solution value  = " << _cplex.getObjValue() << endl;  //Print in console the objective value
    
    //Get the value of variables
    IloNumArray vals(_env);
    
    _cplex.getValues(vals, _x);
    _env.out() << "Values of x "<<setw(15)<<" = " << vals << endl;
    
    
    //View the dual values (sometimes called shadow prices) for each constraint
    _cplex.getDuals(vals, _Constraints);
    _env.out() << "Duals (Shadow prices)"<<setw(6)<<" = " << vals << endl;
    
    //Reduced Costs
    _cplex.getReducedCosts(vals, _x);
    _env.out() << "Reduced Costs "<<setw(13)<<" = " << vals << endl;
    
    
}
