
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
void PassTask(int task, int machine1, int machine2) {
	std::map<int, Node>::iterator it1;
	it1 = M.at(machine1).Tasks.find(task);

	std::pair<int, Node> temp1 = std::pair<int, Node>(it1->first, it1->second);
	M.at(machine1).TasksTime -= (it1->second.time * 4) / M.at(machine1).speed;
	M.at(machine1).Tasks.erase(it1);

	M.at(machine2).Tasks.insert(temp1);
	M.at(machine2).TasksTime += (temp1.second.time * 4) / M.at(machine2).speed;
}
void SwapTasks(int task1, int machine1, int task2, int machine2) {
	 std::map<int, Node>::iterator it1,it2;

	it1= M.at(machine1).Tasks.find(task1);
	std::pair<int, Node> temp1= std::pair<int, Node>(it1->first,it1->second);
	M.at(machine1).TasksTime -= (it1->second.time*4) / M.at(machine1).speed;
	M.at(machine1).Tasks.erase(it1);

	it2 = M.at(machine2).Tasks.find(task2);
	std::pair<int, Node> temp2 = std::pair<int, Node>(it2->first, it2->second);
	M.at(machine2).TasksTime -= (it2->second.time*4)/ M.at(machine2).speed;
	M.at(machine2).Tasks.erase(it2);

	M.at(machine1).Tasks.insert(temp2);
	M.at(machine1).TasksTime += (temp2.second.time*4) / M.at(machine1).speed;
	M.at(machine2).Tasks.insert(temp1);
	M.at(machine2).TasksTime += (temp1.second.time*4)/ M.at(machine2).speed;



}
int GetBestThrow(int machine1, int  machine2) {
	//best throw from machine1 to machine2
	//int segma = abs(M.at(machine1).TasksTime - M.at(machine2).TasksTime);
	int max = std::fmax(M.at(machine1).TasksTime, M.at(machine2).TasksTime);
	int m1s = M.at(machine1).speed;
	int m2s = M.at(machine2).speed;
	int a, b;
	int t1 = -1;
	std::map<int, Node>::iterator i;
	for (i = M.at(machine1).Tasks.begin(); i != M.at(machine1).Tasks.end(); ++i) {
			a = M.at(machine1).TasksTime - (i->second.time * 4) / m1s;
			b = M.at(machine2).TasksTime + (i->second.time * 4) / m2s;
			if (std::fmax(a ,b) < max) {
				max = std::fmax(a, b);
				t1 = i->second.index;
		}

	}

	return t1;

}

std::pair<int, int> GetBestSolOfTwo(int machine1, int  machine2) {
	//int segma = abs(M.at(machine1).TasksTime - M.at(machine2).TasksTime);
	int max = std::fmax(M.at(machine1).TasksTime, M.at(machine2).TasksTime);
	int m1s = M.at(machine1).speed;
	int m2s = M.at(machine2).speed;
	int a, b;
	int t1 = -1,t2=-1;
	std::map<int, Node>::iterator i;
	std::map<int, Node>::iterator j;
	for (i = M.at(machine1).Tasks.begin(); i != M.at(machine1).Tasks.end(); ++i) {
		for (j = M.at(machine2).Tasks.begin(); j != M.at(machine2).Tasks.end(); ++j) {
			a = M.at(machine1).TasksTime - (i->second.time * 4) / m1s;
			a = a + (j->second.time * 4) / m1s;
			b = M.at(machine2).TasksTime - (j->second.time * 4) / m2s;
			b = b + (i->second.time * 4) / m2s;
			//if (abs(a - b) < max) {
			//	segma = abs(a - b);
			if(std::fmax(a,b)<max){
				max = std::fmax(a, b);
				t1 = i->second.index;
				t2 = j->second.index;
			}

		}

	}

	return std::pair<int, int>(t1, t2); 
}
bool M1ToM2Throw(int machine1, int  machine2) {
	bool result = true;
	int best = GetBestThrow(machine1, machine2);
	while (best != -1 ) {
		result = false;
		PassTask(best, machine1, machine2);
		best = GetBestThrow(machine1, machine2);
	}
	return result;

}
bool TwoMachineLocalSearch(int machine1, int  machine2) {
	bool result = true;
	std::pair<int, int>best = GetBestSolOfTwo(machine1, machine2);
	while (best.first != -1 && best.second != -1) {
		result = false;
		SwapTasks(best.first, machine1, best.second, machine2); 
		best = GetBestSolOfTwo(machine1, machine2);
	}
	return result;
}
void init_machines() {
	int i;
	 

	minheap tasks = minheap(J.at(0).time*4, 0);
	minheap* copy = &tasks;
	for (  i = 1; i < J.size(); i++) {
		tasks.insert(copy, new minheap(J.at(i).time * 4, i));
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

 
	minheap machines = minheap(M.at(0).TasksTime, 0);
	 copy = (minheap*)&machines;

	for (i = 1; i < M.size(); i++) {
 		machines.insert(copy, new minheap(M.at(i).TasksTime, i));
	}

	//test
	printf("ئئئئזzszz\n");
	std::pair<int, int> p1;
	minheap copym = machines;
	while (machines.GetRight() != NULL || machines.GetLeft()!=NULL ) {
	minheap* copy = &machines;
		p1 = machines.pop(copy);
		printf("%d \n", p1.first/4);
	}
	printf("%d \n", machines.value/4); 
	///copy
	while (copym.GetRight() != NULL || copym.GetLeft() != NULL) {
		minheap* copy = &copym;
		p1 = copym.pop(copy);
		printf("jjj %d \n", p1.first / 4);
	}
	printf("jjjj %d \n", copym.value / 4);
	
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

	 machinesHV = (minheap**)malloc(sizeof(minheap*) * M.size());
	 tasksHV= (minheap**)malloc(sizeof(minheap*) * J.size());

	


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
	 myfile << "tasks total time: "; myfile << (float)M.at(i).TasksTime/4; myfile << '\n';
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
 bool LevelZero() {
	 /*TODO :to optimize we can use any sort of nlogn so each time we check two machine by
	 o(1) instide of o(n) bcz we only need maximum
	 and also we can change the waywe give initial slolothion */
	 bool flag=true;
	 bool result = true;
	 while (flag) {
		 for (int offset = 1; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() / 2; i++) {
				 flag = flag && M1ToM2Throw(i * 2, (i * 2 + offset) % M.size());

			 }
		 }
		 for (int offset = 0; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size(); i++) {
				 flag = flag && M1ToM2Throw(i ,offset);

			 }

		 }
		 result = result && flag;
		 flag = !flag;

	 }
	 return result;
 }
 bool LevelOne() {
	 bool flag = true;
	 bool result=true;
	 /*TODO later we dont need to check all pairs of machines only pairs that one one machine
	 of them have changed  so we can hold type of ReadyQueue that hold all the machines that
	 was changed and check them with other machines and stop we we have empty ready queue that mean
	 we pass over all compantion of two machines and there no two machine that we can optimize his time
	 */
	 while(flag){
		 for (int offset = 1; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() / 2; i++) {
				flag=flag && TwoMachineLocalSearch(i * 2, (i * 2 + offset) % M.size());
			 }
		 }
		 result = result && flag;
		flag = !flag;

	 }
	 return result;
 }
 void LocalSearch() {
	 bool flag = true;
	 while (flag) {
		 flag = flag && LevelZero();
		 flag = flag && LevelOne();
		 flag = !flag;

	 }
 }
int main()
{
	auto start = high_resolution_clock::now();
	//std:://qDebug() << "printing value: " << std::QString(MY_VAR);
	/*minheap s = minheap(2, 5);
	minheap v= minheap(3, 4);
	s.insert(&s, &v);
	minheap v2 = minheap(1, 1);
	s.insert(&s, &v2);
	minheap v3 = minheap(21, 12);
	s.insert(&s, &v3);
	minheap v4 = minheap(13, 13);
	s.insert(&s, &v4);
	minheap k = s;*/
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
	LocalSearch();

	print_report();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
