//
//  TSP.hpp
//  TSP
//
//  Created by Oscar Alejandro Hernández López on 13/08/21.
//

#ifndef TSP_hpp
#define TSP_hpp


#include "Header.h"

class Node;

double euclideanDistance(Node *O, Node *D);

class Node{
private:
    long _id;
    long _x;
    long _y;
    
public:
    Node(long id, long x, long y);
    
    long getx() {return _x;}
    long gety() {return _y;}
    long getid() {return _id;}
};


class TSP {
private:
    string _file;
    long _nnodes;
    Node **_Nodes;
    
public:
    TSP(string filepath);
    ~TSP();
    
    //Get Functions
    string getFileName() {return _file;}
    long getnnodes() {return _nnodes;}
    Node* getNode(long id){return _Nodes[id];}
    
    double distanceTo(long i,long j);
};

#endif /* TSP_hpp */
