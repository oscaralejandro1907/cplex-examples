#include "Instance.h"

Operation::Operation(int machid, int pt){
    _machineid=machid;
    _pt=pt;
}


Job::Job(int jobid){
    _id=jobid;
}


Instance::Instance(string filename)
{
	//TODO
    _InstanceName=filename;
    
    ifstream input(filename.c_str(), ios::in);
    
    if(!input.is_open()){
        cout<<"Error: File "<<filename<<" not found"<<endl;
        exit(1000);
    }
    
    input>>_njobs>>_nmachines;
    
    _Jobs = new Job*[_njobs];
    for (int j=0; j<_njobs; j++) {
        _Jobs[j] = new Job(j);
        for (int m=0; m<_nmachines; m++) {
            int mach;
            int pt;
            input >> mach >> pt;
            Operation *Op = new Operation(mach,pt);
            _Jobs[j]->push_back(Op);
        }
    }
    
}

Instance::~Instance()
{
	//TODO
}

void Instance::print()
{
	//TODO
    cout << "Number of jobs: "<< _njobs << endl;
    cout << "Number of machines: "<< _nmachines << endl;
    
    for (int j=0; j<_njobs; j++) {
        cout<<"Job "<<_Jobs[j]->getjobid()<<":";
        for (auto e:*_Jobs[j]) {
            cout<<" {"<<e->getmachineid()<<" "<<e->getprocessingtime()<<"}";
        } cout<<endl;
    }
}
