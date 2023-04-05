//
//  cutstock_cplex.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 25/04/21.
//

#include "cutstock_cplex.hpp"

CplexCutstock::CplexCutstock(){
    
    //Instance
    int _rollWidth = 115;
    vector<int> _Stripswidth = {25,40,50,55,70}; //(IloNumArray size)
    vector<int> _Demands = {50,36,24,8,30};
 
    
    ///MASTER PROBLEM - CUTTING OPTIMIZATION PROBLEM
    
    _model = IloModel(_env);    //cutOpt
    _cplex = IloCplex(_model); //cutSolver
    _obj = IloMinimize(_env);   //RollsUsed
    _Constraints = IloRangeArray(_env); //Fill
    _x= IloNumVarArray(_env); //Cut
    
    //Definition of bounds of constraints
    for (auto i:_Demands) {
        _Constraints.add(IloRange(_env,i,IloInfinity));
    }
    
    //Add variables and coefficients
    for (int i=0;i<_Stripswidth.size();i++) {
        _x.add(IloNumVar(_obj(1.0) + _Constraints[i](int(_rollWidth/_Stripswidth[i]))));  //xi values
    }
    
    _model.add(_obj);
    _model.add(_Constraints);
    
    _cplex.exportModel("CutStockMyEx.lp");
    
    ///PATTERN (COLUMN) GENERATION PROBLEM (SUBPROBLEM)
    
    _subproblemModel = IloModel(_env); //patGen
    _subproblemCplex = IloCplex(_subproblemModel); //patSolver
    _subproblemObj = IloMinimize(_env,1); //ReducedCost
    _subproblemConstraints = IloRangeArray(_env);
    _a = IloNumVarArray(_env); //Use
    
    _subproblemConstraints.add(IloRange(_env,-IloInfinity,_rollWidth));
    
    for(auto i:_Stripswidth){
        _a.add(IloNumVar(_subproblemConstraints[0](i),0,IloInfinity,ILOINT));
    }
    
    _subproblemModel.add(_subproblemObj);
    _subproblemModel.add(_subproblemConstraints);
    
    _subproblemCplex.exportModel("PatternMyEx.lp");
    
    ///COLUMN GENERATION PROCEDURE
    
    IloNumArray price(_env, _Stripswidth.size()); //Array to copy the values of dual solution
    IloNumArray newpattern(_env, _Stripswidth.size());

    for (;;) {  //Infinite loop
        //Optimize over current Patterns
        _cplex.solve(); //cutSolver
        reportMasterProblem();
        
        //Find and add a new pattern
        for (int i=0; i<_Stripswidth.size(); i++) {
            price[i] = -_cplex.getDual(_Constraints[i]);
        }
        _subproblemObj.setLinearCoefs(_a, price); //For each _a, set the corresp. value of price array as its linear coef in the OF
        
        _subproblemCplex.solve();
        reportSubProblem();
        
        if (_subproblemCplex.getValue(_subproblemObj) > -RC_EPS) { //If it is non-negative stop the loop, current solution is optimal
            break;
        }
        
        _subproblemCplex.getValues(newpattern, _a); //Save the values of the variables in the subproblem
        _x.add(IloNumVar(_obj(1) + _Constraints(newpattern)));
    } //End Column Generation Procedure
    
    _model.add(IloConversion(_env, _x, ILOINT));
    
    _cplex.solve();
    cout << "Solution status: " << _cplex.getStatus() << endl;
    
    //Report of the procedure
    cout << "Best Integer solution uses " <<_cplex.getObjValue() << " rolls" << endl;
    
    for (IloInt j=0; j<_x.getSize(); j++) {
        cout<<"x_"<<j<< " = "<<_cplex.getValue(_x[j])<<endl;
    }
}

void CplexCutstock::reportMasterProblem(){
    cout<<"Rolls used: "<< _cplex.getObjValue()<<endl;
    
    for (IloInt j=0; j<_x.getSize(); j++) {
        cout<<"x_"<<j<<" (Number of times pattern "<<j<<" will be used)" <<" = "<<_cplex.getValue(_x[j])<<endl;
    }
    cout<<endl;
    
    for (IloInt i=0; i<_Constraints.getSize(); i++) {
        cout<<"Dual Value of Constraint "<<i<<" = "<<_cplex.getDual(_Constraints[i])<< setw(40)<<"(obtained with the getDual method)"<<endl;
    }
    cout<<endl;
}

void CplexCutstock::reportSubProblem(){
    
    cout<<"Reduced Cost (Objective Value in the Subproblem): "<<_subproblemCplex.getValue(_subproblemObj)<< " -CONDITION TO EVALUATE-"<<endl;
    
    if (_subproblemCplex.getValue(_subproblemObj) <= -RC_EPS) {  //If the suproblem obj funct obtained is less than practically 0 (neg), print variables
        for (IloInt i=0; i<_a.getSize(); i++) {
            cout<<"a_"<<i<<" = "<<_subproblemCplex.getValue(_a[i])<<endl;
        }
        cout<<endl;
    }
}
