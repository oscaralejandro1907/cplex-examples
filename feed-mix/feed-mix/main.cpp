//
//  main.cpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#include "Header.h"
#include "CPLEX.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Instance *data = new Instance();
    
    CPLEX *problem = new CPLEX(data);
    return 0;
}
