 #include "machin.h"

machin::machin(const machin& old) {
	this->index = old.index;
	this->speed = old.speed;
	this->Tasks = old.Tasks;
	this->TasksTime = old.TasksTime;
	for (int i = 0; i < old.tasksidx.size(); i++)
		this->tasksidx.push_back(old.tasksidx.at(i));

}

 


machin::~machin()
{
	 
	Tasks.clear();
	tasksidx.clear();
}
