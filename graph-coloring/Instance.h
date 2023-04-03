#pragma once
#include "Header.h"


class Instance {

    int _ncountries;
    const char *_Names[6] = {"Belgium", "Denmark", "France", "Germany", "Luxembourg", "Netherlands"};


public:
	Instance();
	~Instance();
    
    int getNCountries() {return _ncountries;}
    const char *getName(int idcountry) {return _Names[idcountry];}
    
	void print();
};

