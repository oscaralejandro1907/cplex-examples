#include "Instance.h"

int Operation::_idgen=0;
int Job::_idgen=0;


Operation::Operation(int jobid){
    _id = _idgen++;
    _jobid = jobid;
}

void Operation::addmachinept(int m, int pt){
    _allowedmachpt.push_back(pair<int, int>(m,pt));
}

int Operation::getprocessingtime(int m){
    for (auto e:_allowedmachpt) {
        if (e.first==m) {
            return e.second;
        }
    }
    return INT_MAX;
}

bool Operation::isavailableonmachine(int machid){
    return getprocessingtime(machid)<INT_MAX;
}

Job::Job() : vector<Operation *>(){
    _id=_idgen++;
}

Machine::Machine(int machid,int nop){
    _id = machid;
    _nop = nop;
    _pt = new int[nop];
    
    for (int i=0; i< nop; i++) {
        _pt[i] = INFINITY;
    }
}

Machine::~Machine(){
    delete [] _pt;
}

void Machine::Print(){
    cout<<setw(10)<<"MachId_"<<_id<<"can process:";
    for (int i=0; i<_nop; i++) {
        if (canProcess(i)) {
            cout<<"op_"+to_string(i)<<" with pt of "<<_pt[i] << endl;
        }
    } cout << endl;
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
    
    Operation::resetidgen();
    Job::resetidgen();
    
    input>>_njobs>>_nmachines;
    
    _Machines = new Machine*[_nmachines];
    for (int m=0; m<_nmachines; m++) {
        _Machines[m] = new Machine(m,_nops);
    }
    
    _nops = 0;
    _Jobs = new Job[_njobs];
    for (int j=0; j<_njobs; j++) {
        cout << "This is Job id at the beggining of the loop: " << _Jobs[j].getjobid()<<endl;
        assert(_Jobs[j].getjobid() == j);
        int noperations;
        input >> noperations;
        _nops += noperations;
        for (int i=0; i<noperations; i++) {
            Operation *O = new Operation(_Jobs[j].getjobid());
            int nallowedmachines=0;
            input>>nallowedmachines;
            for (int m=0; m<nallowedmachines; m++) {
                int mach;
                int pt;
                input >> mach >> pt;
//                _Machines[mach-1]->_id=mach;
//                _Machines[mach-1]->_pt[i]=pt;
//                O->addmachinept(_Machines[mach-1]->_id, _Machines[mach-1]->_pt[i]);
                O->addmachinept(mach-1, pt);
            }
            _Jobs[j].push_back(O);
        }
        cout << "Job id at the query: " << _Jobs[j].getjobid()<<endl;
    }
    //cout << "TEST"<<endl;
    //_Machines[0]->Print();
    
    _Operations = new Operation*[_nops];
    for (int j=0; j<_njobs; j++) {
        for (auto o:_Jobs[j]) {
            _Operations[o->getoperationid()] = o;
        }
    }
    
    
    
}

Instance::~Instance(){
    for (int i =0; i<_nops; i++) {
        delete _Operations[i];
    }
    
    delete [] _Jobs;
    delete [] _Operations;
}

bool Instance::arePrecedent(int i, int j){
    Operation *Oi = _Operations[i];
    Operation *Oj = _Operations[j];
    
    return (Oi->getjobid() == Oj->getjobid() && Oi->getoperationid() == Oj->getoperationid()-1);
}

void Instance::print()
{
    cout << "Number of jobs: "<< _njobs << endl;
    cout << "Number of machines: "<< _nmachines << endl;
    
    for (int j=0; j<_njobs; j++) {
        cout <<"Job"<<_Jobs[j].getjobid()<<":";
        for (auto op:_Jobs[j]) {
            cout<<"{ "<<op->getoperationid()<<":";
            for (auto e: op->getallowedmachpt()) {
                cout<<e.first<<" "<<e.second<<" ";
            } cout<<"} ";
        }cout<<endl;
    }
}


