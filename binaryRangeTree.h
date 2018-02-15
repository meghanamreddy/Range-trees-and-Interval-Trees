#include <iostream>
#include <cstdlib>
#include <vector>
# ifndef BinaryRangeTree_H
# define BinaryRangeTree_h
using namespace std;


class BinaryRangeTree;
class Line;

/* Class BinaryRangeNode */

class BinaryRangeNode
{
    public:
        int height, data;
	vector<int> data2;
        BinaryRangeNode *left, *right;
	BinaryRangeTree *ytree;
	vector<Line*> lines;
         /* Constructor */
         BinaryRangeNode()
         {
             left = NULL;
             right = NULL;
             data = 0;
			 ytree = NULL;
             height = 0;
         }
 
         /* Constructor */
         BinaryRangeNode(int n, int m, Line *l)
         {
             left = NULL;
             right = NULL;
             data = n;
			 ytree = NULL;
			 data2.push_back(m);
             height = 0;
			 lines.push_back(l);
         }
};


/*
 * Class BinaryRangeTree
 */
 
class BinaryRangeTree
{
    private:
        BinaryRangeNode *root;
    public:
		
         /* Constructor */
		BinaryRangeTree()
        {
        	root = NULL;
        }
	bool isEmpty();
	void makeEmpty();
	void insert(int data, int data2,  Line *l);	
	int height(BinaryRangeNode *t);
	int max(int lhs, int rhs);
	BinaryRangeNode *insert(int x, int y, BinaryRangeNode *t,  Line *l);
	BinaryRangeNode *rotateWithLeftChild(BinaryRangeNode* k2);
	BinaryRangeNode *rotateWithRightChild(BinaryRangeNode *k1);
	BinaryRangeNode *doubleWithLeftChild(BinaryRangeNode *k3);
	BinaryRangeNode *doubleWithRightChild(BinaryRangeNode *k1);
	int countNodes();
	int countNodes(BinaryRangeNode *r);
	bool search(int val);
	bool search(BinaryRangeNode *r, int val);
	void inorder();
	void inorder(BinaryRangeNode *r);
	void preorder();
	void preorder(BinaryRangeNode *r);
	void postorder();
	void postorder(BinaryRangeNode *r);
	void buildytrees();
	void buildytrees(BinaryRangeNode *r);
	void buildytrees(BinaryRangeNode *r,  BinaryRangeTree* temp_tree);
	void printytree();
	void onedquery(int x1, int x2);
	BinaryRangeNode* findSplitNode(BinaryRangeNode* tree, int x1, int x2);
	BinaryRangeNode* findSplitNodeYtree(BinaryRangeNode* tree, int x1, int x2);
	void reportSubtree(BinaryRangeNode *r);
	bool isLeaf(BinaryRangeNode* r);
	void twodquery(int x1, int x2, int y1, int y2);
	void onedqueryYtree(BinaryRangeTree *r, int x1, int x2);
	void reportPoint(BinaryRangeNode *r);
	void reportPointYtree(BinaryRangeNode *r);
	void isPointInRange(BinaryRangeNode* r, int x1, int x2, int y1, int y2);
	BinaryRangeTree* buildRangeTree(vector<Line> lines, BinaryRangeTree* sbbst);
	BinaryRangeTree* buildRangeTreeEndPoints(BinaryRangeTree *sbbst, vector<Line*> lines);
	BinaryRangeTree* buildRangeTree2(BinaryRangeTree *sbbst, vector<Line*> lines);
};

#endif
