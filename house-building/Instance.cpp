#include "Instance.h"

Task::Task(int id, string name, int duration){
    _id=id;
    _taskName=name;
    _duration=duration;
}

void Task::setPrecedingTask(int task){
    _precedingTasks.push_back(task);
}

Instance::Instance() {
	//TODO
    _nTasks=10;
    
    vector<string> TaskNames = {
        "masonry  ",
        "carpentry",
        "plumbing ",
        "ceiling  ",
        "roofing  ",
        "painting ",
        "windows  ",
        "facade   ",
        "garden   ",
        "moving   "
    };
    
    
    vector<int> TaskDurations = {
        35,
        15,
        40,
        15,
        05,
        10,
        05,
        10,
        05,
        05
    };
    
    vector<vector<int>> precedings = {
        {},
        {0},
        {0},
        {0},
        {1},
        {3},
        {4},
        {4,2},
        {4,2},
        {6,7,8,5}
    };
    
    
    _Tasks=new Task*[_nTasks];
    for (int t=0; t<_nTasks; t++) {
        _Tasks[t]=new Task(t,TaskNames[t],TaskDurations[t]);
    }
    
    for (int t=0; t<_nTasks; t++) {
        for (auto elem:precedings[t]) {
            _Tasks[t]->setPrecedingTask(elem);
        }
    }
    
    
}

Instance::~Instance()
{
	//TODO
}

void Instance::print()
{
	//TODO

}
