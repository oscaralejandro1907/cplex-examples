//
//  MILPSolver.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#include "MILPSolver.hpp"

void MILPSolver::solvemethod(Solution *S)
{
    _cplex.setParam(IloCplex::Threads, 1);
    _cplex.solve();
}

MILPSolver::MILPSolver(Instance *I, ObjType obj) : Solver(I,"MILPSolver", obj)
{
    //TODO
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    _obj = IloAdd(_model, IloMaximize(_env,0));
    
    _Constraints = IloRangeArray(_env);
    
    _x=IloNumVarArray(_env);
    
    //Variables x
    for (int i = 0; i < _I->nvars(); i++) {
        _x.add(IloNumVar(_env));
    }
    
    //Objectives
    IloExpr objexpr(_env);
    if (_objtype == ObjType::Benefit) {
        objexpr = 2*_x[0] + 5*_x[1];
        _exprToConstraint = _x[0] + _x[1];
    } else {
        objexpr = _x[0] + _x[1];
        _exprToConstraint = 2*_x[0] + 5*_x[1];
    }
    
    _obj.setExpr(objexpr);
    objexpr.end();
    
    //Bounds of variables
    _x[0].setLB(5);
    _x[0].setUB(40);
    _x[1].setLB(0);
    _x[1].setUB(20);

    //Constraints
    IloExpr c0(_env);
    c0 = 2*_x[0] + 3*_x[1];
    _Constraints.add(IloRange(_env, -IloInfinity ,c0, 95));
    c0.end();
    
    IloExpr c1(_env);
    c1 = _x[0] + 2*_x[1];
    _Constraints.add(IloRange(_env, 40 ,c1, IloInfinity));
    c1.end();

    IloExpr c2(_env);
    c2 = _x[0] + 2*_x[1];
    _Constraints.add(IloRange(_env, -IloInfinity ,c2, 55));
    c2.end();

    _model.add(_Constraints);
    
}

MILPSolver::~MILPSolver()
{
    //TODO
}

void MILPSolver::setObjExprAsConstraint(IloExpr objexpr, int bound){
    IloConstraint cons = IloRange(_env, bound, objexpr, IloInfinity);
    _objConst = cons;
    _Constraints.IloConstraintArray::add(_objConst);
    //_Constraints.add(IloRange(_env, bound, objexpr, IloInfinity));
    _model.add(_Constraints);
}

void MILPSolver::removeConstraint(IloConstraint cons){
    _model.remove(cons);
}

void MILPSolver::exportModel(){
    //Export Model to an external File
    _cplex.exportModel("Model-eps.lp");
}

Solution *MILPSolver::getSolution(){
    
    Solution* S = new Solution(_I);
    
    for (int i=0; i<_I->nvars(); i++) {
        if (_cplex.getValue(_x[i])>= 0.999) {
            S->addProductAmount(_cplex.getValue(_x[i]));
        }
    }
    
    return S;
    
}
