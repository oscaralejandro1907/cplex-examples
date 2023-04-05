//
//  epsConstraint.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#include "epsConstraint.hpp"

EpsConstraint::EpsConstraint(Instance *I, ObjType mainobj): Solver(I, "EpsConstraint", mainobj){
    _nepsValues = 4; //Because I want 5 values (limits included)
    
    if (mainobj == ObjType::Benefit) {
        _Model1 = new MILPSolver(_I,mainobj);
        _Model2 = new MILPSolver(_I,ObjType::Production);
    } else {
        _Model1 = new MILPSolver(_I,mainobj);
        _Model2 = new MILPSolver(_I,ObjType::Benefit);
    }
    
    //Solve both single-objective problems and get Solutions
    _Model1->solve();
    Solution *Sol1 = _Model1->getSolution();
    
    _Model2->solve();
    Solution *Sol2 = _Model2->getSolution();
    
    //Define the objective to be set as Constraint and the limits of epsilon values
    if (_objtype == ObjType::Benefit) {      //_objtype is the same value than mainobj
        _asConstraint = ObjType::Production;
        _epslimits.push_back(Sol1->fitness(ObjType::Production));   //When opt benefit -> fitness in prod
        _epslimits.push_back(Sol2->fitness(ObjType::Production));   //When opt prod -> fitnes in prod
    } else {
        _asConstraint = ObjType::Benefit;
        _epslimits.push_back(Sol1->fitness(ObjType::Benefit));
        _epslimits.push_back(Sol2->fitness(ObjType::Benefit));
    }
    
    //Calculate all epsilon values the model will use
    _epsValues = setEpsValues(_epslimits[0], _epslimits[1], _nepsValues);
    
    
    _SolArray = new SolutionContainer*[_nepsValues+1];
    for (int i=0; i<=_nepsValues; i++) {
        _SolArray[i] = NULL;
    }
    
}

EpsConstraint::~EpsConstraint()
{
    //TODO
}

vector<int> EpsConstraint::setEpsValues(int lb, int ub, int partitions){
    
    if (lb>ub) {
        int temp = lb;
        lb = ub;
        ub = temp;
    }
    
    vector<int> vecEpsValues;
    
    int difference = ub - lb;
    double partition_space = difference/partitions;
    
    if(difference>=partitions){
        for (int i=0; i<=partitions; i++) {
            vecEpsValues.push_back(lb);
            lb += partition_space;
        }
    }
    else {      //Divide in intervals of 1 space
        for (int i=lb; i<=ub; i++) {
            vecEpsValues.push_back(lb);
            lb += 1;
        }
    }
    
    return vecEpsValues;
}


void EpsConstraint::solvemethod(Solution *S){
    
    //Set the second objective as Constraint in a new single-objective model
    //with all values of epsilon to make the Pareto front
    assert((_nepsValues+1) == _epsValues.size());
    
    for (int i=0;i< _epsValues.size(); i++) {
        _Model1->setObjExprAsConstraint(_Model1->getObjExprAsConstraint(), _epsValues[i]);  //Set objective as constraint
        _Model1->solve();
        Solution *Sol = _Model1->getSolution();
        _SolArray[i] = new SolutionContainer(Sol);
        _Model1->removeConstraint(_Model1->getObjectiveParsedConstraint()); //Remove the obj constraint
    
        cout << _SolArray[i]->obj1() << " " << _SolArray[i]->obj2()<< endl;
    }

}

Solution *EpsConstraint::getSolution(){
    
    return nullptr;
    
}
