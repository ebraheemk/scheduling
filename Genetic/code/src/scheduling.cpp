
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
		 break;

	 }

	 case 16:
	 {//how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double a, b, c, d, e, res;
		 std::vector<double> timeTemp;
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
		 b = b/Gen.at(i)->Mchnz.size()  ;
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
		 timeTemp.shrink_to_fit();

		 return  res;
		 break;

	 }

	 case 17: {
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf((Y - XX + 1), 2.0);
		 break;
	 }
	 case 18:
		 // 9.  f(Y)=1/(Y-X+1)^3
		 Y = Gen.at(i)->SolTime;
		 return 1 / powf((Y - XX + 1), 3.0);
		 break;

		 //10.  f(Y)=1/(Y-X+1)^0.5

	 case 19:
		 Y = Gen.at(i)->SolTime;
		 return 1 / sqrtf(Y - XX + 1);
		 break;
	 case 20: {

		 //how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double b, a;
		 std::vector<double> timeTemp;
		 //a hold median
		 for (int j = 0; j < Gen.at(i)->Mchnz.size(); j++)
			 timeTemp.push_back((double)Gen.at(i)->Mchnz.at(j)->TasksTime);
		 std::sort(timeTemp.begin(), timeTemp.end());
		 a = timeTemp.at((Gen.at(i)->Mchnz.size()) / 2);
		 b = 1 / powf((a - XX + 1), 2.0);
		 timeTemp.clear();
		 timeTemp.shrink_to_fit();
		 return b;
		 break;

	 }
	 case 21: {

		 //how many machines far from the best sol in abs (calc the distribution) if they far we give it less greade
		 double b, a;
		 std::vector<double> timeTemp;
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
		// b = b/ Gen.at(i)->Mchnz.size()  ;
		 timeTemp.clear();
		 timeTemp.shrink_to_fit();

		 return b;
		 break;

	 }
	 }

 }
 void BuildNewGen(int xo) { 
	 //build PROBABILITY Table
	 std::vector<double> rind;
	 double t, total=0;
	 for (int i = 0; i < Gen.size(); i++) {
		 //t = (1 - ((double)Gen.at(i)->SolTime / (double)worsSol));
		 double d = TargetFunction(xo, i);
		   d = TargetFunction(xo, i);


		 total = total + TargetFunction(xo, i);

	 }
	 for (int i = 0; i < Gen.size(); i++) {
		// t = (1 - ((double)Gen.at(i)->SolTime / (double)worsSol));
		  double d = TargetFunction(xo, i);
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
		 if (printc) {
			 Pair << "mutation <-- ";	Pair << x;	 Pair << "\n";
		 }
		 mutation(Gen.at(x));
	 }
	 for(int i=0;i< ((population- mutationNo)/2);i++){
		 x = PeakRandomIndex(rind, max);
		 y = PeakRandomIndex(rind, max);
		 #ifdef _pairXdifY
		 int coco = 0;
		 while (y == x) {
			 y = PeakRandomIndex(rind, max);
			 if (coco >= 4) {
				 int fj = rand() % 2;
				 if (fj == 0)
					 fj = -1;
				  
					 y = x + fj;
					 if (y == rind.size())
						 y--;
					 if (y == x)
						 y--;
					 if (y < 0)
						 y++;
				 }
			 }
		 
		#endif
		 if (printc) {
			 Pair << "Pairing "; Pair << x; Pair << " <--> "; Pair << y; Pair << "\n";
		 }
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
			 if (i < print_first) {
				 print_Gen(i, j);
				 Pair << "_-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-_\n";
				 Pair << "_-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-_\n\n";
				 Pair << "function : "; Pair << j; Pair << "\n";
				 Pair << "Gen :"; Pair << i; Pair << "\n";
				 Pair << "_________________________________________________________________________\n";
				 Pair << "_________________________________________________________________________\n";
				 printc = true;
			 }
			 else
				 printc = false;

			 

			 BuildNewGen(j);

			 if ((i % 40) == 0)
			 {
				 ff << "-----------------------------------------------------------------\n";
				 ff << "#################### GEN "; ff << i; ff << "######################\n";
				 ff << "-----------------------------------------------------------------\n";

				 ff << "survival time : "; ff << survival->SolTime/4; ff << "\n";
				 for (int j = 0; j < Gen.size(); j++)
				 {
					 ff << "Cromozom "; ff << j; ff << "time : "; ff << Gen.at(j)->SolTime/4; ff << "\n";
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
 void print_Gen(int g,int fun) {
	 std::string s = "../output/full_func-" + std::to_string(fun)+"_gen_"+ std::to_string(g) + ".txt";
	 
	 std::ofstream print_Chromosome(s);
	 print_Chromosome << "Report\n";
	 for (int k = 0; k < population; k++)
	 {
		 print_Chromosome << "\n";
		 print_Chromosome << "\n";
		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
 		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
		 
		 print_Chromosome << "################# Chromosome "; print_Chromosome << k; print_Chromosome << "\n";
		 
		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
		 print_Chromosome << "______________________________________________________________________________________________________________________\n";
		 print_Chromosome << "\n";
		 print_Chromosome << "\n";
		 int j = 0;

		 for (int i = 0; i < Gen.at(k)->Mchnz.size(); i++) {
			 print_Chromosome << "______________________________________________________________________________________________________________________\n";
			 print_Chromosome << "##########################\n";
			 print_Chromosome << "machine SPEED : ";  print_Chromosome << Gen.at(k)->Mchnz.at(i)->speed; print_Chromosome << '\n';
			 print_Chromosome << "machine index : "; print_Chromosome << Gen.at(k)->Mchnz.at(i)->index; print_Chromosome << '\n';
			 print_Chromosome << "tasks total time: "; print_Chromosome << (float)Gen.at(k)->Mchnz.at(i)->TasksTime / 4; print_Chromosome << '\n';
			 print_Chromosome << "##########################\n";
			 std::map<int, Node>::iterator it;
			 for (it = Gen.at(k)->Mchnz.at(i)->Tasks.begin(); it != Gen.at(k)->Mchnz.at(i)->Tasks.end(); ++it) {
				 //for (int k = 0; k < M.at(i).Tasks.size(); k++) {
				 if (j == 3) {
					 print_Chromosome << '\n';
					 j = 0;
				 }
				 print_Chromosome << "| task index: "; print_Chromosome << it->second.index; print_Chromosome << " \\ task time: "; print_Chromosome << it->second.time / 4; print_Chromosome << " |";
				 j++;
			 }
			 print_Chromosome << '\n';
		 }
	 }
	 print_Chromosome.close();
 }
 void print_report() {
	 std::ofstream myfile("../output/Result.txt");
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

 
 

 
 
int main()
{
	auto start = high_resolution_clock::now();

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
