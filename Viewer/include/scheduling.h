#pragma once
#include <vector>
#include "Node.h"
#include "machin.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#define MachineNum 5
#define taskNum 20
#define maxJopTime 50
int speeds [3] = { 1,2,4 };
std::vector<Node> J;
std::vector<machin> M;
void init_data();
