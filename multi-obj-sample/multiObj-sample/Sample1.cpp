//
//  CPLEX.cpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#include "Sample1.hpp"

Sample1::Sample1(){
    
    _model = IloModel(_env);
    _cplex = IloCplex(_model);

    _Constraints = IloRangeArray(_env);
    _x = IloNumVarArray(_env);
    
    for (int i=0; i<2; i++) {
        _x.add(IloNumVar(_env));
    }
    
    //Objectives
    IloExpr f1(_env);
    f1 = _x[0];
    _objf1 = IloMaximize(_env,f1);
    
    //f1.end();
    
    IloExpr f2(_env);
    f2 = 3*_x[0] + 4*_x[1];
    _objf2 = IloMaximize(_env,f2);
    //f2.end();
    
    //Constraints
    IloExpr c1(_env);
    c1 = _x[0];
    _Constraints.add(IloRange(_env, -IloInfinity,c1, 20));
    c1.end();
    
    IloExpr c2(_env);
    c2 = _x[1];
    _Constraints.add(IloRange(_env, 40 ,c2, 40));
    c2.end();
    
    IloExpr c3(_env);
    c3 = 5*_x[0] + 4*_x[1];
    _Constraints.add(IloRange(_env, -IloInfinity ,c3, 200));
    c3.end();
    
    
    _model.add(_Constraints);
    _model.add(_objf2);
    
    //Export Model
    _cplex.exportModel("Model.lp");
    
    //Solving maximizing f1
    _cplex.solve();
    
    //get obj value
    cout<<_cplex.getObjValue()<<endl;
    
    //Store solution
    IloSolution sol1(_env);
    for (int i=0; i<2; i++) {
        sol1.setValue(_x[i], _cplex.getValue(_x[i]));
    }
    
    
    //Change objective and set the other as constraint
    _model.remove(_objf2);
    IloExpr ch(_env);
    ch = f2;
    _Constraints.add(IloRange(_env, -IloInfinity ,ch, 184));
    _model.add(_Constraints);
    _model.add(_objf1);
    _cplex.exportModel("Modellex.lp");
   _cplex.solve();
    
  cout<<_cplex.getObjValue()<<endl;
    

    
}
