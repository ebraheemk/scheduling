#pragma once
#include <stdio.h>
#include <utility> 
class maxheap
{
public:
	int value;
	int index;//index in array
	maxheap* right;
	maxheap* left;
	maxheap* father;
	int rightCount;
	int leftCount;
	maxheap(int v, int ix) :value(v), index(ix), right(NULL), left(NULL), father(NULL), rightCount(0), leftCount(0) {}
	maxheap(maxheap&);
	void insert(maxheap* t, maxheap * newn);
	std::pair <int, int> pop(maxheap * t);
	void afterpop(maxheap * t);
	maxheap * GetRight() { return this->right; }
	maxheap * GetLeft() { return this->left; }
	maxheap * GetFather() { return this->father; }
	void copy_heap(maxheap* old, maxheap* current);

	~maxheap();

};

