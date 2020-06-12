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
#include "BBNode.h"
 
#define maxLevelSearch 2
int speeds [3] = { 1,2,4 };
std::vector<Node> J;
std::vector<machin> M;
void init_data();
void print_report();
int MinMachineTime, MaxMachineTime;
minheap** tasksHV;


void print_summary();
//std::vector<minheap*> machinesHV;
minheap** machinesHV;
//minheap* machinesROOT;
std::vector<std::pair<int, int> > tasks;
int UpperBound( );
void buildBBtree(  BBNode* cbn, int upBound);




void Branch_and_Bound();
int * d_nm;
int ** TasksTable;//we have on map index as key but on GetBestOfNxM we need elment on place i not with key i so we make array hold task key in place i for each machine
//for report
int ** swapCount;
//std::queue<BBNode*> m;
std::queue<BBNode*> todelete;
//std::vector<BBNode*> leafs;
BBNode* survival;
bool first = true;
bool dontstop;
int optimalsol;
//extend to class
int MinTask;
int nodescount = 0;
std::ofstream mm("../output/tport.txt");
int MinWorst;
int mxms;//max machine speed
int Msum;
int mms; //max machine speed
std::vector<int> uniqe;
std::vector<int>::iterator it;