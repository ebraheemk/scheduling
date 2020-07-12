
 #include <iostream>
#include <cstdlib>
#include "scheduling.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono> 
#include <ctime>
using namespace std::chrono;
#define getcwd _getcwd
void PassTask(Chromosome* a,int task, int machine1, int machine2) {
	std::map<int, Node>::iterator it1;
	it1 = a->Mchnz.at(machine1)->Tasks.find(task);

	std::pair<int, Node> temp1 = std::pair<int, Node>(it1->first, it1->second);
	a->Mchnz.at(machine1)->TasksTime -= (it1->second.time  ) / M.at(machine1).speed;
	a->Mchnz.at(machine1)->Tasks.erase(it1);

	a->Mchnz.at(machine2)->Tasks.insert(temp1);
	a->Mchnz.at(machine2)->TasksTime += (temp1.second.time  ) / M.at(machine2).speed;
	//swapCount[1][0]++;
	//update_TasksTable(machine1);
	//update_TasksTable(machine2);
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
void SwapmTasks(std::vector<int> t1, machin *m1, std::vector<int>t2, machin* m2) {
	std::map<int, Node>::iterator it1, it2;
	std::vector<std::pair<int, Node>>temp1;
	std::vector<std::pair<int, Node>>temp2;
	//swapCount[t1.size()][t2.size()]++;
	int task,i;
	for ( i = 0; i < t1.size(); i++) {
		task = t1.at(i);
		it1 = m1->Tasks.find(task);
		temp1.push_back(std::pair<int, Node>(it1->first, it1->second));
		m1->TasksTime -= (it1->second.time ) / m1->speed;
		m1->Tasks.erase(it1);
 	}


	for (i = 0; i < t2.size(); i++) {
		task = t2.at(i); 
		it2 = m2->Tasks.find(task);
		temp2.push_back(std::pair<int, Node>(it2->first, it2->second));
		m2->TasksTime -= (it2->second.time ) / m2->speed;
		m2->Tasks.erase(it2);
	}

	for (i = 0; i < temp2.size(); i++) {//ftasks sould be unique
		m1->Tasks.insert(temp2.at(i));
		m1->tasksidx.push_back(temp2.at(i).first);

		m1->TasksTime += (temp2.at(i).second.time ) / m1->speed;
	}

	for (i = 0; i < temp1.size(); i++) {
		m2->Tasks.insert(temp1.at(i));
		m2->tasksidx.push_back(temp1.at(i).first);

		m2->TasksTime += (temp1.at(i).second.time ) / m2->speed;
	}
	//update_TasksTable(m1);
	//update_TasksTable(m2);

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
 std::vector<Node> ChooseRandomKtasks(int k) {
	 std::vector<Node> res;
	 int rtmp;
	 for (int i = 0; i < k; i++)
	 {
		 rtmp = rand() % CopyJ.size();
		 res.push_back(Node( CopyJ.at(rtmp).time*4, CopyJ.at(rtmp).index));
		 CopyJ.erase(CopyJ.begin() + rtmp);

	 }
	 return res;
 }
 std::vector<int> ChooseRandomKtasks(int k, machin* mch) {
	 std::vector<int> res;
	 int rtmp;
	 for (int i = 0; i < k; i++)
	 {
		 rtmp = rand() % mch->tasksidx.size();
		 res.push_back(mch->tasksidx.at(rtmp));
		 mch->tasksidx.erase(mch->tasksidx.begin() + rtmp);

	 }
	 return res;
 }
 int peak_machine(int m) {
	 int k   = (rand() % (M.size()));
	 int j = rand() % 2;
	 if (j == 0)
		 j = -1;
	 if (k == m) {
		 k = k + j;
		 if (k == M.size())
			 k--;
		 if (k == m)
			 k--;
		 if (k < 0)
			 k++;
	 }
	 return k;
 }
 void mutation(Chromosome* c1) {
	 Chromosome* ccc = new Chromosome(*c1) ;
	 int k,m;
	 int m1, m2, tmp;
	 std::map<int, int>::iterator it1;
	 k = (rand() % (J.size() )) ;
 	 m = (rand() % (J.size() )) ;
	 if (m < k)
	 {
		 tmp = k;
		 k = m;
		 m = tmp;
	 }
#ifdef _dontChangeAll
	 if ((m - k) == (J.size() - 1))// we dont want to change all
	 {
		 k++;
		 m--;
	 }
#endif
	 for (int i =k; i <= m; i++) {
		 it1 = ccc->Tsx.find(i);// M.at(m1).Tasks.find(m1Comp[j]);

		 m1 = it1->second;
		 m2 = peak_machine(m1);
		 PassTask(ccc, i, m1, m2);
 		 it1->second = m2;
 	 }
	 ccc->SolTime = ccc->Mchnz.at(0)->TasksTime;
 
	 //update sol time
	 for (int i = 1; i < ccc->Mchnz.size(); i++) {
		 if (ccc->Mchnz.at(i)->TasksTime > ccc->SolTime)
			 ccc->SolTime = ccc->Mchnz.at(i)->TasksTime;
	 }

	 //update survival ,lower/upper bound

	 if ((ccc->SolTime < bestSol)) {
		 bestSol = ccc->SolTime;
		 delete survival;
		 survival = new Chromosome(*ccc);
	 }
	 if (ccc->SolTime > newworsSol)
		 newworsSol = ccc->SolTime;
	 NextGen.push_back(ccc);
	 

 }

void pmx(Chromosome*c1, Chromosome*c2, int k, int m){
	//Chromosome* c1 = new Chromosome(*ck1);
	Chromosome* ccc1 = new Chromosome(*c1);

	Chromosome* ccc2 = new Chromosome(*c2);

	 std::map<int, int>::iterator it1, it2;
	 int m1, m2;
	 for (int i = k; i <= m; i++) {
		 it1 = ccc1->Tsx.find(i);// M.at(m1).Tasks.find(m1Comp[j]);
		 it2 = ccc2->Tsx.find(i);
		 m1 = it1->second;
		 m2 = it2->second;

		 PassTask(ccc1, i, m1, m2);
		 PassTask(ccc2, i, m2, m1);
		 it1->second = m2;
		 it2->second = m1;
	 }
	 ccc1->SolTime = ccc1->Mchnz.at(0)->TasksTime;
	 ccc2->SolTime = ccc2->Mchnz.at(0)->TasksTime;

	 //update sol time
	 for (int i = 1; i < ccc1->Mchnz.size();i++) {
		 if (ccc1->Mchnz.at(i)->TasksTime > ccc1->SolTime)
			 ccc1->SolTime = ccc1->Mchnz.at(i)->TasksTime;

		 if (ccc2->Mchnz.at(i)->TasksTime > ccc2->SolTime)
			 ccc2->SolTime = ccc2->Mchnz.at(i)->TasksTime;
		
		
	 }

	 //update survival ,lower/upper bound

	 if (  (ccc1->SolTime < bestSol)) {
		 bestSol = ccc1->SolTime;
		 delete survival;
		 survival = new Chromosome(*ccc1);
	 }
	 if (ccc1->SolTime > newworsSol)
		 newworsSol = ccc1->SolTime;

	  

	 if ((ccc2->SolTime < bestSol)) {
		 bestSol = ccc2->SolTime;
		 delete survival;
		 survival = new Chromosome(*ccc2);
	 }
	 if (ccc2->SolTime > newworsSol)
		 newworsSol = ccc2->SolTime;

	 NextGen.push_back(ccc1);
	 NextGen.push_back(ccc2);


 }
 void Pairing(Chromosome* cm1 , Chromosome* cm2) {
	 int k,m;
	 int m1, m2, tmp;
	// Chromosome* res1 = new	Chromosome();
	 //Chromosome* res2 = new	Chromosome();
	 k = (rand() % (J.size())) ;
	 m = (rand() % (J.size() )) ;
	 if (m < k)
	 {
		 tmp = k;
		 k = m;
		 m = tmp;
	 }
#ifdef _dontChangeAll
	 if ((m - k) == (J.size() - 1))// we dont want to change all
	 {
		 k++;
		 m--;
	 }
#endif
	 pmx(cm1, cm2, k, m);

	  


 }
 int PeakRandomIndex(std::vector<double> fm, double max) {
	 double x = ((double)rand() / (RAND_MAX + 1)) ;
	 x = x * max;
	 int index = fm.size() / 2;
	 int low = 0;
	 int hight = fm.size();
	 bool con = true;
	 while (con) {
		 if ((hight - low) <= 1)
			 return index;
		 if((x<=fm.at(index))&& (x > fm.at(index-1)))
			 return index;
		 if (x > fm.at(index)) {
			 low = index;
			 index = (low + hight) / 2;
		 }
		 else
		 {
			 hight = index;
			 index = (low + hight) / 2;
		 }

		 
	 }
 }
 double TargetFunction(int x,int i) {
	 int j;
	 double Y;
	 switch (x) {
	 case 1:
		 Y = Gen.at(i)->SolTime;
		 return 1 / Y;


		 break;
	 case 2:
		 Y = Gen.at(i)->SolTime;
		 return 1 / (Y*Y);


		 break;
	 case 3:
		 Y = Gen.at(i)->SolTime;
		 return 1 / sqrtf(Y);


		 break;
	 case 4:
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf(Y, 3.0);
		 break;
	 case 5:
		 Y = Gen.at(i)->SolTime;
		 return 1 / (2 * Y - XX);
		 break;
		 // 6.  f(Y)= 1/(Y-X+1)
	 case 6:
		 Y = Gen.at(i)->SolTime;
		 return 1 / (Y - XX + 1);
		 break;

		 //7.  f(Y)=1/(3*Y-2*X)
	 case 7:
		 Y = Gen.at(i)->SolTime;
		 return 1 / ((3 * Y) - (2 * XX));
		 break;
		 //8. f(Y)= 1/(Y-X+1)^2

	 case 8:
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf((Y - XX + 1), 2.0);
		 break;
	 case 9:
		 // 9.  f(Y)=1/(Y-X+1)^3
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf((Y - XX + 1), 3.0);
		 break;

		 //10.  f(Y)=1/(Y-X+1)^0.5

	 case 10:
		 Y = Gen.at(i)->SolTime;
		 return 1 / sqrtf(Y - XX + 1);
		 break;

	 case 11:
	 {
		 double t = ((double)Gen.at(i)->SolTime / (double)worsSol);
		 return (1.0 - powf(t, 3.0));
		 break;
	 }


	 case 12:
	 {
		 Y = Gen.at(i)->SolTime;
		 double temp = 1 - (1 / (Y - XX));
		 return temp;
		 break;

	 }

	 case 13:
	 {
		 Y = Gen.at(i)->SolTime;
		 double temp = (1 / (Y - XX));
		 return 1 - powf(temp, 12);
		 break;

	 }

	 case 14:
	 {//how many machines far from the best sol in abs (calc the distribution) if they far we give it good greade

		 int sum = 0;
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 sum += powf((Gen.at(i)->Mchnz.at(j)->TasksTime - XX), 2.0);
		 return 1 - (1.0 / sum);
	 }
	 case 15:
	 {//how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade

		 int sum = 0;
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 sum += powf((Gen.at(i)->Mchnz.at(j)->TasksTime - XX), 2.0);
		 return  (1.0 / sum);
	 }

	 case 16:
	 {//how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double a, b, c, d, e, res;
		 int min, max, minM;
		 minM = Gen.at(i)->Mchnz.at(0)->speed;
		 min = Gen.at(i)->Mchnz.at(0)->TasksTime;
		 max = Gen.at(i)->Mchnz.at(0)->TasksTime;
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++) {
			 if (Gen.at(i)->Mchnz.at(j)->speed < minM)
				 minM = Gen.at(i)->Mchnz.at(j)->speed;
			 if (Gen.at(i)->Mchnz.at(j)->TasksTime < min)
				 min = Gen.at(i)->Mchnz.at(j)->TasksTime;
			 if (Gen.at(i)->Mchnz.at(j)->TasksTime > max)
				 max = Gen.at(i)->Mchnz.at(j)->TasksTime;
		 }
		 //a hold median
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 timeTemp.push_back((double)Gen.at(i)->Mchnz.at(j)->TasksTime / max);
		 std::sort(timeTemp.begin(), timeTemp.end());
		 a = timeTemp.at((Gen.at(i)->Mchnz.size()) / 2);
		 b = 0;//b hold normilaizd norm2 dist from median 
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 b += powf((timeTemp.at(j) - a), 2.0);//0.02 moution
		 b = Gen.at(i)->Mchnz.size() / b;
		 //C hold how many distance bettwen ratio
		// c = powf(((max - min) / ((tsum/minM) - XX)), 2.0);
		//c = (max - min) / ((tsum / minM) - XX);
		 c = 1 / powf((((tsum / minM) - XX) - (max - min) + 1), 2.0);
		 Y = Gen.at(i)->SolTime;
		 d = 1 / powf((Y - XX + 1), 2.0);
		 e = 1 / powf(((a*max) - XX + 1), 2.0);
		 res = e * 0.4 + d * 0.3 + c * 0.00 + b * 0.3;
		 // res = 0.2*b + 0.8*c;
		 // res = 0.1*a + 0.9*d;
		 // a=  (1.0 / sum);
		 timeTemp.clear();
		 return  res;
	 }

	 case 17: {
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf((Y - XX + 1), 2.0);
		 break;
	 }
	 case 18: {

		 //how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double b, a;
		 int max = Gen.at(i)->Mchnz.at(0)->TasksTime;
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++) {
			  
			 if (Gen.at(i)->Mchnz.at(j)->TasksTime > max)
				 max = Gen.at(i)->Mchnz.at(j)->TasksTime;
		 }
		 //a hold median
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 timeTemp.push_back((double)Gen.at(i)->Mchnz.at(j)->TasksTime / max);
		 std::sort(timeTemp.begin(), timeTemp.end());
		 a = timeTemp.at((Gen.at(i)->Mchnz.size()) / 2);
		 b = 0;//b hold normilaizd norm2 dist from median 
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 b += powf((timeTemp.at(j) - a), 2.0);//0.02 moution
		 b = Gen.at(i)->Mchnz.size() / b;
		 return b;

	 }
	 case 19: {

		 //how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double b, a;

		 //a hold median
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 timeTemp.push_back((double)Gen.at(i)->Mchnz.at(j)->TasksTime);
		 std::sort(timeTemp.begin(), timeTemp.end());
		 a = timeTemp.at((Gen.at(i)->Mchnz.size()) / 2);
		 b = 1 / powf((a - XX + 1), 2.0);

		 return b;

	 }
	 }

 }
 void BuildNewGen(int xo) { 
	 //build PROBABILITY Table
	 std::vector<double> rind;
	 double t, total=0;
	 for (int i = 0; i < Gen.size(); i++) {
		 //t = (1 - ((double)Gen.at(i)->SolTime / (double)worsSol));
		 total = total + TargetFunction(xo, i);

	 }
	 for (int i = 0; i < Gen.size(); i++) {
		 t = (1 - ((double)Gen.at(i)->SolTime / (double)worsSol));
		 rind.push_back(TargetFunction(xo, i) / total);
	 }
	 for (int i = 1; i < Gen.size(); i++)
		 rind.at(i) = rind.at(i) + rind.at(i - 1);
	 rind.at(Gen.size() - 1) = 1;


	 int x, y, tmp;
	 double max = 1;
	 double factor;
	
	// while (rind.size() > 1) {
	 for (int i = 0; i < mutationNo; i++) {
		 x = PeakRandomIndex(rind, max);
		 mutation(Gen.at(x));
	 }
	 for(int i=0;i< ((population- mutationNo)/2);i++){
		 x = PeakRandomIndex(rind, max);
		 y = PeakRandomIndex(rind, max);
		 #ifdef _pairXdifY
		 while(y==x)
			 y = PeakRandomIndex(rind, max);
		#endif
		 Pairing(Gen.at(x), Gen.at(y));
	 }
	 worsSol = newworsSol;
	 for (int i = 0; i < population; i++)
		 delete Gen.at(i);
	 Gen.clear();
	 for (int i = 0; i < population; i++)
		 Gen.push_back(NextGen.at(i));
	 NextGen.clear();

 }
 void init_first_gen() {
	 int rtmp  ;
	  
	 for (int j = Bf; j <= Ef; j++) {
		 double total = 0;
		 Gen.clear();
	 for (int i = 0; i < population; i++)
	 {
		 Chromosome* a = new	Chromosome();
		 a->index = i;
		 std::vector<int> dist = GetrandomDistribution();
		 for (int j = 0; j < J.size(); j++)
			 CopyJ.push_back(Node(J.at(j).time, J.at(j).index));
		 for (int j = 0; j < dist.size(); j++) {
			 std::vector<Node> temp= ChooseRandomKtasks(dist.at(j));
			 a->Mchnz.push_back(new machin(M.at(j).speed, M.at(j).index));
			 for (int k = 0; k < temp.size(); k++) {
				 a->Mchnz.at(j)->Tasks.insert(std::pair<int,Node>(temp.at(k).index,temp.at(k)));
				 a->Tsx.insert(std::pair<int, int>(temp.at(k).index, j));
				 a->Mchnz.at(j)->TasksTime += temp.at(k).time / a->Mchnz.at(j)->speed;

				 a->Mchnz.at(j)->tasksidx.push_back(temp.at(k).index); 
			 }
			 if (a->Mchnz.at(j)->TasksTime > a->SolTime)
				 a->SolTime = a->Mchnz.at(j)->TasksTime;

 			 temp.clear();

		 }

		// CopyJ.clear();
		 if (bestSol == -1 || (a->SolTime < bestSol)) {
			 bestSol = a->SolTime;
			 delete survival;
			 survival = new Chromosome(*a);
		 }
		 if (a->SolTime > worsSol)
			 worsSol = a->SolTime;

		 Gen.push_back(a);


	 }
	 
		 std::string s = "../output/gen_func-" + std::to_string(j) + ".txt";

		 std::ofstream ff(s);
		 for (int i = 0; i < GenNo; i++) {

			 BuildNewGen(j);

			 if ((i % 40) == 0)
			 {
				 ff << "-----------------------------------------------------------------\n";
				 ff << "#################### GEN "; ff << i; ff << "######################\n";
				 ff << "-----------------------------------------------------------------\n";

				 ff << "survival time : "; ff << survival->SolTime; ff << "\n";
				 for (int j = 0; j < Gen.size(); j++)
				 {
					 ff << "Cromozom "; ff << j; ff << "time : "; ff << Gen.at(j)->SolTime; ff << "\n";
				 }

			 }
			 if (i < print_first) {

			 }
		 }
	 }
 	 
  }
 std::vector<int> GetrandomDistribution()
 {
	 int x = J.size(),temp;
	 std::vector<int> res;
	 for (int i = 0; i < M.size()-1; i++) {
		 if (x > 0)
			 temp = rand() % x;
		 else
			 temp = 0;
		  
		 res.push_back(temp);
		 x = x - temp;


	 }
	 if(x>0)
		 res.push_back(x);
	 else
		 res.push_back(0);

	 return res;
 }
 void print_report() {
	 std::ofstream myfile("../output/report.txt");
	 myfile << "Report\n";


	 myfile << "______________________________________________________________________________________________________________________\n";
	 int j = 0;
	  
	 for(int i=0;i< survival->Mchnz.size();i++){
	 myfile << "______________________________________________________________________________________________________________________\n";
	 myfile << "##########################\n";
	 myfile << "machine SPEED : ";  myfile << survival->Mchnz.at(i)->speed; myfile << '\n';
	 myfile << "machine index : "; myfile << survival->Mchnz.at(i)->index; myfile << '\n';
	 myfile << "tasks total time: "; myfile << (float)survival->Mchnz.at(i)->TasksTime/4; myfile << '\n';
	 myfile << "##########################\n";
	 std::map<int, Node>::iterator it;
	 for (it = survival->Mchnz.at(i)->Tasks.begin(); it != survival->Mchnz.at(i)->Tasks.end(); ++it){
	 //for (int k = 0; k < M.at(i).Tasks.size(); k++) {
		 if (j == 3) {
			 myfile << '\n';
			 j = 0;
		 }
		 myfile << "| task index: "; myfile << it->second.index; myfile << " \\ task time: "; myfile << it->second.time/4; myfile << " |";
		 j++;
	 }
	 myfile << '\n';
	 }
	 myfile.close();
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
	srand((unsigned)time(NULL));
	init_data();
	tsum = 0;
	msum = 0;
	for (int i = 0; i < J.size(); i++)
		tsum += J.at(i).time*4;
	for (int i = 0; i < M.size(); i++)
		msum += M.at(i).speed;
	XX = (double)tsum / (double)msum;
	init_first_gen();
	
	print_report();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
