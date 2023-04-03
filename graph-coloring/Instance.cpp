#include "Instance.h"

Instance::Instance() {
	//TODO
    _ncountries = 6;
    
}

Instance::~Instance()
{
	//TODO
}

void Instance::print()
{
	//TODO
    cout<<"Number of countries: "<<_ncountries<<endl;
    
    cout<<"Countries are: "<<endl;
    
    for (int i=0; i<_ncountries; i++) {
        cout<<_Names[i]<<endl;
    }
}
