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
	struct MaxLength
	{
		MaxLength() :key(0), length(0) {};
		int key, length;
	};
	Item *root;
	int deletedNode;
	MaxLength maxLength;

	int countHeight(Item** working) {
		if (*working == NULL){
			return 0;
		}

		int lSonHeight = countHeight(&((*working)->lSon)),
			rSonHeight = countHeight(&((*working)->rSon));
		countLength(lSonHeight, rSonHeight, **working);
		countMaxLength(**working);
		if (((*working)->rSon) == NULL &&  ((*working)->lSon) == NULL) {
			return 0;
		}
		else if (rSonHeight >= lSonHeight) {
			return rSonHeight + 1;
		}
		else {
			return lSonHeight + 1;
		}
	}

	void countLength(int lSonHeight, int rSonHeight, Item& current) {
		if (current.lSon == NULL && current.rSon == NULL) {
			current.length = 0;
		}
		else if (current.lSon == NULL || current.rSon == NULL) {
			current.length = lSonHeight + rSonHeight + 1;
		}
		else {
			current.length = lSonHeight + rSonHeight + 2;
		}
	}

	void countMaxLength(Item& current) {
		if (current.length > maxLength.length) {
			maxLength.key = current.key;
			maxLength.length = current.length;
		}
		else if (current.length == maxLength.length && current.key < maxLength.key) {
			maxLength.key = current.key;
			maxLength.length = current.length;
		}

	}

	void destroyNode(Item *node) {
		if (node) {
			destroyNode(node->lSon);
			destroyNode(node->rSon);
			delete node;
		}
	}

	Item** find(int key) {
		Item **working = &root;
		while (*working) {
			if (key > (*working)->key) {
				working = &((*working)->rSon);
			}
			else if (key < (*working)->key) {
				working = &((*working)->lSon);
			}
			else {
				return working;
			}
		}
		return working;
	}
	void showNodes(ostream& fout, Item *node) {
		if (node) {
			fout << node->key << endl;
			showNodes(fout, node->lSon);
			showNodes(fout, node->rSon);
		}
	}
	Item** searchRight(Item** specNode) {
		Item** current = specNode;
		while (*specNode) {
			if ((*specNode)->lSon != NULL) {
				return searchShortLeft(&((*specNode)->lSon));
			}
			else if ((*specNode)->lSon == NULL) {
				specNode = &((*specNode)->rSon);
			}
		}
		if ((*current)->key < deletedNode) {
			deletedNode = (*current)->key;
		}
		return current;
	}

	Item** searchShortLeft(Item** specNode) {
		while ((*specNode)->lSon != NULL) {
			if ((*specNode)->rSon != NULL && ((*specNode)->lSon)->length < ((*specNode)->rSon)->length) {
				break;
			}
			else {
				specNode = &((*specNode)->lSon);
			}
		}
		return specNode;
	}

	Item** searchLeft(Item** specNode) {
		while (((*specNode)->lSon)->lSon != NULL) {
			if (((*specNode)->lSon)->rSon != NULL && (((*specNode)->lSon)->lSon)->length < (((*specNode)->lSon)->rSon)->length) {
				break;
			}
			else {
				specNode = &((*specNode)->lSon);
			}
		}
		return specNode;
	}
	void turnLeft(Item** specNode) {
		Item **current = searchLeft(specNode);
		if (((*current)->lSon)->rSon != NULL) {
			current = &(((*current)->lSon)->rSon);
			if ((*current)->lSon != NULL){
				current = searchShortLeft(&(*current)->lSon);
			}
		}
		deletedNode = (*current)->key;
	}
	void turnRight(Item** specNode) {
		deletedNode = ((*specNode)->rSon)->key;
		Item** another = searchRight(&((*specNode)->rSon));
		deletedNode = (*another)->key;
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

	void findDeletedNode() {
		Item **specNode = find(maxLength.key);
		if ((*specNode)->lSon != NULL) {
			turnLeft(specNode);
		}
		else {
			turnRight(specNode);
		}
		deleteNode(deletedNode);
	}
	
	void Show(ostream& fout) {
		showNodes(fout, root);
	}
	int getKey() {
		return deletedNode;
	}
	~Tree() {
		destroyNode(root);
	}
};

int main() {
	ifstream fin("in.txt");
	Tree workingTree;
	while (fin.peek() != EOF)
	{
		int a;
		fin >> a;
		workingTree.insert(a);
	}
	fin.close();
	workingTree.countHeights();
	workingTree.findDeletedNode();
	ofstream fout("out.txt");
	workingTree.Show(fout);
	fout.close();
	system("pause");
	return 0;
}

