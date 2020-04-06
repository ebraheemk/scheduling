#include "minheap.h"


using namespace std;
void minheap::afterpop(minheap * t ){
	if (t->rightCount > 0 && t->leftCount > 0) {
		if (t->right->value > t->left->value) {
			t->value = t->left->value;
			t->index = t->left->index;
			afterpop(t->left);
		}
		else
		{
			t->value = t->right->value;
			t->index = t->right->index;
			afterpop(t->right);
		}
	}
	else if (t->rightCount>0) {
		t->value = t->right->value;
		t->index = t->right->index;
		afterpop(t->right);
	}
	else if (t->leftCount > 0) {
		t->value = t->left->value;
		t->index = t->left->index;
		afterpop(t->left);
	}
	else {
		t->value = -1;
		t = t->father;
		if (t->right->value == -1)
			t->right = NULL;
		else
			t -> left = NULL;
	}
}
std::pair <int, int> minheap::pop(minheap * t) {
	//int tval, tindx;
	pair<int, int> result;
	result.first = t->value;
	result.second = t->index;
	afterpop(t);

	return result;
}
 void minheap::insert(minheap * t, minheap * newn) {
	//minheap t = minheap(v, ix);
	 int tempix, tempval;
 	if (( t->leftCount > 0) && (t->leftCount <= t->rightCount)) {
		t->leftCount = t->leftCount + 1;
		insert(t->left, newn);
	}
	else {
		if (t->rightCount > 0 && (t->leftCount > t->rightCount)) {
			t->rightCount = t->rightCount + 1;
			insert(t->right, newn);
		}
		else {
			if (t->leftCount == 0) {
				t->left = newn;
				newn->father = t;
				t->leftCount = t->leftCount + 1;

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
				t->rightCount = t->rightCount + 1;

				if (newn->value < newn->father->value) {
					tempix = newn->index;
					tempval = newn->value;
					newn->index = newn->father->index;
					newn->value = newn->father->value;
					newn->father->index = tempix;
					newn->father->value = tempval;
				}
			}
		}
	}
	if(t->father!=NULL)
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
