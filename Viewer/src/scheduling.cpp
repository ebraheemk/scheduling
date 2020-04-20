
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
		tasksHV.push_back(minheap(J.at(i).time*4, i));

	minheap tasks = minheap(J.at(0).time*4, 0);
	for (  i = 1; i < J.size(); i++) {
		minheap* copy = (minheap*)&tasks;
		tasks.insert(copy, (minheap*)&tasksHV[i]);
	}




	//init machines with initial soulution

	int j = 0,k=0,z=0;
	std::pair<int, int> p;

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for(k=0;k<M.at(j).speed && i < J.size();k++, i++){
			minheap* copy = &tasks;
			if(i!= J.size()-1)
			p = tasks.pop(copy);
			else {
				p.first = tasks.value;
				p.second = tasks.index;
			}
			
			M.at(j).TasksTime += p.first/ M.at(j).speed;
			M.at(j).Tasks.insert(std::pair<int,Node>(p.second,Node(p.first /4, p.second)));
			z++;
			 
		}
		j++;
	}

	printf("Tasks num=%d\n",z);
	//INIT MACHIN MINHEAP

	for (i = 0; i < M.size(); i++)
		machinesHV.push_back(minheap(M.at(i).TasksTime, i));

	minheap machines = minheap(M.at(0).TasksTime, 0);
	for (i = 1; i < M.size(); i++) {
		minheap* copy = (minheap*)&machines;
		machines.insert(copy, (minheap*)&machinesHV[i]);
	}

	//test
	printf("ئئئئזzszz\n");
	std::pair<int, int> p1;
	while (machines.right != NULL || machines.left!=NULL ) {
	minheap* copy = &machines;
		p1 = machines.pop(copy);
		printf("%d \n", p1.first/4);
	}
	printf("%d \n", machines.value/4); 

}
 void init_data() {
	 std::string line;
	 std::ifstream myfile("tasks.txt");
	 int i = 0;
	 if (myfile.is_open())
	 {
		 while (std::getline(myfile, line))
		 {
 			 J.push_back(Node(std::stoi(line),i));
			 i++;
		 }
		 myfile.close();
	 }

	 std::ifstream myfile2("machines.txt");
	  i = 0;
	 if (myfile2.is_open())
	 {
		 while (std::getline(myfile2, line))
		 {
			 M.push_back(machin(std::stoi(line),i));
			 i++;
		 }
		 myfile2.close();
	 }

 		 

	


}
 void print_report() {
	 std::ofstream myfile("../output/report.txt");
	 myfile << "Report\n";
	 myfile << "______________________________________________________________________________________________________________________\n";
	 int j = 0;
	 for(int i=0;i<M.size();i++){ 
	 myfile << "______________________________________________________________________________________________________________________\n";
	 myfile << "##########################\n";
	 myfile << "machine SPEED : ";  myfile << M.at(i).speed; myfile << '\n';
	 myfile << "machine no : "; myfile << i; myfile << '\n';
	 myfile << "tasks total time: "; myfile << M.at(i).TasksTime/4; myfile << '\n';
	 myfile << "##########################\n";
	 std::map<int, Node>::iterator it;
	 for (it = M.at(i).Tasks.begin(); it != M.at(i).Tasks.end(); ++it){
	 //for (int k = 0; k < M.at(i).Tasks.size(); k++) {
		 if (j == 3) {
			 myfile << '\n';
			 j = 0;
		 }
		 myfile << "| task index: "; myfile << it->second.index; myfile << " \\ task time: "; myfile << it->second.time; myfile << " |";
		 j++;
	 }
	 myfile << '\n';
	 }
	 myfile.close();
 }
int main()
{
	auto start = high_resolution_clock::now();
	//std:://qDebug() << "printing value: " << std::QString(MY_VAR);
	int sum = 0;
 
	init_data();
	for (int i = 0; i < J.size(); i++)
		sum += J.at(i).time;
	printf("Task time avg %d\n", sum / J.size());
	sum = 0;
	for (int i = 0; i < M.size(); i++)
		sum += M.at(i).speed;
	printf("speed avg %f\n", sum / 30.0);
	init_machines();


	print_report();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
