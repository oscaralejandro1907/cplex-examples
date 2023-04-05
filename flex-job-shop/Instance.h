#pragma once
#include "Header.h"

class Instance;

class Operation {
    int _id;
    static int _idgen;
    int _jobid;  //id of the job of the operation
    
    vector<pair<int, int>> _allowedmachpt;
    
public:
    Operation(int opid);
    
    int getjobid() {return _jobid;}
    int getoperationid() {return _id;}
    
    static void resetidgen() {_idgen=0;}
    
    void addmachinept(int m, int pt);
    int getprocessingtime(int m);
    
    bool isavailableonmachine(int machid);
    
    vector<pair<int, int>> getallowedmachpt() {return _allowedmachpt;}
};

class Job:public vector<Operation*> {
    static int _idgen;
    int _id;
public:
    Job();
    
    static void resetidgen() {_idgen = 0;}
    int getjobid() {return _id;}
    
    size_t getnoperations() {return this->size() ;}
};

class Machine {
    friend Instance;
    
    int _id;
    int _nop;
    int *_pt;
    
public:
    Machine(int machid, int nop);
    ~Machine();
    
    int getId() {return _id; }
    
    double getprocessingtime(int opid) {return _pt[opid];}
    
    bool canProcess(int opid) {return _pt[opid]<INFINITY;}
    
    void Print();
};


class Instance {
    string _InstanceName;
    
    int _njobs;
    int _nmachines;
    Operation **_Operations;
    Job *_Jobs;
    
    int _nops;
    
    Machine **_Machines;


public:
	Instance(string filename);
	~Instance();
    
    string getInstanceName() {return _InstanceName;}
    
    int getNjobs() {return _njobs;}
    int getNmachines() {return _nmachines;}
    Operation *getOperation(int i) {return _Operations[i];}
    Job *getJob(int j) {return &_Jobs[j];}
    
    Machine *getMachine(int m) {return _Machines[m];}
    
    int getNops() {return _nops;}
    
    bool arePrecedent(int i, int j);
    
	void print();
};

