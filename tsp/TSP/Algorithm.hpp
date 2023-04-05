//
//  Algorithm.hpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 13/08/21.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "Header.h"
#include "Solution.hpp"

typedef int param_t;

class Algorithm {
protected:
    string _AlgoName;
    TSP *_dataTSP;
    
    double _TimLim;
    double _MaxIter;
    double _Gap;
    
public:
    
    static const param_t TimLim;
    static const param_t Gap;
    
    Algorithm(TSP *data, string AlgoName){
        _dataTSP = data;
        _AlgoName = AlgoName;
        
        _TimLim=3600;
        _MaxIter=1000;
        _Gap=0.01;
    }
    
    virtual ~Algorithm(){}
    
    string getSolverName() {return _AlgoName;}
    
    void setParam(param_t param, double val){
        if(param==TimLim) _TimLim=val;
        else if(param==Gap) _Gap=val;
    }
    
    virtual Solution *solve(Solution *S=NULL)=0;
    
};  //This will be the parent class for all algorithms/solvers

#endif /* Algorithm_hpp */
