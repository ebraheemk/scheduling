
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

	update_TasksTable(machine1);
	update_TasksTable(machine2);
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


	update_TasksTable(machine1);
	update_TasksTable(machine2);
}
void SwapmTasks(std::vector<int> t1, int m1, std::vector<int>t2, int m2) {
	std::map<int, Node>::iterator it1, it2;
	std::vector<std::pair<int, Node>>temp1;
	std::vector<std::pair<int, Node>>temp2;

	int task,i;
	for ( i = 0; i < t1.size(); i++) {
		task = t1.at(i);
		it1 = M.at(m1).Tasks.find(task);
		temp1.push_back(std::pair<int, Node>(it1->first, it1->second));
		M.at(m1).TasksTime -= (it1->second.time * 4) / M.at(m1).speed;
		M.at(m1).Tasks.erase(it1);
	}


	for (i = 0; i < t2.size(); i++) {
		task = t2.at(i); 
		it2 = M.at(m2).Tasks.find(task);
		temp2.push_back(std::pair<int, Node>(it2->first, it2->second));
		M.at(m2).TasksTime -= (it2->second.time * 4) / M.at(m2).speed;
		M.at(m2).Tasks.erase(it2);
	}

	for (i = 0; i < temp2.size(); i++) {
		M.at(m1).Tasks.insert(temp2.at(i));
		M.at(m1).TasksTime += (temp2.at(i).second.time * 4) / M.at(m1).speed;
	}

	for (i = 0; i < temp1.size(); i++) {
		M.at(m2).Tasks.insert(temp1.at(i));
		M.at(m2).TasksTime += (temp1.at(i).second.time * 4) / M.at(m2).speed;
	}
	update_TasksTable(m1);
	update_TasksTable(m2);

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
 void print_summary() {
	 int sum = 0;
	 std::ofstream myfile("../output/summary.txt");
	 myfile << "summary\n";
	 myfile << "Tasks Count : "; myfile << J.size(); myfile << "\n";

	 for (int i = 0; i < J.size(); i++)
		 sum += J.at(i).time;
	 myfile << "Total tasks time : "; myfile << sum; myfile << "\n";
	 myfile << "Task time avrge   : "; myfile << sum / (float)J.size(); myfile << "\n";
	 myfile << "machines count  :"; myfile << M.size(); myfile << "\n";
	 sum = 0;
	 for (int i = 0; i < M.size(); i++)
		 sum += M.at(i).speed;
	 myfile << "machines speed avg "; myfile << sum /(float) M.size(); myfile << '\n';
	 float worst = (float)M.at(0).TasksTime / 4;
	 for (int i = 1; i < M.size(); i++)
	 {
		 if (((float)M.at(i).TasksTime / 4) > worst)
			 worst = (float)M.at(i).TasksTime / 4;
	 }
	 myfile << "Worst Machine Timing "; myfile << worst; myfile << '\n';
	 myfile << "______________________________________________________________________________________________________________________\n";
	 myfile << "______________________________________________________________________________________________________________________\n";
	 myfile << "tasks:\n"; 
	 int k = 0;
	 for (int i = 0; i < J.size(); i++) {
		 if (k == 3) {
			 k = 0;
			 myfile << "\n";

		 }
		 myfile << "| task index: "; myfile << J.at(i).index; myfile << " \\ task time: "; myfile << J.at(i).time; myfile << " |";
		 
		  
		 k++;
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
	 myfile << "machine index : "; myfile << M.at(i).index; myfile << '\n';
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
 bool LocalSearchNxM(int n, int m) {
	 bool flag = true;
	 bool result = true;
	 while (flag) {
		 for (int offset = 1; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() / 2; i++) {
				 int* d = new int[n];
				 GetBestOfNxM(i * 2, n, (i * 2 + offset) % M.size(), m, 0, d, 0, true);
				 if(!GetBestOfNxMbool)
				 SwapmTasks(NxMcom1Best, i * 2, NxMcom2Best, (i * 2 + offset) % M.size());
				 flag = flag && GetBestOfNxMbool;
			 }
		 }

		 for (int offset = 0; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() ; i++) {
				 int* d = new int[n];
				 GetBestOfNxM(offset, n, i, m, 0, d, 0, true);
				 if (!GetBestOfNxMbool)
					 SwapmTasks(NxMcom1Best, offset, NxMcom2Best, i );
				 flag = flag && GetBestOfNxMbool;
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
		 //flag = flag && LevelOne();
		// flag = flag && LocalSearchNxM(0, 1);

		 flag = flag && LocalSearchNxM(1, 1);

		 flag = flag && LocalSearchNxM(1, 2);
		// flag = flag && LocalSearchNxM(1, 3);
		

 		 flag = !flag;

	 }
 }
 void GetBestOf1xM(int m1Comp[], int m1, int m2, int m2tasksNo, int index, int comb[], int i,bool firsttime ) {
	 if (firsttime) {
		 Max1xM=std::fmax(M.at(m1).TasksTime, M.at(m2).TasksTime);//TODO later we can optimize uzing MaxNxM
		 GetBestOf1xMbool = true;
	 }
	 if (index == m2tasksNo) {
		 std::map<int, Node>::iterator it1, it2;
		 int a = M.at(m1).TasksTime;
		 int b = M.at(m2).TasksTime;
		 for (int j = 0; j < sizeof(m1Comp) / sizeof(m1Comp[0]); j++) {
			 it1 = M.at(m1).Tasks.find(m1Comp[j]);
			 a = a - it1->second.time*4/ M.at(m1).speed;
			 b = b + it1->second.time * 4 / M.at(m2).speed;
		 }
		 for (int j = 0; j < m2tasksNo; j++) {
			 it2 = M.at(m2).Tasks.find(comb[j]);
			 b = b - it2->second.time * 4 / M.at(m2).speed;
			 a = a + it2->second.time * 4 / M.at(m1).speed;
		 }
		 if (std::fmax(a, b) < Max1xM) {
			 GetBestOf1xMbool = false;
			 Max1xM = fmax(a, b);
			 com2Best1xM= std::vector<int>(comb, comb + m2tasksNo);//we have error here 
		 }
		/* if(max(a,b)<MaxNxM)
			 WE HAVE an better sol save it and continue....
			 //ToDo Later*/


		 return;
	 }
	 if (i >= M.at(m2).Tasks.size())
		 return;
	 comb[index] = TasksTable[m2][i];
	 GetBestOf1xM(m1Comp, m1, m2, m2tasksNo, index + 1, comb, i + 1, false);
	 GetBestOf1xM(m1Comp, m1, m2, m2tasksNo, index, comb, i + 1, false);

 }
 void GetBestOfNxM( int m1, int m1tasksNo, int m2, int m2tasksNo, int index, int* comb, int i,bool firsttime) {
	 if (M.at(m1).Tasks.size() < m1tasksNo || M.at(m2).Tasks.size() < m2tasksNo) {
		 GetBestOfNxMbool = true;
		 GetBestOf1xMbool = true;
		 return;
	 }
	 if (firsttime) {
		  MaxNxM= std::fmax(M.at(m1).TasksTime, M.at(m2).TasksTime);
		  GetBestOfNxMbool = true;

		  

	  }
	 if (index == m1tasksNo) {
		// std::vector<int> m1c(&comb,)
		 int* d = new int[m2tasksNo];
		 GetBestOf1xM(comb, m1, m2, m2tasksNo,0,d,0,true);
		 if (!GetBestOf1xMbool) {
			 if (Max1xM < MaxNxM) {
				 MaxNxM = Max1xM;
				 NxMcom1Best = std::vector<int>(comb, comb + m1tasksNo);//we have error here also 
				 NxMcom2Best = com2Best1xM;
				 GetBestOfNxMbool = false;

			 }
		 }
		 return;
	 }
	 if (i >= M.at(m1).Tasks.size())
		 return;
	 //int xx = M.at(m1).Tasks;
	// comb[index] = M.at(m1).Tasks[i].index;
	 comb[index] = TasksTable[m1][i];
	 GetBestOfNxM(m1, m1tasksNo,m2, m2tasksNo, index + 1, comb, i + 1,false);
	 GetBestOfNxM(m1, m1tasksNo, m2, m2tasksNo, index , comb, i + 1, false);

 }
 void update_TasksTable(int machine_index){
	 std::map<int, Node>::iterator j;
	 int k = 0;
	 TasksTable[machine_index] = (int*)realloc(TasksTable[machine_index],M.at(machine_index).Tasks.size() * sizeof(int));

	 for (j = M.at(machine_index).Tasks.begin(); j != M.at(machine_index).Tasks.end(); ++j, k++)
		 TasksTable[machine_index][k] = j->first;

 }

 void init_TasksTable() {
	 std::map<int, Node>::iterator j;
	 TasksTable = (int **)malloc(sizeof(int*)*M.size());
	 for (int i = 0; i < M.size(); i++) {
		 TasksTable[i] = (int*)malloc(M.at(i).Tasks.size() * sizeof(int));

		 int k = 0;
		 for (j = M.at(i).Tasks.begin(); j != M.at(i).Tasks.end(); ++j, k++) {
			 TasksTable[i][k] = j->first;
			 printf("%d,%d|", i, TasksTable[i][k]);
		 }
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
	//int sum = 0;
	
	init_data();
	 
	init_machines();
	
	init_TasksTable();
	//GetBestOfNxM(3, 1, 1, 1, 0, temp, 0, true);
	//SwapmTasks(NxMcom1Best, 3, NxMcom2Best, 1);//have error should chose two tasks 
	LocalSearch();
	 
	 
	print_report();
	print_summary();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
