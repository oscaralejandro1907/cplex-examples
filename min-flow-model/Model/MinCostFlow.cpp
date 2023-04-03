//
//  MinCostFlow.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 16/01/21.
//

#include "MinCostFlow.hpp"

//   minimize  c*x
//   subject to  Hx = d
//               Ax = b
//               l <= x <= u
//   where
//
//   H = (  0  0  0  0  0  0  0 -1 -1 -1  0  0 )  d = ( -1 )
//       (  1  0  0  0  0  1  0  1  0  0  0  0 )      (  4 )
//       (  0  1  0  1  0  0  1  0  1  0  0  0 )      (  1 )
//       (  0  0  1  0  1  0  0  0  0  1  0  0 )      (  1 )
//       (  0  0  0  0  0 -1 -1  0  0  0 -1  1 )      ( -2 )
//       (  0  0  0 -1 -1  0  1  0  0  0  1  0 )      ( -2 )
//       ( -1 -1 -1  0  0  0  0  0  0  0  0 -1 )      ( -1 )

//   c = (  1  1  1  1  1  1  1  0  0  0  2  2 )
//   l = (  0  0  0  0  0  0  0  0  0  0  0  0 )
//   u = ( 50 50 50 50 50 50 50 50 50 50 50 50 )

InstanceFlow::InstanceFlow(){
    _nnodes = 12;
    _costs = {1,1,1,1,1,1,1,0,0,0,2,2};
}

CplexFlow::CplexFlow(InstanceFlow *data){
    _IP = IloModel(_env);
    _cplexIP = IloCplex(_IP);
    
    _objIP = IloAdd(_IP, IloMinimize(_env,0));
    
    _Constraints = IloRangeArray(_env);
    
    _x=IloNumVarArray(_env);
    
    //Creating Variables
    for (int i=0; i<data->getnodes(); i++) {
        _x.add(IloNumVar(_env));    //Adding Variables
    }
    
    //Bounds of Variables
    for (int v=0; v<data->getnodes(); v++) {
        _x.add(IloNumVar(_env,0.0,50.0));
    }
    
    //Creating Objective Function
    IloExpr z(_env);
    for (int a=0; a<12; a++) {
        z+=data->getCosts()[a]*_x[a];
    }
    _objIP.setExpr(z);  //Add Obj. Function to Model

    z.end();

    //Creating Constraints
    IloExpr expr1(_env);
    expr1= -_x[7]-_x[8]-_x[9];
    _Constraints.add(IloRange(_env,-1,expr1,-1));
    expr1.end();
    
    IloExpr expr2(_env);
    expr2 = _x[0]+_x[5]+_x[7];
    _Constraints.add(IloRange(_env,4,expr2,4));
    expr2.end();
    
    IloExpr expr3(_env);
    expr3 = _x[1]+_x[3]+_x[6] + _x[8];
    _Constraints.add(IloRange(_env,1,expr3,1));
    expr3.end();
    
    IloExpr expr4(_env);
    expr4 = _x[2]+_x[4]+_x[9];
    _Constraints.add(IloRange(_env,1,expr4,1));
    expr4.end();
    
    IloExpr expr5(_env);
    expr5 = -_x[5]-_x[6]-_x[10]+_x[11];
    _Constraints.add(IloRange(_env,-2,expr5,-2));
    expr5.end();
    
    IloExpr expr6(_env);
    expr6 = -_x[3]-_x[4]+_x[10];
    _Constraints.add(IloRange(_env,-2,expr6,-2));
    expr6.end();
    
    IloExpr expr7(_env);
    expr7 = -_x[0]-_x[1]-_x[2]-_x[11];
    _Constraints.add(IloRange(_env,-1,expr7,-1));
    expr7.end();
    
    _IP.add(_Constraints); //Add Constraints to the Model
    
    //Export Model
      
    _cplexIP.exportModel("modelflow.lp"); //Export Model to an external file
    
    solve();
    
    IloNumArray vals(_env);
    _cplexIP.getDuals(vals, _Constraints);
          _env.out() << "Duals         = " << vals << endl;
    
    //Add this two constraints
    //
    //   A = (  0  0  0  0  0  0  0  0  0  0  2  5 )  b = (  2 )
    //       (  1  0  1  0  0  1  0  0  0  0  0  0 )      (  3 )
    
    IloExpr expra1(_env);
    expra1 = 2*_x[10]+5*_x[11];
    _Constraints.add(IloRange(_env,2,expra1,2));
    expra1.end();
    
    IloExpr expra2(_env);
    expra2 = _x[0]+_x[2]+_x[5];
    _Constraints.add(IloRange(_env,3,expra2,3));
    expra2.end();
    
    _IP.add(_Constraints); //Add Constraints to the Model
    
    cout<<"Results after constraints added: "<<endl;
    solve();    //Re-optimize
    
    //Print values of variables
    cout<<"Values of variables"<<endl;
    for (int i=0; i<data->getnodes(); i++) {
        cout<<"x_"<<i<<") "<<_cplexIP.getValue(_x[i])<<endl;
    }
    
    cout<<"Reduced costs"<<endl;
    for (int i=0; i<data->getnodes(); i++) {
        cout<<"x_"<<i<<") "<<_cplexIP.getReducedCost(_x[i])<<endl;
    }
    
}

void CplexFlow::solve(){
    
    try {
        _cplexIP.solve();
    } catch (IloException &ex) {
        cerr << "Concert error/exception caught: "<<ex<<endl;
    }
    catch(...) {
        cerr << "Unknown error/exception caught: "<<endl;
    }
    
    _env.out() << "Solution status = " << _cplexIP.getStatus() << endl; //Show in console if the status of a solution is optimal
    _env.out() << "Solution value  = " << _cplexIP.getObjValue() << endl;   //Print in console the objective value
    
    
}
