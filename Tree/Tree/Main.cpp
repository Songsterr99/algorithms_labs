#include<iostream>
#include<fstream>

using namespace std;
class Tree {
private:
	struct Item {
		Item(int _key) :key(_key), lSon(NULL), rSon(NULL) {};
		Item *rSon, *lSon;
		int key;
	};
	Item *root;
public:
	Tree() {
		root = NULL;
	}
	bool Insert(int key) {
		Item **working = &root;
		while (*working) {
			/*if (key > working->key) {
				working = working->rSon;
			} else if(key < working->key) {
				working = working->lSon;
			} else {
				return false;
			}*/
		}
		*working = new Item(key);
		cout << root->key;
		return true;
	}
	int getKey() {
		return root->key;
	}
};


int main() {
	Tree workingTree;
	workingTree.Insert(3);
	system("pause");
	return 0;
}

