#pragma once
#include <vector>
#include <algorithm>    // std::sort
#include "Node.h"
#include "machin.h"
#include "minheap.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <maxheap.h>
#include <Chromosome.h>
#define _dontChangeAll
#define _pairXdifY
#define print_first 5
#define population 100 //should be even number
#define mutationNo 4//should be even number
#define GenNo 50000
#define Bf 17
#define Ef 19 
int speeds [3] = { 1,2,4 };
std::vector<Node> J;
std::vector<machin> M;
void init_data();
 void print_report();
 

int MinMachineTime, MaxMachineTime;
 void PassTask(Chromosome*,int task, int machine1, int machine2);
minheap** tasksHV;
 
//std::vector<minheap*> machinesHV;
minheap** machinesHV;
//minheap* machinesROOT;
int MaxNxM;
int Max1xM;
std::vector<int> NxMcom1Best;
std::vector<int> NxMcom2Best;
std::vector<int> com2Best1xM;
bool GetBestOfNxMbool;
bool GetBestOf1xMbool;
int * d_nm;
int ** TasksTable;//we have on map index as key but on GetBestOfNxM we need elment on place i not with key i so we make array hold task key in place i for each machine
//for report
int ** swapCount;

//for genitic
std::vector<int> GetrandomDistribution();
std::vector<Node> ChooseRandomKtasks(int k);
std::vector<Node> CopyJ;

void init_first_gen();
std::vector<Chromosome*> Gen;
std::vector<Chromosome*> NextGen;

void Pairing(Chromosome*, Chromosome* );
std::vector<int> ChooseRandomKtasks(int k, machin* mch);
int bestSol=-1;
int worsSol = -1;
int newworsSol = -1;
int PeakRandomIndex( std::vector<double>,double);

Chromosome* survival;
int ccindex=0;
void pmx(Chromosome*, Chromosome*, int, int);
void BuildNewGen( int);
 std::ofstream ff ;
 std::ofstream allfirst;
 std::ofstream Pair("../output/Pairing_mutation_report.txt");


double TargetFunction(int,int);
int tsum;
int msum;
double XX;
void mutation(Chromosome*);
void print_Gen(int,int);
int peak_machine(int);
//std::vector<double> timeTemp;
bool printc;