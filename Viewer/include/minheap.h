#pragma once
#include <stdio.h>
class minheap
{
public:
	int value;
	int index;//index in array
	minheap* right;
	minheap* left;
	minheap* father;
	int rightCount;
	int leftCount;


	minheap(int v, int ix):value(v),index(ix), right(NULL), left(NULL), father(NULL), rightCount(0),leftCount(0){}
	void insert(minheap* t,  minheap * newn);
	~minheap();

};


