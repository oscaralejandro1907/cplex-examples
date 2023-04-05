//
//  Solver.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#ifndef Solver_hpp
#define Solver_hpp

#include "Solution.hpp"

class Solver{
protected:
    Instance *_I;
    string _name;
    
    ObjType _objtype;
    
    virtual void solvemethod(Solution *S)=0;
    
public:
    Solver(Instance *I, string name, ObjType obj);
    virtual ~Solver();
    
    string getSolverName() {return _name;}
    void solve(Solution *S=NULL);
    virtual Solution *getSolution()=0;
    
};

#endif /* Solver_hpp */
