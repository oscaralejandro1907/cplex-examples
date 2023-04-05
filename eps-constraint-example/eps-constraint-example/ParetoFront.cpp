//
//  ParetoFront.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 26/03/23.
//

#include "ParetoFront.hpp"

SolutionContainer::SolutionContainer(Solution *S){
    _S = new Solution(S);
    _obj1 = S->fitness(ObjType::Benefit);
    _obj2 = S->fitness(ObjType::Production);
}

SolutionContainer::~SolutionContainer()
{
    delete _S;
    _S = NULL;
}

ParetoFront::ParetoFront(Instance *I): Solver(I, "ParetoFront", ObjType::Production){
//    _nsol = 5;
//    _SolArray = new SolutionContainer*[_nsol];
//    for (int i=0; i<_nsol; i++) {
//        _SolArray[i] = NULL;
//    }
}

ParetoFront::~ParetoFront(){
//    for(int k=0;k<_nsol;k++){
//        if(_SolArray[k]!=NULL) {
//            delete _SolArray[k];
//        }
//    }
//    delete [] _SolArray;
}

void ParetoFront::solvemethod(Solution *S){
    Solver *eps = new EpsConstraint(_I, ObjType::Production);
    eps->solve();
    
}

Solution *ParetoFront::getSolution(){
    
    return nullptr;
    
}
