#pragma once
#include "Header.h"

class Operation {
    int _machineid;
    int _pt;
    
public:
    Operation(int machid, int pt);
    
    int getmachineid() {return _machineid;}
    int getprocessingtime() {return _pt;}
};


class Job:public vector<Operation*> {
    int _id;
public:
    Job(int jobid);
    
    int getjobid() {return _id;}
};


class Instance {
    string _InstanceName;
    
    int _njobs;
    int _nmachines;
    Operation **_Operations;
    Job **_Jobs;


public:
	Instance(string filename);
	~Instance();
    
    string getInstanceName() {return _InstanceName;}
    
    int getNjobs() {return _njobs;}
    int getNmachines() {return _nmachines;}
    //Operation *getOperation(int i) {return _Operations[i];}
    Job *getJob(int j) {return _Jobs[j];}
    
	void print();
};

