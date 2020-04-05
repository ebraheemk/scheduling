#include "minheap.h"



minheap::minheap(int value, int index)
{
	
}
 void minheap::insert(minheap * t, minheap * newn) {
	//minheap t = minheap(v, ix);
	 int tempix, tempval;
 	if (t->rightCount > 0 && t->leftCount > 0 && t->leftCount <= t->rightCount) {
		t->leftCount = t->leftCount + 1;
		insert(t->left, newn);
	}
	else if (t->rightCount > 0 && t->leftCount > 0 ) {
		t->rightCount = t->rightCount + 1;
		insert(t->right, newn);
	}
	else if (t->leftCount == 0) {
		t->left = newn;
		newn->father = t;

		if (newn->value < newn->father->value) {
			tempix = newn->index;
			tempval = newn->value;
			newn->index = newn->father->index;
			newn->value = newn->father->value;
			newn->father->index = tempix;
			newn->father->value = tempval;
		}
	}
	else {
		t->right = newn;
		newn->father = t;

		if (newn->value < newn->father->value) {
			tempix = newn->index;
			tempval = newn->value;
			newn->index = newn->father->index;
			newn->value = newn->father->value;
			newn->father->index = tempix;
			newn->father->value = tempval;
		}
	}
	if (t->value < t->father->value) {
		tempix = t->index;
		tempval = t->value;
		t->index = t->father->index;
		t->value = t->father->value;
		t->father->index = tempix;
		t->father->value = tempval;
	}

}


minheap::~minheap()
{
}
