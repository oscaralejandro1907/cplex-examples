//
//  Instance.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#ifndef Instance_hpp
#define Instance_hpp

#include "Header.h"

enum class ObjType { Benefit, Production };

class Instance {
    int _nvariables;
    vector <int> _vectorcoef;
    
public:
    Instance();
    
    int nvars(){return _nvariables;}
    vector <int> getCoefVector(){return _vectorcoef;}
};

#endif /* Instance_hpp */
