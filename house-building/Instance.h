#include "Header.h"

class Task {
    int _id;
    string _taskName;
    int _duration;
    
    vector<int> _precedingTasks;
    
public:
    Task(int id, string name, int duration);
    
    int getTaskId() {return _id;}
    string getTaskName() {return _taskName;}
    int getDuration() {return _duration;}
    
    void setPrecedingTask(int task);
    vector<int> getPrecedingTasks() {return _precedingTasks;}
};


class Instance {
    int _nTasks;
    Task **_Tasks;


public:
	Instance();
	~Instance();
    
    int getnTasks()  {return _nTasks;}
    
    Task *getTask(int taskid) {
        return _Tasks[taskid];
    }
    
	void print();
};

