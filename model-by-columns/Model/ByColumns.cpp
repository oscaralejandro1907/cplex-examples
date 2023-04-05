//
//  ByColumns.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 04/03/21.
//

/*
 Maximize
 x1 + 2x2 + 3x3
 subject to
 -x1 + x2 + x3 <=  20
 x1 - 3x2 + x3 <=  30
 with these bounds
 0 <= x1 <= 40
 0 <= x2 <= +
 0 <= x3 <= +
 */

#include "ByColumns.hpp"

CplexbyCols::CplexbyCols(){
    
    //Initialisation
    _model = IloModel(_env);
    _cplex = IloCplex(_model);
    _obj = IloMaximize(_env);
    _Constraints = IloRangeArray(_env);
    _x= IloNumVarArray(_env);
    
    //Définition des limites des contraintes
    _Constraints.add(IloRange(_env, -IloInfinity, 20));
    _Constraints.add(IloRange(_env, -IloInfinity, 30));
    
    //Ajout de coefficients et de limites de variables
    _x.add(IloNumVar(_obj(1.0) + _Constraints[0](-1.0) + _Constraints[1](1.0), 0.0, 40.0));  //valeurs de x1
    _x.add(IloNumVar(_obj(2.0) + _Constraints[0](1.0) + _Constraints[1](-3.0))); //valeurs de x2
    _x.add(IloNumVar(_obj(3.0) + _Constraints[0](1.0) + _Constraints[1](1.0)));

    _model.add(_obj);
    _model.add(_Constraints);
    
    _cplex.exportModel("ModelbyCols.lp");
    
    _cplex.solve();
    
    IloNumArray vals(_env);
    _cplex.getDuals(vals, _Constraints);
          _env.out() << "Duals         = " << vals << endl;
    
}
