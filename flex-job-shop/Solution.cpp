#include "Solution.h"

Solution::Solution(Instance* I){
	_I = I;
    _machseq = new vector<int>[_I->getNmachines()];
    _st = new double[_I->getNops()];
    _ct = new double[_I->getNops()];
}

Solution::~Solution(){
    delete [] _machseq;
    delete [] _st;
    delete [] _ct;
}

bool Solution::addoperation(int m, int op, double st, double ct){
    assert(st<INT_MAX);
    _machseq[m].push_back(op);
    _st[op] = st;
    _ct[op] = ct;
    return true;
}

void Solution::sortall(){
    for (int m=0; m<_I->getNmachines(); m++) {
        sort(_machseq[m].begin(), _machseq[m].end(), customcomp(_st));
    }
}

int Solution::getmachassignmentforop(int i){
    for (int m=0; m<_I->getNmachines(); m++) {
        if (find(_machseq[m].begin(), _machseq[m].end(), i) != _machseq[m].end()) {
            return m;
        }
    }
    return -1;
}

bool Solution::isFeasible() {
    
    vector<string> ErrorMessages;
    set<int> op_list;
    
    for (int m=0; m<_I->getNmachines(); m++) {
        for (auto o:_machseq[m] ) {
            op_list.insert(o);
        }
    }
    
    
    if (op_list.size() != _I->getNops()) {
        int n = _I->getNops() - (int)op_list.size();
        string mess = to_string(n) + " operations are missing";
        ErrorMessages.push_back(mess);
    }

    for (int i=0; i<_I->getNops()-1; i++) {
        int j= i+1;
        if (_I->arePrecedent(i, j)) {
            if (ct(i) > st(j)) {
                string mess = "Precedence error between operations" + to_string(i) + "and" + to_string(j);
                ErrorMessages.push_back(mess);
            }
        }
    }
    
    if (!ErrorMessages.empty()) {
        cout<<"Solution infeasible: "<<endl;
        for (auto mess:ErrorMessages) {
            cout<<mess<<endl;
        }
        return false;
    }
    
	return ErrorMessages.empty();   //If no mess, throw 1 (true)
}

void Solution::printSolution(){
    sortall();
    for (int m=0; m<_I->getNmachines(); m++) {
        cout << "Schedule for machine "<<to_string(m) << ":  ";
        for (vector<int>::iterator it = _machseq[m].begin(); it != _machseq[m].end(); it++) {
            cout << to_string(*it) + ":[" + to_string(st(*it)) + ", " + to_string(ct(*it)) + "] ";
        } cout << endl;
    }
}
