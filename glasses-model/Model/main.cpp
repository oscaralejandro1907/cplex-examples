//
//  main.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/01/21.
//
//

#include "Glasses.hpp"

int main(int argc, const char * argv[]) {
    
    CplexGlasses *CG = new CplexGlasses();
    CG->solve();
    CG->print();
    
return 0;

}
