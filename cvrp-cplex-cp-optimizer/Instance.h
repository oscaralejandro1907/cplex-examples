#include "Header.h"

class Instance;

class Node {
    friend Instance;
    
    int _x;
    int _y;
    int _dem;
    int _id;
    
public:
    Node();
    ~Node() {}
    
    int getIndex() {return _id;}
    int demand() {return _dem;}
    bool isdepot() {return _id==1;}
    bool iscustomer() {return !isdepot();}
    
    double distanceTo(Node *N);
};


class Instance {
    
    string _name;   //instance name
    int _nnodes;    //number of nodes, (first node is the depot)
    Node **_Nodes;      //List of Nodes (objects of type Node)
    int _nvehicles;     //number of vehicles
    int _Q;             //vehicle capacity

public:
	Instance(string filename);
	~Instance();
    
    string getInstanceName() {return _name;}
    int getvehiclecapacity() {return _Q;}
    int getnvehicles() {return _nvehicles;}
    int getnnodes() {return _nnodes;}
    Node *getNode(int i) {return _Nodes[i];}
    Node *getdepot() {return _Nodes[0];}
    
    double getDistance(Node *O, Node *D);

	void print();
};

