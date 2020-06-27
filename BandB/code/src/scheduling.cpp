
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

		for (k = 0; k < Mcopy.at(j).speed && i < J.size(); k++, i++) {
			minheap* copy = &tasks;
			if (i != J.size() - 1)
				p = tasks.pop(copy);
			else {
				p.first = tasks.value;
				p.second = tasks.index;
			}

			Mcopy.at(j).TasksTime += p.first / Mcopy.at(j).speed;
			Mcopy.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}
	std::vector<machin> Mcopy2;

	int minm, maxm;
	minm = Mcopy.at(0).TasksTime;
	maxm = Mcopy.at(0).TasksTime;
	for (i = 0; i < M.size(); i++) {
		if (Mcopy.at(i).TasksTime < minm)
			minm = Mcopy.at(i).TasksTime;
		if (Mcopy.at(i).TasksTime > maxm)
			maxm = Mcopy.at(i).TasksTime;
	}
	printf("minmum1 hmdan m %d", minm);
	maxheap tasks2 = maxheap(J.at(0).time * 4, 0);
	maxheap* copy2 = &tasks2;
	for (i = 1; i < J.size(); i++) {
		tasks2.insert(copy2, new maxheap(J.at(i).time * 4, i));
	}
	for (int i = 0; i < M.size(); i++)
		Mcopy2.push_back(M.at(i));

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for (k = 0; k < Mcopy2.at(j).speed && i < J.size(); k++, i++) {
			maxheap* copy2 = &tasks2;
			if (i != J.size() - 1)
				p = tasks2.pop(copy2);
			else {
				p.first = tasks2.value;
				p.second = tasks2.index;
			}

			Mcopy2.at(j).TasksTime += p.first / Mcopy2.at(j).speed;
			Mcopy2.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}

	for (i = 0; i < M.size(); i++) {

		if (Mcopy2.at(i).TasksTime > minm)
			minm = Mcopy2.at(i).TasksTime;
	}
	maxm = fmin(minm, maxm);//minm now is maxmum not minmum
	printf("maximum hmdan m %d", maxm);

	return maxm;
}



bool sortbyfir(const std::pair<int, BBNode*> &a,
	const std::pair<int, BBNode*> &b)
{
	return (a.first < b.first);
}


int CalcWorstTime(BBNode* ek) {
	int minIdx,max;
	for (int i = 0; i < M.size(); i++)
		MachTemp[i] = ek->machinesTime[i];
	//((tasks.at(cbn->deapth).first) / M.at(k).speed)
	int tt;
	for (int i = ek->deapth; i < tasks.size(); i++) {
		//find minmum machine
		tt = tasks.at(i).first;
		minIdx = 0;
		for (int j = 1; j < M.size(); j++) {
			if ((MachTemp[j]+(tt/M.at(j).speed)) < (MachTemp[minIdx]+ (tt / M.at(minIdx).speed)))
				minIdx = j;
			 
		}
		MachTemp[minIdx] += (tt / M.at(minIdx).speed);
	}
	max = MachTemp[0];
	for (int i = 1; i < M.size(); i++)
		if (MachTemp[i] > max)
			max = MachTemp[i];
	return max;
}
void buildBBtree(  BBNode*  cbn, int upBound) {
	nodescount++;
	int sum, tmf,minMt;
	while (!todelete.empty()) {
		BBNode* dd = todelete.front();
		todelete.pop();
		delete dd;
	
		 
		}
	//}

	int temp, totaltasktime = 0;
	if (cbn->deapth == tasks.size() ) {
		mm << "\nsol task time : "; mm << cbn->taskstime / 4; mm << "\n";
		for (int i = 0; i < cbn->Mi.size(); i++)
		{
			mm << "| M = "; mm << cbn->Mi.at(i).first; mm << " task index= "; mm << cbn->Mi.at(i).second; mm << "|";
		}

		if (first) {
			survival = cbn;
			first = false;
		}
		else {
			if (cbn->taskstime < survival->taskstime) {
				delete survival;
				survival = cbn;
			}
			else
				delete cbn;

		}
		//delete cbn;
		//leafs.push_back(cbn);
		if (survival->taskstime < MinWorst)
			MinWorst = survival->taskstime;
		if (survival->taskstime <= optimalsol)
			dontstop = false;
		 
	}
	else if ((cbn->deapth < tasks.size())&& dontstop) {
		std::vector<std::pair<int, BBNode*>> tempo;
		for (int k = 0; k < M.size(); k++)
		{
			BBNode* ek = new BBNode();
			ek->deapth = cbn->deapth + 1;
			ek->machinesTime = (int*)malloc(sizeof(int)*M.size());
			 
			for (int i = 0; i < k; i++) {
				ek->machinesTime[i] = cbn->machinesTime[i];
 			}
			ek->machinesTime[k] = cbn->machinesTime[k] + ((tasks.at(cbn->deapth).first) / M.at(k).speed);
			for (int i = k + 1; i < M.size(); i++) {
						ek->machinesTime[i] = cbn->machinesTime[i];
 
				}
			 
			int x = ek->machinesTime[k];
			ek->taskstime = fmax(ek->machinesTime[k], cbn->taskstime);
			totaltasktime = 0;
			for(int i=0;i<M.size();i++)
				totaltasktime = totaltasktime + ((ek->taskstime - ek->machinesTime[i])*M.at(i).speed);

	

			temp = (int)((tasks.size() - cbn->deapth - 1) / M.size());

			ek->taskMachineRatio = temp / mxms;
			ek->Tsum = cbn->Tsum - tasks.at(cbn->deapth).first;

			 sum = 0;
			 for (int i = (tasks.size() - ek->taskMachineRatio); i < tasks.size(); i++)
				 sum = sum + tasks.at(i).first;
			 minMt = ek->machinesTime[0];
			 for (int i = 0; i < M.size(); i++)
			 {
				 if (minMt > ek->machinesTime[i])
					 minMt = ek->machinesTime[i];
			 }
			 tmf = fmax(((ek->Tsum - totaltasktime) / Msum), 0);
			ek->BestTiming = ek->taskstime +tmf;/*should add div max machine speed*/;
			ek->BestTiming = fmax(ek->BestTiming, (sum+ minMt));
		 


			for (int e = 0; e < cbn->Mi.size(); e++)
				ek->Mi.push_back(cbn->Mi.at(e));
			  
			ek->Mi.push_back(std::pair<int, int>(M.at(k).index, tasks.at(cbn->deapth).second));

			ek->worstTiming = CalcWorstTime(ek);
 			if (ek->worstTiming < MinWorst)
				MinWorst = ek->worstTiming;
			int toto = ek->machinesTime[k] * 10 + M.at(k).speed;
			it = find(uniqe.begin(), uniqe.end(), toto);
			if (it == uniqe.end() || uniqe.empty()) {
			//	cbn->m.push(ek);
				tempo.push_back(std::pair<int, BBNode*>(ek->taskstime, ek));
				uniqe.push_back(toto);
			}
			else
				todelete.push(ek);
		}
		uniqe.clear();
		//uniqe.shrink_to_fit();
		std::sort(tempo.begin(), tempo.end(), sortbyfir);
		for (int h = 0; h < tempo.size(); h++)
			cbn->m.push(tempo.at(h).second);

	    BBNode* nextcall;
		while (!cbn->m.empty()) {
			nextcall = cbn->m.front();
			cbn->m.pop();
			int lolo = fmin(MinWorst, upBound)+1;
			if (!first)
				lolo = survival->taskstime;
			if ((nextcall->BestTiming <= fmin(MinWorst, upBound))&&(nextcall->BestTiming<lolo))
				buildBBtree( nextcall, upBound);
			else
				todelete.push(nextcall);

			 
		}
		 
	       todelete.push(cbn);
 		 
		  

	}

}



/**/

void print_report() {
	std::ofstream myfile("../output/report.txt");
	myfile << "Report\n";
	myfile << "node count : "; myfile << nodescount; myfile << "\n";
	 

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

 void Branch_and_Bound() {
	// std::vector<Node> M = J;

	 int up = UpperBound();



	 int Tsum = 0, mmspeed;
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
	 MinTask = minTask;
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
	 mxms = tempmax;
	 mms=mmspeed;
	 int temp = (int)(J.size() / M.size());

	 int bt = fmax((Tsum / Msum), (int)(minTask*(double)(temp / tempmax)));//should change
	 MinWorst = Tsum/mms;

	BBNode A =  BBNode(0, (double)temp / (double)tempmax, 0, bt, Tsum, mmspeed, M.size());

	optimalsol = bt;
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


	 dontstop = true;
	  

	 buildBBtree( &A, up);
	 mm.close();
	// printf("\n&&%d&&&\n",leafs.size());

	/* BBNode* ServiverPath;
	 int min = leafs.at(0)->taskstime;
	 ServiverPath = leafs.at(0);
	 int mmtime;
	 for (int i = 0; i < leafs.size(); i++) {
			 if (leafs.at(i)->taskstime < min) {
				 min = leafs.at(i)->taskstime;
				 ServiverPath = leafs.at(i);
			 }
		 
	 }*/
	 printf("servival");
	 //insert from servival path to machines
	 for (int i = 0; i < survival->Mi.size(); i++)
	 {
		 M.at(survival->Mi.at(i).first).Tasks.insert(std::pair<int, Node>(survival->Mi.at(i).second, J.at(survival->Mi.at(i).second)));
		 M.at(survival->Mi.at(i).first).TasksTime +=  ((J.at(survival->Mi.at(i).second).time * 4) / M.at(survival->Mi.at(i).first).speed);

	 }
 	 //insert_soulution(A.ServiverPath);
	 //next go from leaf to root on servivel path and insert tasks into machines 
  }

int main()
{
	auto start = high_resolution_clock::now();
	
	//int sum = 0;
	
	init_data();
	 
	MachTemp = new int[M.size()];
	Branch_and_Bound();
	print_report();
	//print_summary();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count()/1000000.0 << std::endl;
}
