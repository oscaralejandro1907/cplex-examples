//
//  Integer.cpp
//  CPLEX_Models
//
//  Created by Oscar Alejandro Hernández López on 05/03/21.
//

#include "Integer.hpp"

/*
 𝑥𝑗: Total number of units produced of product 𝑗
 𝑦𝑖: Total number of overtime hours for department 𝑖
 
 𝑀𝑎𝑥𝑖𝑚𝑖𝑧𝑒 𝑧 =150𝑥1 + 75𝑥2 − 80𝑦1 − 125𝑦2 − 20𝑦3
 s.t.
 1.00𝑥1 +0.35𝑥2 ≤100+𝑦1    Production time of Department A
 0.30𝑥1 +0.20𝑥2 ≤ 36+𝑦2    Production time of Department B
 0.20𝑥1 +0.50𝑥2 ≤ 50+𝑦3    Production time of Department C
 𝑦1 ≤ 10                   Max. overtime of Department A
 𝑦2 ≤ 6                    Max. overtime of Department B
 𝑦3 ≤ 8                    Max. overtime of Department C
 𝑥1 ,𝑥2 ≥ 0,               Non-negativity
 𝑦1 ,𝑦2 ,𝑦3 ≥ 0,           Non-negativity
 𝑥1, 𝑥2 integer            Integrality
 
 This problem is populatebyColumn
 */

CplexIntegerModel::CplexIntegerModel(){
    
    //Initialization
    _IPModel = IloModel(_env);
    _cplexIP = IloCplex(_IPModel);
    _obj = IloMaximize(_env);
    _Constraints = IloRangeArray(_env);
    _x = IloIntVarArray(_env);
    _y = IloIntVarArray(_env);
    
    //Definition of Constraints and their limits
    _Constraints.add(IloRange(_env, -IloInfinity,100));
    _Constraints.add(IloRange(_env, -IloInfinity,36));
    _Constraints.add(IloRange(_env, -IloInfinity,50));
    _Constraints.add(IloRange(_env, -IloInfinity,10));
    _Constraints.add(IloRange(_env, -IloInfinity,6));
    _Constraints.add(IloRange(_env, -IloInfinity,8));
    
    //Coeficient and limits of variables
    _x.add(IloIntVar(_obj(100.7) + _Constraints[0](1.0)+_Constraints[1](0.3) + _Constraints[2](0.2)));    //Values of x1
    _x.add(IloIntVar(_obj(75) + _Constraints[0](0.35)+_Constraints[1](0.2) + _Constraints[2](0.5)));    //Values of x2
    _y.add(IloIntVar(_obj(-80.0) + _Constraints[0](-1.0) + _Constraints[3](1.0)));    //Values of y1
    _y.add(IloIntVar(_obj(-125.0) + _Constraints[1](-1.0) + _Constraints[4](1.0)));    //Values of y2
    _y.add(IloIntVar(_obj(-20.0) + _Constraints[2](-1.0) + _Constraints[5](1.0)));    //Values of y3
    
    _IPModel.add(_obj);
    _IPModel.add(_Constraints);
    
    _cplexIP.exportModel("IPModel.lp");
    
}


void CplexIntegerModel::relaxModel(){
    _relax = IloModel(_env);
    _relax.add(_IPModel);
    _relax.add(IloConversion(_env,_x,ILOFLOAT));
    _relax.add(IloConversion(_env, _y, ILOFLOAT));
    
    solve();
    
}


void CplexIntegerModel::solve(){
    
    try {
        _cplexIP.solve();
    } catch (IloException &ex) {
        cerr << "Concert error/exception caught: "<<ex<<endl;
    }
    catch(...) {
        cerr << "Unknown error/exception caught: "<<endl;
    }
    
    getSolution();
    
}


void CplexIntegerModel::getSolution(){
    
    _env.out() << "Solution status = " << _cplexIP.getStatus() << endl; //Show in console if the status of a solution is optimal
    _env.out() << "Solution value  = " << _cplexIP.getObjValue() << endl;   //Print in console the objective value
    
    IloNumArray vars(_env);
    
    _cplexIP.getValues(vars, _x);
    _env.out()<<"Values "<<vars<<endl;
    
}
