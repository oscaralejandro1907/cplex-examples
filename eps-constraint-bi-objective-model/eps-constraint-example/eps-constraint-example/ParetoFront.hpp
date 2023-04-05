//
//  ParetoFront.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 26/03/23.
//

#ifndef ParetoFront_hpp
#define ParetoFront_hpp

#include "epsConstraint.hpp"

class SolutionContainer{
private:
    Solution *_S;
    Solver *_solver;
    int _obj1;
    int _obj2;
public:
    SolutionContainer(Solution* S);
    ~SolutionContainer();
    
    int obj1() {return _obj1;}
    int obj2() {return _obj2;}
    Solution* solution() {return _S;}
};


class ParetoFront : public Solver{
    
    int _nsol;
    int _kmin,_kmax;    //Range for Pareto Font
    SolutionContainer** _SolArray;      //Array of Solutions
    
    void solvemethod(Solution *S);
    
public:
    ParetoFront(Instance *I);
    ~ParetoFront();
    
    Solution* getSolution();
    
    void printPF();
    
};

#endif /* ParetoFront_hpp */
