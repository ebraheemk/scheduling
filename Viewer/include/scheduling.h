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
std::vector<minheap> tasksHV;
std::vector<minheap> machinesHV;
minheap* machinesROOT;