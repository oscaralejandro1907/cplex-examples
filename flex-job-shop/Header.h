#pragma once

#include <string>
#include <ilconcert/iloenv.h>
#include <ilcplex/ilocplex.h>
#include <ilcp/cp.h>


#include <set>
#include <list>
#include <vector>
#include <algorithm>

#include <iomanip>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <limits.h>
#include <map>

#include <chrono>
#include <numeric>

using namespace std;

//Compare by st
struct customcomp {
private:
    double *_w;
public:
    customcomp(double *w) {_w=w;}
    bool operator() (int i,int j) { return (_w[i]+0.0001<_w[j]);}
    double operator() (int i) { return _w[i];}

};
