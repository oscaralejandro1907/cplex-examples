//
//  Solution.hpp
//  eps-constraint-example
//
//  Created by Oscar Alejandro Hernández López on 25/03/23.
//

#ifndef Solution_hpp
#define Solution_hpp

#include "Instance.hpp"

class Solution{
private:
    Instance *_I;
    
    vector<int> _product_amounts;
    
public:
    Solution(Instance *I);
    
    Solution(Solution* S);
    
    ~Solution();
    
    void addProductAmount(int p);
    
    int fitness(ObjType obj);
    
    void print();
    
    void copy(Solution *S);
    
};

#endif /* Solution_hpp */
