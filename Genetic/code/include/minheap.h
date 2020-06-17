#pragma once
#include <stdio.h>
#include <utility> 
class minheap
{
public:
	int value;
	int index;//index in array
	int rightCount;
	int leftCount;


	minheap(int v, int ix):value(v),index(ix), right(NULL), left(NULL), father(NULL), rightCount(0),leftCount(0){}
	minheap( minheap&);
	void insert(minheap* t,  minheap * newn);
	std::pair <int, int> pop(minheap * t);
	void afterpop(minheap * t);
	void copy_heap(minheap* old, minheap* current);
	minheap * GetRight() { return this->right; }
	minheap * GetLeft() { return this->left; }
	minheap * GetFather() { return this->father; }

	~minheap();
private:
	minheap* right;
	minheap* left;
	minheap* father;

};


