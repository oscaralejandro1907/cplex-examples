#include "Instance.h"

Node::Node(){
    _id=-1;
    _x=-1;
    _y=-1;
}

double Node::distanceTo(Node *N){
    double d = sqrt(pow(this->_x - N->_x, 2) + pow(this->_y - N->_y, 2));
    return round(d);
}


Instance::Instance(string filename){
	//TODO
    ifstream input(filename.c_str(), ios::in);
        
        if(!input.is_open()){
            cout<<"Error: File "<<filename<<" not found"<<endl;
            exit(1000);
        }
    
    string buffer1, buffer2;
    input>>buffer1>>buffer2>>_name;
    assert(buffer1=="NAME" && buffer2==":");
    
    //Get the number of vehicles from _name
    char *str = new char[_name.length() + 1];
    strcpy(str, _name.c_str());
    char * pch = std::strtok (str,"k.");
    int k=0;
    while (pch != NULL) {
        buffer1=pch;
        pch = strtok (NULL, "/");
        if(k==1) {
            _nvehicles=stoi(buffer1);
        }
        k++;
    }
    delete [] str;
    
    while(buffer1!="DIMENSION") {
        input>>buffer1;
    }
    input>>buffer2>>_nnodes;
    
    assert(buffer1=="DIMENSION" && buffer2==":");
    
    //Buffer Capacity
    while(buffer1!="CAPACITY") {
        input>>buffer1;
    }
    input>>buffer2>>_Q;
    
    assert(buffer1=="CAPACITY" && buffer2==":");
    
    
    input>>buffer1;
    assert(buffer1=="NODE_COORD_SECTION");
    _Nodes=new Node*[_nnodes];
    for(int i=0;i<_nnodes;++i){
        _Nodes[i]=new Node();
        input>>_Nodes[i]->_id>>_Nodes[i]->_x>>_Nodes[i]->_y;
    }
    
    input>>buffer1;
    assert(buffer1=="DEMAND_SECTION");
    for (int i=0; i<_nnodes; i++) {
        int nodeid;
        input>>nodeid>>_Nodes[i]->_dem;
        assert(nodeid==_Nodes[i]->_id);
    }
}

Instance::~Instance(){
    for(int i=0;i<_nnodes;++i) {
        delete _Nodes[i];
    }
    
    delete [] _Nodes;
}

double Instance::getDistance(Node *O, Node *D){
    return O->distanceTo(D);
}

void Instance::print(){
	//TODO
    cout<<"# vehicles: "<<_nvehicles<<endl;
    cout<<"# nodes: " << _nnodes<<endl;
    for (int i=0; i<_nnodes; i++) {
        cout << "["<< _Nodes[i]->_id <<": ("<< _Nodes[i]->_x<<","<<_Nodes[i]->_y<<")]"<<endl;
    }
}
