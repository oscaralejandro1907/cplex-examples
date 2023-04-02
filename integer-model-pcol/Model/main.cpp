//
//  main.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/01/21.
//
//

#include "Header.h"
#include "Integer.hpp"

int main(int argc, const char * argv[]) {
    
    CplexIntegerModel *_ipmodel = new CplexIntegerModel();
    _ipmodel->solve();
    
    _ipmodel->relaxModel(); //This function relax x variables to continuos and then call function solve
    
return 0;

}
