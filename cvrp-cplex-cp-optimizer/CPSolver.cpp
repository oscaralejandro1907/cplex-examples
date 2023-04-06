#include "CPSolver.h"

void CPSolver::solvemethod(Solution* S)
{
	_cp.setParameter(IloCP::TimeLimit, _timlim);
	_cp.setParameter(IloCP::FailLimit, IloIntMax);
	_cp.setParameter(IloCP::Workers, 1);        //Number of threads
	_cp.setParameter(IloCP::SearchType, IloCP::Restart);
	_cp.solve();
    
    _cp.getObjValue();
}

CPSolver::CPSolver(Instance* I) : Solver(I,"CPSolver")
{
	//TODO: Constraint Programming Model
    try {
        _model = IloModel(_env);
        _cp = IloCP(_model);
        
        //Init Variables
        _operations = IloIntervalVarArray(_env);
        //Add nvehicles to the range; because of the init and final depots visits operation for each vehicle
        _opalternatives = IloIntervalVarArray2(_env, _I->getnnodes() + _I->getnvehicles());
        
        int initDepotIndex = 0;
        for (int i=0; i<_I->getnnodes(); i++) {
            Node *N = _I->getNode(i);
            if(N->isdepot()){
                //Initial depot
                string label = "Initial_Depot_";
                IloIntervalVar op(_env, 0, 0, IloFalse, 0, label.c_str());
                _operations.add(op);
                _opalternatives[i] = IloIntervalVarArray(_env);
                initDepotIndex = i;
            }
            else {
                //If node is not depot
                string label = "c" + to_string(N->getIndex());
                IloIntervalVar op(_env,label.c_str());
                op.setPresent();
                _operations.add(op);
                _opalternatives[i] = IloIntervalVarArray(_env);
                for (int v=0; v<_I->getnvehicles(); v++) {
                    string labelalt = label + "_v" + to_string(v);
                    IloIntervalVar vehalt(_env, 0, 0, IloTrue, 0, labelalt.c_str());
                    _opalternatives[i].add(vehalt);
                }
            }
        }

        //Final depot: one for each vehicle
        int finalDepotIndex = _I->getnnodes();
        int index = _I->getnnodes();
        for (int v = 0; v < _I->getnvehicles(); v++) {
            string label = "Final_Depot_" + to_string(v);
            IloIntervalVar op(_env, 0, 0, IloFalse, 0, label.c_str());
            _operations.add(op);
            _opalternatives[index++] = IloIntervalVarArray(_env);
        }

        //Assign values to distance matrix
        _M=IloTransitionDistance(_env, _I->getnnodes());
        for (int i=0; i<_I->getnnodes(); i++) {
            for (int j = 0; j < _I->getnnodes(); ++j){
                int dist = _I->getDistance(_I->getNode(i), _I->getNode(j));
                _M.setValue(i, j, dist);
            }
        }

        //Specify types for each node
        IloIntArray type(_env,_I->getnnodes()+1);
        for (int i=0; i<_I->getnnodes(); i++) {
            type[i] = i;
        }
        type[I->getnnodes()] = initDepotIndex;  //type of the final depot

        //Define routes and spans
        _R=IloIntervalSequenceVarArray(_env);
        _routespans = IloIntervalVarArray(_env);
        for (int v=0; v<_I->getnvehicles(); v++) {
            string label = "r_" + to_string(v);
            IloIntervalVarArray route(_env);
            for (int i=0; i<_I->getnnodes(); i++) {
                if(i != initDepotIndex){
                    route.add(_opalternatives[i][v]);
                }
                else{
                    route.add(_operations[initDepotIndex]);
                }
            }
            route.add(_operations[finalDepotIndex + v]);
            _R.add(IloIntervalSequenceVar(_env, route, type, label.c_str()));

            string labelrs = "rspan_" + to_string(v);
            IloIntervalVar span(_env, labelrs.c_str());
            _routespans.add(span);

            string labels = "span_" + to_string(v);
            _model.add(IloSpan(_env, span, route, labels.c_str()));
        }
        
        //Objective
        IloNumExpr cost(_env);
        for (int v = 0; v < _I->getnvehicles(); v++) {
            cost += IloLengthOf(_routespans[v]);
        }
        _obj = IloMinimize(_env, cost);
        _model.add(_obj);
        
        //Constraints
        //Routes must start and finish at the depot
        for (int v=0; v< _I->getnvehicles(); v++) {
            _model.add(IloFirst(_env, _R[v], _operations[initDepotIndex]));
            _model.add(IloLast(_env, _R[v], _operations[finalDepotIndex+v]));
        }
        
        //Travelling distance
        for (int v = 0; v < _I->getnvehicles(); v++) {
            string label = "Nol_" + to_string(v);
            _model.add(IloNoOverlap(_env, _R[v], _M, label.c_str()));
        }
        
        //All customers must be visited
        for (int i=0; i < _I->getnnodes(); i++) {
            if (i != initDepotIndex) {
                string label = "Alt_" + to_string(i);
                _model.add(IloAlternative(_env, _operations[i], _opalternatives[i], label.c_str()));
            }
        }
        
        //Vehicle Capacity
        for (int v=0; v<_I->getnvehicles(); v++) {
            string label = "Cap_" + to_string(v);
            IloCumulFunctionExpr C(_env);
            for (int i=0; i<_I->getnnodes(); i++) {
                if (i != initDepotIndex) {
                    C += IloStepAtStart(_opalternatives[i][v], _I->getNode(i)->demand());
                }
            }
            _model.add(C <= _I->getvehiclecapacity());
        }
        
        //Extracting the model
        _cp.exportModel("Model_cvrp.cpo");
        
    } catch (IloException& e) {
        cout << e << endl;
        exit(1000);
    }
}

CPSolver::~CPSolver()
{
	//TODO
}

Solution* CPSolver::recoversolution()
{
	//TODO
	return nullptr;
}
