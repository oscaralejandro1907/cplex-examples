#pragma once
#include "Instance.h"
class Solution{
	Instance* _I;

public:
	Solution(Instance* I);
	~Solution();

	bool isFeasible();
};

