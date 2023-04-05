//
//  CPLEXSolver.cpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 13/08/21.
//

#include "CPLEXSolver.hpp"

CplexModel::CplexModel(TSP *data):Algorithm(data, "CplexSolver"){
    
    //Object Initialization
    _model=IloModel(_env);
    _cplex=IloCplex(_model);
    _obj = IloAdd(_model, IloMinimize(_env,0));
    
    _Constraints = IloRangeArray(_env);
    _x = IloArray<IloNumVarArray> (_env,_dataTSP->getnnodes()+1);
    _u = IloNumVarArray(_env);
    
    
    //Creating Variables x
    for (long i=0; i<_dataTSP->getnnodes()+1; i++) {
        _x[i]=IloNumVarArray(_env);
        for (long j=0; j<_dataTSP->getnnodes()+1; j++) {
            ostringstream label;
            label<<"x_"<<i<<"_"<<j;
            _x[i].add(IloNumVar(_env,0,1,ILOINT,label.str().c_str()));
        }
    }
    
    //Creating Variables u
    for (long i=0; i<_dataTSP->getnnodes()+1; i++) {
        ostringstream label;
        label<<"u_"<<i;
        _u.add(IloNumVar(_env,1,_dataTSP->getnnodes()+1,ILOINT,label.str().c_str()));
    }
    _u[0].setUB(1);
    
    //Creating Objective Function
    IloExpr obj(_env);
    for (long i=0; i<_dataTSP->getnnodes(); i++) {
        for (long j=1; j<_dataTSP->getnnodes()+1; j++) if(i!=j){
            obj+=_dataTSP->distanceTo(i, j%_dataTSP->getnnodes())*_x[i][j];
        }
    }
    _obj.setExpr(obj);
    obj.end();
    
    //Creating Constraints
    //Leaves node i exactly once
    for (long i=0; i<_dataTSP->getnnodes(); i++) {
        ostringstream label;
        label<<"Leaving_from_"<<i;
        IloExpr expr(_env);
        for (long j=1; j<_dataTSP->getnnodes()+1; j++) if(i!=j) {
            expr+=_x[i][j];
        }
        _Constraints.add(IloRange(_env,1,expr,1,label.str().c_str()));
    }

    //Arrives at node j exactly once
    for (long i=1; i<_dataTSP->getnnodes()+1; i++) {
        ostringstream label;
        label<<"Arriving_at_"<<i;
        IloExpr expr(_env);
        for(long j=0;j<_dataTSP->getnnodes();j++) if(i!=j){
            expr+=_x[j][i];
        }
        _Constraints.add(IloRange(_env,1,expr,1,label.str().c_str()));
    }
    
    //Eliminate subtours
    for (long i=0; i<_dataTSP->getnnodes(); i++) {
        for (long j=1; j<_dataTSP->getnnodes()+1; j++) if(i!=j) {
            ostringstream label;
            label<<"No_subtours_with_"<<i<<"_"<<j;
            IloExpr expr(_env);
            expr=_u[i]-_u[j]+1-_dataTSP->getnnodes()*(1-_x[i][j]);
            _Constraints.add( IloRange(_env, -IloInfinity, expr, 0, label.str().c_str()) );
        }
    }
    
    _model.add(_Constraints);
    //Export Model
    _cplex.exportModel("TSP_Model.lp");
    
}


Solution *CplexModel::solve(Solution *){
    Solution *S=NULL;
    
    //Solving the model with Cplex Solver
    try {
        _cplex.solve();
    } catch (IloException &ex) {
        cerr << "Concert error/exception caught: "<<ex<<endl;
    }
    catch(...) {
        cerr << "Unknown error/exception caught: "<<endl;
    }
    
    //Show info from Cplex Solver
    _env.out() << "Cplex Solution status = " << _cplex.getStatus() << endl; //Show in console if the status of a solution is optimal
    _env.out() << "Cplex Solution value  = " << _cplex.getObjValue() << endl;  //Print in console the objective value

    
    //Get the value of variables from Cplex Solver
    cout<<"Cplex Values of variables"<<endl;
    for (long i=0; i<_dataTSP->getnnodes(); i++) {
        for (long j=1; j<_dataTSP->getnnodes()+1; j++) if(i!=j) {
            cout<<"x_"<<i<<"_"<<j<<": "<<_cplex.getValue(_x[i][j])<<endl;
        }
    }
    
    
    S=new Solution(_dataTSP);
    
    long i=0;
    while (i!=_dataTSP->getnnodes()) {
        S->push_back(i);
        for (long j=1; j<_dataTSP->getnnodes()+1; j++) if(i!=j) {
            if (_cplex.getValue(_x[i][j])>0.5) {
                i=j;
                break;
            }
        }
    }
    
    S->calculateFitness();
    
    return S;
    
}
