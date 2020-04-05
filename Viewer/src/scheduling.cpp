
 #include <iostream>
#include <cstdlib>
#include "scheduling.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#define getcwd _getcwd
void init_machines() {

	//heap insert log(n) and sorted array insert log(n) so i go in sorted array 
	//first we add one task for each machine
	//for (int i = 0; i < M.size(); i++) {
 	//	M.at(i).Tasks.push_back(J.back);
	//	J.pop_back();


	//}
	minheap tasks = minheap(J.at(0).time, 0);
	for (int i = 1; i < J.size(); i++) {
		minheap temp = minheap(J.at(i).time, i);
		tasks.insert(&tasks, &temp);
	}

}
 void init_data() {
	 std::string line;
	 std::ifstream myfile("tasks.txt");
	 if (myfile.is_open())
	 {
		 while (std::getline(myfile, line))
		 {
 			 J.push_back(Node(std::stoi(line)));
		 }
		 myfile.close();
	 }

	 std::ifstream myfile2("machines.txt");

	 if (myfile2.is_open())
	 {
		 while (std::getline(myfile2, line))
		 {
			 M.push_back(machin(std::stoi(line)));
		 }
		 myfile2.close();
	 }

 		 

	


}
int main()
{
	//std:://qDebug() << "printing value: " << std::QString(MY_VAR);
	init_data();
	init_machines();
    std::cout << "Hello World!\n "; 
	system("pwd");
	for (int i = 0; i < M.size(); i++)
		printf(" machin:%d  speed:%d", i, M.at(i).speed);
	printf("\n Tasks :\n");
	for (int i = 0; i < J.size(); i++)
		printf(" %d ,",  J.at(i).time);
}
