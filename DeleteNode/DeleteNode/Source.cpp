#include<iostream>
#include<fstream>

using namespace std;
class Tree {
private:
	struct Item {
		Item(int _key) : length(0), key(_key), lSon(NULL), rSon(NULL) {};
		Item *rSon, *lSon;
		int key, length;
	};
	Item *root;
	void destroyNodes(Item *node) {
		if (node) {
			destroyNodes(node->lSon);
			destroyNodes(node->rSon);
			delete node;
		}
	}
	void showNodes(ostream& fout, Item *node) {
		if (node) {
			fout << node->key << endl;
			showNodes(fout, node->lSon);
			showNodes(fout, node->rSon);
		}
	}
	void deleteComplicated(Item** working) {
		Item **current = working,
			*lSon = (*working)->lSon;
		working = &(*working)->rSon;
		if ((*working)->lSon == NULL) {
			*current = *working;
			(*current)->lSon = lSon;
		}
		else {
			while ((*working)->lSon) {
				working = &(*working)->lSon;
			}
			(*current)->key = (*working)->key;
			*working = (*working)->rSon;
		}
	}
public:
	Item** find(int key) {
		Item **working = &root;
		while (*working) {
			if (key > (*working)->key) {
				working = &((*working)->rSon);
			}
			else if (key < (*working)->key) {
				working = &((*working)->lSon);
			}
			else if(key == (*working)->key){
				return working;
			}
		}
		return working;
	}
	void deleteNode(int key) {
		Item **working = find(key);
		if (*working == NULL) {
			cout << "!" << endl;
			return;
		}
		if ((*working)->lSon == NULL && (*working)->rSon == NULL) {
			*working = NULL;
		}
		else if ((*working)->lSon == NULL) {
			*working = (*working)->rSon;
		}
		else if ((*working)->rSon == NULL) {
			*working = (*working)->lSon;
		}
		else {
			deleteComplicated(working);
		}
	}
	Tree() {
		root = NULL;
	}
	bool insert(int key) {
		Item **working = &root;
		while (*working) {
			if (key > (*working)->key) {
				working = &((*working)->rSon);
			}
			else if (key < (*working)->key) {
				working = &((*working)->lSon);
			}
			else{
				return false;
			}
		}
		*working = new Item(key);
		return true;
	}

	void Show(ostream& fout) {
		showNodes(fout, root);
	}

	~Tree() {
		destroyNodes(root);
	}
};

int main() {
	ifstream fin("input.txt");
	Tree workingTree;
	int deletedNode;
	fin >> deletedNode;
	fin.ignore();
	while (fin.peek() != EOF)
	{
		int a;
		fin >> a;
		workingTree.insert(a);
	}
	fin.close();
	ofstream fout("output.txt");
	workingTree.deleteNode(deletedNode);
	workingTree.Show(fout);
	fout.close();
	system("pause");
	return 0;
}
