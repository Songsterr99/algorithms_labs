#include<iostream>
#include<fstream>

using namespace std;
class Tree {
private:
	struct Item {
		Item(int _key) : height(0), key(_key), lSon(NULL), rSon(NULL) {};
		Item *rSon, *lSon;
		int key, height;
	};
	Item *root;
	int countHeight(Item** working) {
		if (*working == NULL){
			return 0;
		}
		else if (((*working)->rSon) == NULL &&  ((*working)->lSon) == NULL) {
			return (*working)->height = 0;
		}
		else if (countHeight(&((*working)->rSon)) >= countHeight(&((*working)->lSon))) {
			return (*working)->height = countHeight(&((*working)->rSon)) + 1;
		}
		else {
			return (*working)->height = countHeight(&((*working)->lSon)) + 1;
		}

	}
public:
	Tree() {
		root = NULL;
	}
	bool insert(int key) {
		Item **working = &root;
		while (*working) {
			if (key > (*working)->key) {
				working = &((*working)->rSon);
			} else if(key < (*working)->key) {
				working = &((*working)->lSon);
			} else {
				return false;
			}
		}
		*working = new Item(key);
		return true;
	}

	void countHeights() {
		countHeight(&root);
	}

	int getKey() {
		return root->height;
	}
};


int main() {
	Tree workingTree;
	workingTree.insert(5);
	workingTree.insert(7);
	workingTree.insert(9);
	workingTree.insert(6);
	workingTree.insert(10);
	workingTree.insert(11);
	workingTree.countHeights();
	cout << workingTree.getKey() << endl;
	system("pause");
	return 0;
}

