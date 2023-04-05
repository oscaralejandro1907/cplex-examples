//
//  main.cpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#include "Header.h"
#include "ParetoFront.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Instance *I = new Instance();
    
//    Solver *M = new MILPSolver(I,ObjType::Production);
//    M->solve();
//
//    Solution *S = M->getSolution();
//    S->print();
//
//    Solver *Ep = new EpsConstraint(I,ObjType::Production);
    
    Solver *PF = new ParetoFront(I);
    PF->solve();
    
    return 0;
}
