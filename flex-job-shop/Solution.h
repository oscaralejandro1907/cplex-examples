#pragma once
#include "Instance.h"

class Solution{
	Instance* _I;
    
    vector<int> *_machseq;
    double *_st;
    double *_ct;

public:
	Solution(Instance* I);
	~Solution();
    
    bool addoperation(int m,int op, double st, double ct);
    void sortall();
    double st(int i) {return _st[i];}
    double ct(int i) {return _ct[i];}
    
    int getmachassignmentforop(int i);
    
    bool isFeasible();
    void printSolution();
};

