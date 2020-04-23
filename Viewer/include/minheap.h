#pragma once
#include <stdio.h>
#include <utility> 
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
	minheap( minheap&);
	void insert(minheap* t,  minheap * newn);
	std::pair <int, int> pop(minheap * t);
	void afterpop(minheap * t);
	void copy_heap(minheap* old, minheap* current);
	~minheap();

};


