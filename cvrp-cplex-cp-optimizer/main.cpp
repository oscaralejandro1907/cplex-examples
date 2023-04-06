// CodeTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Solver.h"
#include "MILPSolver.h"
#include "CPSolver.h"

int main(int argc, char* argv[])
{
    assert(argc > 1);
    string filename = argv[1];
    double timlim = 60;
    if (argc >= 3) timlim = stod(string(argv[2]));

    Instance *I = new Instance(filename);
    I->print();
    
    Solver *Sl = new CPSolver(I);
    Sl->solve(NULL);
    
    return 0;
}
