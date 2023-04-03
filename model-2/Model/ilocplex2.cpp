//
//  ilocplex2.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 05/03/21.
//

#include "ilocplex2.hpp"
#include "Header.h"

/*
 MAxZ = X1 + (3/2) X2
 
 2X1 + 2X2 ≤ 16    Restricción debida a las horas disponibles por semana de la MQ A

 X1 + 2X2 ≤ 12    Restricción debida a las horas disponibles por semana de la MQ B

 4X1 + 2X2 ≤ 28    Restricción debida a las horas disponibles por semana de la MQ C
 
 Xj ≥ 0 ;

 */
CplexModel::CplexModel(){
    //Initialization
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    
    _obj = IloAdd(_model, IloMaximize(_env,0));
    _Constraints = IloRangeArray(_env);
    _x=IloNumVarArray(_env);
    
    //Variables x
    _x.add(IloNumVar(_env));
    _x.add(IloNumVar(_env));
    
    //Objective
    IloExpr Z(_env);
    Z = _x[0] + 1.5*_x[1];
    _obj.setExpr(Z);
    
    Z.end();
    
    //Constraints
    IloExpr c1(_env);
    c1 = 2*_x[0] + 2*_x[1];
    _Constraints.add(IloRange(_env,-IloInfinity,c1,16));
    c1.end();
    
    IloExpr c2(_env);
    c2 = _x[0] + 2*_x[1];
    _Constraints.add(IloRange(_env,-IloInfinity,c2,12));
    c2.end();

    IloExpr c3(_env);
    c3 = 4*_x[0] + 2*_x[1];
    _Constraints.add(IloRange(_env,-IloInfinity,c3,28));
    
    _model.add(_Constraints);
    
    _cplex.exportModel("model2.lp");
    
    _cplex.solve();
    
    _env.out() <<"Solution status = " <<_cplex.getStatus()<<endl;
    
    _env.out() << "Solution value = "<<_cplex.getObjValue()<<endl;
    
    IloNumArray vals(_env);
    
    _cplex.getValues(vals, _x);
    _env.out() << "Vals = " << vals <<endl;
    
    _cplex.getSlacks(vals, _Constraints);
    _env.out() << "Slacks = " << vals << endl;
    

    _cplex.getDuals(vals, _Constraints);
          _env.out() << "Duals         = " << vals << endl;
}
