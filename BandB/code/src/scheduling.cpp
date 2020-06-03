
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
/*
void PassTask(int task, int machine1, int machine2) {
	std::map<int, Node>::iterator it1;
	it1 = M.at(machine1).Tasks.find(task);

	std::pair<int, Node> temp1 = std::pair<int, Node>(it1->first, it1->second);
	M.at(machine1).TasksTime -= (it1->second.time * 4) / M.at(machine1).speed;
	M.at(machine1).Tasks.erase(it1);

	M.at(machine2).Tasks.insert(temp1);
	M.at(machine2).TasksTime += (temp1.second.time * 4) / M.at(machine2).speed;
	swapCount[1][0]++;
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
	swapCount[1][1]++;

	update_TasksTable(machine1);
	update_TasksTable(machine2);
}
void SwapmTasks(std::vector<int> t1, int m1, std::vector<int>t2, int m2) {
	std::map<int, Node>::iterator it1, it2;
	std::vector<std::pair<int, Node>>temp1;
	std::vector<std::pair<int, Node>>temp2;
	swapCount[t1.size()][t2.size()]++;
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
			//if (std::fmax(a ,b) < max) {
			if ((std::fmax(a, b) < max) || ((std::fmax(a, b) == max) && ((a + b) < (M.at(machine1).TasksTime + M.at(machine2).TasksTime)))) {

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
	
}*/
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

 

	


}/*
 void print_summary() {
	 int sum = 0;
	 int minTask=J.at(0).time, maxTask= J.at(0).time;
	 std::ofstream myfile("../output/summary.txt");
	 myfile << "summary\n";
	 myfile << "Tasks Count : "; myfile << J.size(); myfile << "\n";

	 for (int i = 0; i < J.size(); i++) {
		 sum += J.at(i).time;
		 if (J.at(i).time > maxTask)
			 maxTask = J.at(i).time;
		 if (J.at(i).time < minTask)
			 minTask = J.at(i).time;
	 }
	 myfile << "Total tasks time : "; myfile << sum; myfile << "\n";
	 myfile << "Task time average    : "; myfile << sum / (float)J.size(); myfile << "\n";
	 myfile << "machines count  :"; myfile << M.size(); myfile << "\n";
	 float taskssum = sum;
	 sum = 0;
	 for (int i = 0; i < M.size(); i++)
		 sum += M.at(i).speed;
	 myfile << "machines speed avg "; myfile << sum /(float) M.size(); myfile << '\n';

	 myfile << "max task time : "; myfile << maxTask; myfile << "\n";
	 myfile << "min task time : "; myfile << minTask; myfile << "\n";
	 float optimal = taskssum / (float)sum;
	 myfile << "optimal timing if tasks count > 4xmachine count :  "; myfile << fmax(optimal, minTask); myfile << "\n";


	 float worst = (float)M.at(0).TasksTime / 4;
	 for (int i = 1; i < M.size(); i++)
	 {
		 if (((float)M.at(i).TasksTime / 4) > worst)
			 worst = (float)M.at(i).TasksTime / 4;
	 }
	 myfile << "Worst Machine Timing result  :  "; myfile << worst; myfile << '\n';
	 for (int i = 0; i < (maxLevelSearch + 1); i++) {
		 for (int j = 0; j < (maxLevelSearch + 1); j++) {
			 myfile << "swap "; myfile << i; myfile << "->"; myfile << j; myfile << "Count "; myfile << swapCount[i][j]; myfile << '\n';

		 }
	 }
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
	 and also we can change the waywe give initial slolothion *//*
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
	 int* d = new int[n];
	 while (flag) {
		 for (int offset = 1; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() / 2; i++) {
				  
				 GetBestOfNxM(i * 2, n, (i * 2 + offset) % M.size(), m, 0, d, 0, true);
				 if(!GetBestOfNxMbool)
				 SwapmTasks(NxMcom1Best, i * 2, NxMcom2Best, (i * 2 + offset) % M.size());
				 flag = flag && GetBestOfNxMbool;

				 /*
			 GetBestOfNxM((i * 2 + offset) % M.size() , n, i * 2, m, 0, d, 0, true);
			 if (!GetBestOfNxMbool)
				 SwapmTasks(NxMcom1Best, (i * 2 + offset) % M.size()  , NxMcom2Best, i * 2);
			 flag = flag && GetBestOfNxMbool;*/
/*
			 }
		 }

		 for (int offset = 0; offset < M.size(); offset++) {
			 for (int i = 0; i < M.size() ; i++) {
				
				 GetBestOfNxM(offset, n, i, m, 0, d, 0, true);
				 if (!GetBestOfNxMbool)
					 SwapmTasks(NxMcom1Best, offset, NxMcom2Best, i );
				 flag = flag && GetBestOfNxMbool;

				 /* GetBestOfNxM(i, n, offset, m, 0, d, 0, true);
				 if (!GetBestOfNxMbool)
					 SwapmTasks(NxMcom1Best, i, NxMcom2Best, offset);
				 flag = flag && GetBestOfNxMbool;*//*
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
	 *//*
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
	 bool temp;
	 while (flag) {
		  
		 flag = flag && LevelZero();
		 //flag = flag && LevelOne();
		 //Todo we should update the way we calc level for example 2->2 take time more time than 1->3 
		 for (int i = 1; i <= maxLevelSearch; i++) {
			 for (int j = i; j <= maxLevelSearch; j++) {
				 if (j == 1 && i == 1) {
					 temp = LocalSearchNxM(i, j);
					 if (temp) {
						 i = 4; j = 4;
					 }
					 flag = flag && temp;
				 }
				 else {

					 if (j == 1) {
						 if(TasksTable[i-1][maxLevelSearch]>0)
							 temp = LocalSearchNxM(i, j);
						 if (temp) {
							 i = 4; j = 4;
						 }
						 flag = flag && temp;
					 }
					 else {
						 if (TasksTable[i][j-1] > 0)
							 temp = LocalSearchNxM(i, j);
						 if (temp) {
							 i = 4; j = 4;
						 }
						 flag = flag && temp;
					 }
				 }




				 
			 }
		 }
		// flag = flag && LocalSearchNxM(1, 1); 
		// flag = flag && LocalSearchNxM(1, 2);

		  
		//  
		

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
		 //if (std::fmax(a, b) < Max1xM) {
		 if ((std::fmax(a, b) < Max1xM) || ((std::fmax(a, b) == Max1xM) && ((a + b) < (M.at(m1).TasksTime + M.at(m2).TasksTime)))) {

			 GetBestOf1xMbool = false;
			 Max1xM = fmax(a, b);
			 com2Best1xM= std::vector<int>(comb, comb + m2tasksNo);//we have error here 
		 }
		/* if(max(a,b)<MaxNxM)
			 WE HAVE an better sol save it and continue....
			 //ToDo Later*/
/*

		 return;
	 }
	 if (i >= M.at(m2).Tasks.size())
		 return;
	 comb[index] = TasksTable[m2][i];
	 GetBestOf1xM(m1Comp, m1, m2, m2tasksNo, index + 1, comb, i + 1, false);
	 GetBestOf1xM(m1Comp, m1, m2, m2tasksNo, index, comb, i + 1, false);

 }
 void GetBestOfNxM( int m1, int m1tasksNo, int m2, int m2tasksNo, int index, int* comb, int i,bool firsttime) {
	 if ((M.at(m1).Tasks.size() < m1tasksNo || M.at(m2).Tasks.size() < m2tasksNo)||(m1==m2)) {
		 GetBestOfNxMbool = true;
		 GetBestOf1xMbool = true;
		 return;
	 }
	 if (firsttime) {
		  MaxNxM= std::fmax(M.at(m1).TasksTime, M.at(m2).TasksTime);
		  GetBestOfNxMbool = true;
		  free(d_nm);
		  d_nm = new int[m2tasksNo];
		  

	  }
	 if (index == m1tasksNo) {
		// std::vector<int> m1c(&comb,)
		 
		 GetBestOf1xM(comb, m1, m2, m2tasksNo,0, d_nm,0,true);
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
 }*/

int UpperBound( ) {
	int i;

	std::vector<machin> Mcopy;
	for (int i = 0; i < M.size(); i++)
		Mcopy.push_back(M.at(i));

	minheap tasks = minheap(J.at(0).time * 4, 0);
	minheap* copy = &tasks;
	for (i = 1; i < J.size(); i++) {
		tasks.insert(copy, new minheap(J.at(i).time * 4, i));
	}


	int j = 0, k = 0, z = 0;
	std::pair<int, int> p;

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for (k = 0; k < M.at(j).speed && i < J.size(); k++, i++) {
			minheap* copy = &tasks;
			if (i != J.size() - 1)
				p = tasks.pop(copy);
			else {
				p.first = tasks.value;
				p.second = tasks.index;
			}

			M.at(j).TasksTime += p.first / M.at(j).speed;
			M.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}

	int minm, maxm;
	minm = M.at(0).TasksTime;
	maxm = M.at(0).TasksTime;
	for (i = 0; i < M.size(); i++) {
		if (M.at(i).TasksTime < minm)
			minm = M.at(i).TasksTime;
		if (M.at(i).TasksTime > maxm)
			maxm = M.at(i).TasksTime;
	}
	printf("minmum1 hmdan m %d", minm);
	maxheap tasks2 = maxheap(J.at(0).time * 4, 0);
	maxheap* copy2 = &tasks2;
	for (i = 1; i < J.size(); i++) {
		tasks2.insert(copy2, new maxheap(J.at(i).time * 4, i));
	}
	for (int i = 0; i < M.size(); i++)
		Mcopy.push_back(M.at(i));

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for (k = 0; k < M.at(j).speed && i < J.size(); k++, i++) {
			maxheap* copy2 = &tasks2;
			if (i != J.size() - 1)
				p = tasks2.pop(copy2);
			else {
				p.first = tasks2.value;
				p.second = tasks2.index;
			}

			M.at(j).TasksTime += p.first / M.at(j).speed;
			M.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}

	for (i = 0; i < M.size(); i++) {

		if (M.at(i).TasksTime > minm)
			minm = M.at(i).TasksTime;
	}
	maxm = fmin(minm, maxm);//minm now is maxmum not minmum
	printf("maximum hmdan m %d", maxm);

	return maxm;
}





void buildBBtree( int i, BBNode*  cbn, BBNode*  root, int upBound) {
	while (!todelete.empty()) {
		BBNode* dd = todelete.front();
		//if (cbn->deapth > dd->deapth) {
		//delete dd->Mi;
	//	delete[] dd->machinesTime;
		//delete dd;
		//delete todelete.front()
		todelete.pop();
		//}
	}

	int temp, totaltasktime = 0;
	root->nodesc++;
	if (cbn->deapth == tasks.size() - 1) {
		leafs.push_back(cbn);
	}
	if (cbn->deapth < tasks.size()) {



		//cbn->machines = (BBNode**)malloc(sizeof(BBNode*)*M.size());
		cbn->ntaskidx = tasks.at(cbn->deapth).second;
		for (int k = 0; k < M.size(); k++)
		{
			BBNode* ek = new BBNode();
			//	ek = (BBNode*)malloc(sizeof(BBNode));
				//cbn->machines[k]->father = cbn;
			ek->machine_index = M.at(k).index;
			ek->machine_speed = M.at(k).speed;
			ek->deapth = cbn->deapth + 1;
			ek->machinesTime = (int*)malloc(sizeof(int)*M.size());
			totaltasktime = 0;
			ek->machinesTime[k] = cbn->machinesTime[k] + (tasks.at(cbn->deapth).first) / M.at(k).speed;
			ek->taskstime = fmax(ek->machinesTime[k], cbn->taskstime);
			totaltasktime += (ek->taskstime - ek->machinesTime[k])*M.at(k).speed;

			for (int i = 0; i < k; i++) {
				ek->machinesTime[i] = cbn->machinesTime[i];
				totaltasktime += (ek->taskstime - ek->machinesTime[i])*M.at(i).speed;
			}
			for (int i = k + 1; i < M.size(); i++) {
				ek->machinesTime[i] = cbn->machinesTime[i];
				totaltasktime += (ek->taskstime - ek->machinesTime[i])*M.at(i).speed;

			}

			temp = (int)((tasks.size() - cbn->deapth - 1) / M.size());
			//if (temp < 1)
			//	temp = 1;
			ek->taskMachineRatio = (double)temp / root->mxms;
			ek->Tsum = cbn->Tsum - tasks.at(cbn->deapth).first;
			ek->MinTask = cbn->MinTask;//TASKS sorted from the bigest to the smallest so the minumum will did not changed

			ek->BestTiming = ek->taskstime + (int)fmax(((ek->Tsum - totaltasktime) / root->Msum), (ek->MinTask*ek->taskMachineRatio)/*should add div max machine speed*/);
			//cbn->machines[k]->BestTiming = cbn->machines[k]->BestTiming - (totaltasktime / root->Msum);
			ek->worstTiming = ek->taskstime + (ek->Tsum / root->mms);
			if (ek->worstTiming < root->MinWorst)
				root->MinWorst = ek->worstTiming;


			for (int e = 0; e < cbn->Mi.size(); e++)
				ek->Mi.push_back(cbn->Mi.at(e));

			ek->Mi.push_back(std::pair<int, int>(M.at(k).index, tasks.at(cbn->deapth).second));
			m.push(ek);
		}





		//	for (int k = 0; k < M.size(); k++)//we need to check all brother befor start new level for this reson we have two loops
			//{
			//	if (cbn->machines[k] != NULL) {
		bool roro = true;
	    BBNode* nextcall;
		while (roro && (!m.empty())) {
			nextcall = m.front();
			m.pop();
			if (nextcall->BestTiming <= fmin(root->MinWorst, upBound))
				roro = false;
			else
				todelete.push(nextcall);


		}

		buildBBtree( i + 1, nextcall, root, upBound);

		todelete.push(nextcall);
		//todo no recurseve constructor move to shechdulier
	}

}



/**/

void print_report() {
	std::ofstream myfile("../output/report.txt");
	myfile << "Report\n";


	myfile << "______________________________________________________________________________________________________________________\n";
	int j = 0;
	for (int i = 0; i < M.size(); i++) {
		myfile << "______________________________________________________________________________________________________________________\n";
		myfile << "##########################\n";
		myfile << "machine SPEED : ";  myfile << M.at(i).speed; myfile << '\n';
		myfile << "machine index : "; myfile << M.at(i).index; myfile << '\n';
		myfile << "tasks total time: "; myfile << (float)M.at(i).TasksTime / 4; myfile << '\n';
		myfile << "##########################\n";
		std::map<int, Node>::iterator it;
		for (it = M.at(i).Tasks.begin(); it != M.at(i).Tasks.end(); ++it) {
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
void insert_soulution(BBNode* survival) {
	int i = J.size() - 1;
	while (i>=0) {

//		M.at(survival->machine_index).Tasks.insert(std::pair<int,Node>(survival->father->ntaskidx, J.at(survival->father->ntaskidx)));
		//we multiplay with 4 becouse in print report we divide by 4
		//worng J.at(i) not sorted 
		//M.at(survival->machine_index).TasksTime = M.at(survival->machine_index).TasksTime + ((J.at(survival->father->ntaskidx).time*4) / M.at(survival->machine_index).speed);
		i--;
		//survival = survival->father;
	}

}
 void Branch_and_Bound() {
	// std::vector<Node> M = J;
	 int up = UpperBound();



	 int Tsum = 0, mmspeed, Msum;
	 int maxTask = J.at(0).time;
	 int minTask = J.at(0).time;
	 for (int i = 0; i < J.size(); i++) {
		 Tsum += J.at(i).time;
		 if (J.at(i).time > maxTask)
			 maxTask = J.at(i).time;
		 if (J.at(i).time < minTask)
			 minTask = J.at(i).time;
	 }
	 minTask = minTask * 4;
	 maxTask = maxTask * 4;
	 Tsum = Tsum * 4;
	 mmspeed = M.at(0).speed;
	 int tempmax = M.at(0).speed;
	 Msum = M.at(0).speed;
	 for (int i = 1; i < M.size(); i++) {
		 Msum = Msum + M.at(i).speed;
		 if (M.at(i).speed < mmspeed)
			 mmspeed = M.at(i).speed;
		 if (M.at(i).speed > tempmax)
			 tempmax = M.at(i).speed;
	 }
	 int temp = (int)(J.size() / M.size());
	 if (temp < 1)
		 temp = 1;
	 int bt = fmax((Tsum / Msum), (int)(minTask*(double)(temp / tempmax)));
	BBNode A =  BBNode(0, -1, -1, (double)temp / tempmax, 0, bt, Tsum, Msum, mmspeed, minTask, tempmax, M.size());



	// BBNode A = BBNode(J, M,up); 
 	 //BBNode A = BBNode(J, M);

	 std::pair<int, int> p1;
	 maxheap mxhp = maxheap(J.at(0).time * 4, 0);
	 for (int i = 1; i < J.size(); i++) {
		 mxhp.insert(&mxhp, new maxheap(J.at(i).time * 4, i));
	 }

	 while (mxhp.GetRight() != NULL || mxhp.GetLeft() != NULL) {
		 p1 = mxhp.pop(&mxhp);
		 tasks.push_back(p1);
	 }
	 tasks.push_back(std::pair<int, int>(mxhp.value, mxhp.index));



	 buildBBtree( 0, &A, &A, up);
	 printf("\n&&%d&&&\n",leafs.size());
 	 //insert_soulution(A.ServiverPath);
	 //next go from leaf to root on servivel path and insert tasks into machines 
  }

int main()
{
	auto start = high_resolution_clock::now();
	
	//int sum = 0;
	
	init_data();
	 
	
	Branch_and_Bound();
	print_report();
//	print_report();
	//print_summary();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
