#include "CPSolver.h"

void CPSolver::solvemethod(Solution* S)
{
	_cp.setParameter(IloCP::TimeLimit, _timlim);
	_cp.setParameter(IloCP::FailLimit, IloIntMax);
	//_cp.setParameter(IloCP::Workers, 1);
	_cp.setParameter(IloCP::SearchType, IloCP::Restart);
	_cp.solve();
    
    if (_cp.solve()) {
        _cp.out() << "Makespan \t: " << _cp.getObjValue() << endl;
    }
    
}


void CPSolver::initModel(){
    
    //Init variables
    _operations = IloIntervalVarArray(_env);    //Array for operations
    _opalts = IloIntervalVarArray2(_env,_I->getNops()); //Array of alternatives for an operation
    for (int i=0; i<_I->getNops(); i++) {
        string label = "op"+to_string(i);
        IloIntervalVar op(_env,label.c_str()); //Each op interval var
        op.setPresent(); //Each op has to be done
        _operations.add(op);    //Add op to the array _operations
        _opalts[i] = IloIntervalVarArray(_env); //The alternatives array for each op
        Operation *O = _I->getOperation(i);
        for (int m=0; m<_I->getNmachines(); m++) {
            if (O->isavailableonmachine(m)) {
                string labelalt = label+"_"+to_string(m);
                int pt=O->getprocessingtime(m);
                IloIntervalVar opalt(_env,pt,pt,IloTrue,0,labelalt.c_str());
                _opalts[i].add(opalt);
            }
        }
    }
    
    //Objective
    IloIntExprArray end(_env);
    for (int i=0; i<_I->getNops(); i++) {
        end.add(IloEndOf(_operations[i]));
    }
    _obj=IloMinimize(_env,IloMax(end));
    _model.add(_obj);
    
    //Alternatives
    for (int i=0; i<_I->getNops(); i++) {
        _model.add(IloAlternative(_env, _operations[i], _opalts[i]));
    }
    
    //NoOverlap
    for (int m=0; m<_I->getNmachines(); m++) {
        IloIntervalVarArray opsinmachine(_env);
        for (int i=0; i<_I->getNops(); i++) {
            Operation *O = _I->getOperation(i);
            if (O->isavailableonmachine(m)) {
                int pos=-1;
                for (int k=0; k<=m; k++) {
                    if (O->isavailableonmachine(k)) {
                        pos++;
                    }
                }
                opsinmachine.add(_opalts[i][pos]);
            }
        }
        _model.add(IloNoOverlap(_env,opsinmachine));
    }
    
    //Precedences
    for (int i=0; i<_I->getNops()-1; i++) {
        int j=i+1;
        if (_I->arePrecedent(i, j)) {
            _model.add(IloEndBeforeStart(_env, _operations[i], _operations[j]));
        }
    }
    
    
}


CPSolver::CPSolver(Instance* I) : Solver(I,"CPSolver"){
	//TODO
    _model=IloModel(_env);
    _cp=IloCP(_model);

    initModel();
    
    //Extracting the model
    _cp.exportModel("ModelFlexJS.cpo");
}

CPSolver::~CPSolver() {
	//TODO
}

Solution* CPSolver::recoversolution() {
    try {
        _Solution = new Solution(_I);
        if (_cp.getStatus() == IloAlgorithm::Feasible || _cp.getStatus() == IloAlgorithm::Optimal) {
            for (int m=0; m<_I->getNmachines(); m++) {
                for (int i=0; i<_I->getNops(); i++) {
                    Operation *O = _I->getOperation(i);
                    if (O->isavailableonmachine(m)) {
                        int pos=-1;
                        for (int k=0; k<=m; k++) {
                            if (O->isavailableonmachine(k)) {
                                pos++;
                            }
                        }
                        if (_cp.isPresent(_opalts[i][pos])) {
                            _Solution->addoperation(m, i, _cp.getStart(_operations[i]), _cp.getEnd(_operations[i]));
                        }
                    }
                }
            }
        }
        
    } catch (IloException &e) {
        cout << e << endl;
        exit(1000);
    }
    
	return _Solution;
}
