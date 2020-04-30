#pragma once
#include <vector>
#include "Node.h"
#include "machin.h"
#include "minheap.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <maxheap.h>
#define MachineNum 5
#define taskNum 20
#define maxJopTime 50
int speeds [3] = { 1,2,4 };
std::vector<Node> J;
std::vector<machin> M;
void init_data();
void init_machines(); 
void print_report();
int MinMachineTime, MaxMachineTime;
void SwapTasks(int task1, int machine1, int task2, int machine2);
void PassTask(int task, int machine1, int machine2);
minheap** tasksHV;
bool TwoMachineLocalSearch(int machine1, int  machine2);
bool M1ToM2Throw(int machine1, int  machine2);
std::pair<int,int> GetBestSolOfTwo(int machine1, int  machine2);
int GetBestThrow(int machine1, int  machine2);

bool LevelOne();
bool LevelZero();
void LocalSearch();
void SwapmTasks(std::vector<int> t1, int m1, std::vector<int>t2, int m2);
void GetBestOf1xM(int m1Comp[],int m1,int m2,int m2tasksNo, int index, int comb[], int i, bool firsttime);/*given compination of machine1 finde the bes compination of M tasks that
give best solution if we swap given compinatin from machine1 and the M tasks from machine2  */
void GetBestOfNxM(int m1,int m1tasksNo ,int m2,int m2tasksNo,int index,int comb[],int i,bool firsttime);/*we want to do local search NxM first we go over N compenation of machine1
and for each compination we call getbest1xm wich take compenation from machine 1 and find best
compination from machine2 
*/
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