
 #include <iostream>
#include <cstdlib>
#include "scheduling.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono> 
using namespace std::chrono;
#define getcwd _getcwd
void init_machines() {
	int i;
	//heap insert log(n) and sorted array insert log(n) so i go in sorted array 
	//first we add one task for each machine
	//for (int i = 0; i < M.size(); i++) {
 	//	M.at(i).Tasks.push_back(J.back);
	//	J.pop_back();


	//}
 	for (i = 0; i < J.size(); i++) 
		tasksHV.push_back(minheap(J.at(i).time, i));

	minheap tasks = minheap(J.at(0).time, 0);
	for (  i = 1; i < J.size(); i++) {
		minheap* copy = (minheap*)&tasks;
		tasks.insert(copy, (minheap*)&tasksHV[i]);
	}

	for (  i = 1; i < M.size(); i++)
		machinesHV.push_back(minheap(M.at(i).TasksTime, i));

	minheap machines = minheap(M.at(0).TasksTime, 0);
	for(  i=1;i<M.size();i++) {
		minheap* copy = (minheap*)&machines;
		machines.insert(copy, (minheap*)&machinesHV[i]);
	}


	//init machines with initial soulution

	int j = 0;
	std::pair<int, int> p;

	for (i = 0; i < J.size(); i++) {
		if (j == M.size())
			j = 0;

		minheap* copy = &tasks;
		if(i!= J.size()-1)
		p = tasks.pop(copy);
		else {
			p.first = tasks.value;
			p.second = tasks.index;
		}
			
		M.at(j).TasksTime += p.first;
		M.at(j).Tasks.push_back(Node(p.first));
		j++;
	}
	/*
	printf("ئئئئזzszz\n");
	std::pair<int, int> p;
	while (tasks.right != NULL || tasks.left!=NULL ) {
	minheap* copy = &tasks;
		p = tasks.pop(copy);
		printf("%d \n", p.first);
	}
	printf("%d \n",tasks.value);*/

}
 void init_data() {
	 std::string line;
	 std::ifstream myfile("tasks.txt");
	 if (myfile.is_open())
	 {
		 while (std::getline(myfile, line))
		 {
 			 J.push_back(Node(std::stoi(line)));
		 }
		 myfile.close();
	 }

	 std::ifstream myfile2("machines.txt");

	 if (myfile2.is_open())
	 {
		 while (std::getline(myfile2, line))
		 {
			 M.push_back(machin(std::stoi(line)));
		 }
		 myfile2.close();
	 }

 		 

	


}
int main()
{
	auto start = high_resolution_clock::now();
	//std:://qDebug() << "printing value: " << std::QString(MY_VAR);
	init_data();
	init_machines();
    /*std::cout << "Hello World!\n "; 
	system("pwd");
	for (int i = 0; i < M.size(); i++)
		printf(" machin:%d  speed:%d", i, M.at(i).speed);
	printf("\n Tasks :\n");
	for (int i = 0; i < J.size(); i++)
		printf(" %d ,",  J.at(i).time);*/
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
