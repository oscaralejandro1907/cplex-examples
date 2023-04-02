//
//  CPLEX.cpp
//  feed-mix
//
//  Created by Oscar Alejandro Hernández López on 04/10/21.
//

#include "CPLEX.hpp"

CPLEX::CPLEX(Instance *data){
    
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    _obj = IloAdd(_model, IloMinimize(_env,0));
    
    //Variables x
    _x=IloArray<IloNumVarArray>(_env,data->getNingredients());
    for (int i=0; i<data->getNingredients(); i++) {
        _x[i]=IloNumVarArray(_env);
        for (int k=0; k<data->getNTypesOfAnimals(); k++) {
            ostringstream label;
            label<<"x_"<<i<<"_"<<k;
            //_x[i].add(IloNumVar(_env,0.0,IloInfinity,label.str().c_str()) );
            _x[i].add(IloNumVar(_env,0.0,data->getCapacities()[i],label.str().c_str()) );
        }
    }
    
    //Objective Function
    IloExpr objexpr(_env);
    for (int i=0; i<data->getNingredients(); i++) {
        for (int k=0; k<data->getNTypesOfAnimals(); k++) {
            objexpr+=data->getCosts()[i]*_x[i][k];
        }
    }
    
    _obj.setExpr(objexpr);
    objexpr.end();
    
    //Constraints
    _Constraints = IloRangeArray(_env);
    
    //Feed Demand
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CDem_"<<k;
        
        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=_x[i][k];
        }
        _Constraints.add( IloRange(_env, data->getDemands()[k], expr, data->getDemands()[k], label.str().c_str()) );
        expr.end();
    }
    
    //Feed Capacity
    for (int i=0; i<data->getNingredients(); i++) {
        ostringstream label;
        label<<"CCap_"<<i;

        IloExpr expr (_env);
        for (int k=0; k<data->getNTypesOfAnimals(); k++) {
            expr+=_x[i][k];
        }
        _Constraints.add( IloRange(_env, -IloInfinity, expr, data->getCapacities()[i], label.str().c_str()) );
        expr.end();
    }

    
    //Requirements of Vitamins
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CVit_"<<k;

        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=data->getContents()[i][0]*_x[i][k];
        }
        _Constraints.add(IloRange(_env,data->getLB()[0][k]*data->getDemands()[k], expr, IloInfinity,label.str().c_str()) );
        expr.end();
    }
    
    //For the Bound
        IloExpr expr1 (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr1+=data->getContents()[i][0]*_x[i][2];
        }
    _Constraints.add(IloRange(_env,-IloInfinity, expr1, data->getUB()[0][2]*data->getDemands()[2]) );
    expr1.end();

    //Requirements of Protein
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CProt_"<<k;

        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=data->getContents()[i][1]*_x[i][k];
        }
        _Constraints.add(IloRange(_env,data->getLB()[1][k]*data->getDemands()[k], expr, data->getUB()[1][k]*data->getDemands()[k],label.str().c_str()) );
        expr.end();
    }

    //Requirements of Calcium
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CCal_"<<k;

        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=data->getContents()[i][2]*_x[i][k];
        }
        _Constraints.add(IloRange(_env,data->getLB()[2][k]*data->getDemands()[k], expr, data->getUB()[2][k]*data->getDemands()[k],label.str().c_str()) );
        expr.end();
    }

    //Requirements of Crude Fat
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CFat_"<<k;

        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=data->getContents()[i][3]*_x[i][k];
        }
        _Constraints.add(IloRange(_env,data->getLB()[3][k]*data->getDemands()[k], expr, IloInfinity,label.str().c_str()) );
        expr.end();
    }
    
    //For Bound
    for (int k=0; k<data->getNTypesOfAnimals(); k++) {
        ostringstream label;
        label<<"CFat_"<<k;

        IloExpr expr (_env);
        for (int i=0; i<data->getNingredients(); i++) {
            expr+=data->getContents()[i][3]*_x[i][k];
        }
        _Constraints.add(IloRange(_env,-IloInfinity, expr, data->getUB()[3][k]*data->getDemands()[k],label.str().c_str()) );
        expr.end();
    }

    _model.add(_Constraints);
    //Export Model
    _cplex.exportModel("ModelFeed.lp");
//
    _cplex.solve();
//
    _env.out() << "Solution value = "<<_cplex.getObjValue()<<endl;
//
    for (int i=0; i<data->getNingredients(); i++) {
        for (int k=0; k<data->getNTypesOfAnimals(); k++) {
            if(_cplex.getValue(_x[i][k]) > 0){
                cout<<"x_"<<i<<k<<") "<<_cplex.getValue(_x[i][k])<<endl;
            }
        }
    }
    
}
