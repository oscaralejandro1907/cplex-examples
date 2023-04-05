//
//  Sample2.cpp
//  multiObj-sample
//
//  Created by Oscar Alejandro Hernández López on 24/06/22.
//

#include "Sample2.hpp"

Sample2::Sample2(){
    
    //data
    int nkids = 200;
    
    int costBus30seats = 400;
    int costBus40seats = 500;
    int costBus50seats = 625;
    
    
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    
    _Constraints = IloRangeArray(_env);
    
    _x = IloNumVarArray(_env);
    for (int i=0; i<3; i++) {
        _x.add(IloNumVar(_env));
    }
    
    //kids to be transported
    IloExpr c(_env);
    c = 30*_x[0] + 40*_x[1] + 50*_x[2];
    _Constraints.add(IloRange(_env, nkids ,c, IloInfinity));
    c.end();
    
    //Add constraint
    _model.add(_Constraints);
    
    //Objectives
    IloExpr costs(_env);
    costs = costBus30seats*_x[0] + costBus40seats*_x[1] + costBus50seats*_x[2];
    
    IloExpr co2(_env);
    co2 = 1.2*_x[0] + 1.1*_x[1] + 1*_x[2];
    
    IloNumExprArray objArray(_env);
    objArray.add(costs);
    objArray.add(co2);
    
    // Multicriteria lexicographic optimization
    _model.add(IloMinimize(_env, IloStaticLex(_env, objArray)));
    
    _cplex.exportModel("Modellex2.lp");
    
    _cplex.solve();
    
    cout<<_cplex.getObjValue()<<endl;
    

    
}
