
 #include <iostream>
#include <cstdlib>
#include "scheduling.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#define getcwd _getcwd
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
    std::cout << "Hello World!\n "; 
	system("pwd");
	for (int i = 0; i < M.size(); i++)
		printf(" machin:%d  speed:%d", i, M.at(i).speed);
	printf("\n Tasks :\n");
	for (int i = 0; i < J.size(); i++)
		printf(" %d ,",  J.at(i).time);
}
