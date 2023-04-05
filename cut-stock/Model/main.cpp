//
//  main.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/01/21.
//
//

#include "cutstock_cplex.hpp"

int main(int argc, const char * argv[]) {
    
    CplexCutstock *CSt = new CplexCutstock();
    
    CSt->reportMasterProblem();
    CSt->reportSubProblem();

return 0;

}  
