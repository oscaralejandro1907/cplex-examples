//
//  epsConstraint.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#ifndef epsConstraint_hpp
#define epsConstraint_hpp

#include "MILPSolver.hpp"
#include "ParetoFront.hpp"

class MILPSolver;
class SolutionContainer;

class EpsConstraint : public Solver {
    
    int _nepsValues;
    MILPSolver *_Model1, *_Model2;
    
    ObjType _asConstraint;
    
    vector<int> _epslimits;     //Limits in which epsilon values take place
    vector <int> _epsValues;    //All epsilon values that will be bounds in the Constraints
    
    SolutionContainer** _SolArray;      //Array of Solutions
    
    void solvemethod(Solution *S);
    
public:
    EpsConstraint(Instance *I, ObjType mainobj);
    ~EpsConstraint();
    
    int nEpsValues(){return _nepsValues;}
    
    Solution *getSolution();
    
    vector<int> setEpsValues(int lb, int ub, int partitions);
    
};


#endif /* epsConstraint_hpp */
