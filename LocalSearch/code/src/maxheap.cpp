#include "maxheap.h"
using namespace std;
/*#########################!!
###########################!!!!!!!!	SHOULD BE TESTED
###########################!!!*/
void maxheap::afterpop(maxheap * t) {
	if (t->right != NULL && t->left != NULL) {
		if (t->right->value < t->left->value) {
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
	else if (t->right != NULL) {
		t->value = t->right->value;
		t->index = t->right->index;
		afterpop(t->right);
	}
	else if (t->left != NULL) {
		t->value = t->left->value;
		t->index = t->left->index;
		afterpop(t->left);
	}
	else {
		t->value = -1;
		t = t->father;

		if (t->right != NULL)
			if (t->right->value == -1)
				t->right = NULL;

		if (t->left != NULL)
			if (t->left->value == -1)
				t->left = NULL;
	}
}
std::pair <int, int> maxheap::pop(maxheap * t) {
	//int tval, tindx;
	pair<int, int> result;
	result.first = t->value;
	result.second = t->index;
	afterpop(t);

	return result;
}
void maxheap::insert(maxheap * t, maxheap * newn) {
	//minheap t = minheap(v, ix);
	int tempix, tempval;
	if ((t->leftCount > 0) && (t->leftCount <= t->rightCount)) {
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

				if (newn->value > newn->father->value) {
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

				if (newn->value > newn->father->value) {
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
	if (t->father != NULL)
		if (t->value > t->father->value) {
			tempix = t->index;
			tempval = t->value;
			t->index = t->father->index;
			t->value = t->father->value;
			t->father->index = tempix;
			t->father->value = tempval;
		}

}


maxheap::~maxheap()
{
}
