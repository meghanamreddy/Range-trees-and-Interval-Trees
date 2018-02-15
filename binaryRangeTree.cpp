#include <iostream>
#include <cstdlib>
#include <vector>
#include "binaryRangeTree.h"
#include "line.h"
using namespace std;

/* range trees implemented */ 



/* Function to check if tree is empty */
bool BinaryRangeTree::isEmpty()
{
	return root == NULL;
}
 
/* Make the tree logically empty */
void BinaryRangeTree::makeEmpty()
{
	root = NULL;
}
 
/* Function to insert data */
void BinaryRangeTree::insert(int data, int data2, Line *l)
{
	root = insert(data, data2, root, l);
}
 
/* Function to get height of node */
int BinaryRangeTree::height(BinaryRangeNode *t)
{
	return t == NULL ? -1 : t->height;
}
 
/* Function to max of left/right node */
int BinaryRangeTree::max(int lhs, int rhs)
{
	return lhs > rhs ? lhs : rhs;
}
 
/* Function to insert data recursively */
BinaryRangeNode* BinaryRangeTree::insert(int x, int y, BinaryRangeNode *t, Line *line)
{	
     if (t == NULL) 
         t = new BinaryRangeNode(x,y, line);
     else if (x < t->data)
     {
         t->left = insert(x, y, t->left, line);
         if (height(t->left) - height(t->right) == 2)
             if (x < t->left->data)
                 t = rotateWithLeftChild(t);
             else
                 t = doubleWithLeftChild(t);
     }
     else if (x > t->data)
     {
         t->right = insert(x, y, t->right, line);
         if (height(t->right) - height(t->left) == 2)
             if (x > t->right->data)
                 t = rotateWithRightChild(t);
             else
                 t = doubleWithRightChild(t);
     }
	else if (x == t->data) {
		t->data2.push_back(y);
		t->lines.push_back(line);			
	}
     t->height = max(height(t->left), height(t->right)) + 1;
     return t;
 }

 /* Rotate binary tree node with left child */
 BinaryRangeNode* BinaryRangeTree::rotateWithLeftChild(BinaryRangeNode* k2)
 {
     BinaryRangeNode *k1 = k2->left;
     k2->left = k1->right;
     k1->right = k2;
     k2->height = max(height(k2->left), height(k2->right)) + 1;
     k1->height = max(height(k1->left), k2->height) + 1;
     return k1;
 }

 /* Rotate binary tree node with right child */
 BinaryRangeNode* BinaryRangeTree::rotateWithRightChild(BinaryRangeNode *k1)
 {
     BinaryRangeNode *k2 = k1->right;
     k1->right = k2->left;
     k2->left = k1;
     k1->height = max(height(k1->left), height(k1->right)) + 1;
     k2->height = max(height(k2->right), k1->height) + 1;
     return k2;
 }

 /*
  * Double rotate binary tree node: first left child
  * with its right child; then node k3 with new left child
  */
 BinaryRangeNode* BinaryRangeTree::doubleWithLeftChild(BinaryRangeNode *k3)
 {
     k3->left = rotateWithRightChild(k3->left);
     return rotateWithLeftChild(k3);
 }

 /*
  * Double rotate binary tree node: first right child
  * with its left child; then node k1 with new right child
  */
 BinaryRangeNode* BinaryRangeTree::doubleWithRightChild(BinaryRangeNode *k1)
 {
     k1->right = rotateWithLeftChild(k1->right);
     return rotateWithRightChild(k1);
 }

 /* Functions to count number of nodes */
 int BinaryRangeTree::countNodes()
 {
     return countNodes(root);
 }

 int BinaryRangeTree::countNodes(BinaryRangeNode *r)
 {
     if (r == NULL)
         return 0;
     else
     {
         int l = 1;
         l += countNodes(r->left);
         l += countNodes(r->right);
         return l;
     }
 }

 /* Functions to search for an element */
 bool BinaryRangeTree::search(int val)
 {
     return search(root, val);
 }

 bool BinaryRangeTree::search(BinaryRangeNode *r, int val)
 {
     bool found = false;
     while ((r != NULL) && !found)
     {
         int rval = r->data;
         if (val < rval)
             r = r->left;
         else if (val > rval)
             r = r->right;
         else
         {
             found = true;
             break;
         }
         found = search(r, val);
     }
     return found;
 }

 /* Function for inorder traversal */
 void BinaryRangeTree::inorder()
 {
     inorder(root);
 }

 void BinaryRangeTree::inorder(BinaryRangeNode *r)
 {
	int i;
     if (r != NULL)
     {
         inorder(r->left);
         cout<< " { " << r->data<<" : ";
		for (i=0; i<r->data2.size(); i++)
			cout << r->data2[i] << "  ";
	cout << "} ";
         inorder(r->right);
     }
 }

 /* Function for preorder traversal */
 void BinaryRangeTree::preorder()
 {
	cout << " preorder " << endl;
     preorder(root);
 }
 void BinaryRangeTree::preorder(BinaryRangeNode *r)
 {
	int i;
     if (r != NULL)
     {
	for (i=0; i<r->lines.size(); i++) {
			if (r->lines[i]->reported != 1)	{
				cout << " OP1 { (" << r->lines[i]->x1 << " " << r->lines[i]->y1 << ") -- (" << r->lines[i]->x2 << " " << r->lines[i]->y2 << ") } " << endl;
			}
	}
         preorder(r->left);
         preorder(r->right);
     }
 }

 /* Function for postorder traversal */
 void BinaryRangeTree::postorder()
 {
     postorder(root);
 }
 void BinaryRangeTree::postorder(BinaryRangeNode *r)
 {
	int i;
     if (r != NULL)
     {
         postorder(r->left);
         postorder(r->right);
         cout<< " { " << r->data<<" : ";
		for (i=0; i<r->data2.size(); i++)
			cout << r->data2[i] << "  ";
	cout << "} ";
     }
 }

void BinaryRangeTree::buildytrees() {
	buildytrees(root);
}

/* constuct the second layer on range trees, indexed on y-coordinates */
void BinaryRangeTree::buildytrees(BinaryRangeNode *r) {
	if (r != NULL) {
		BinaryRangeTree* temp_tree = new BinaryRangeTree();
		buildytrees(r, temp_tree);
		r->ytree = temp_tree;
		buildytrees(r->left);	
		buildytrees(r->right);	
	}
}

void BinaryRangeTree::buildytrees(BinaryRangeNode *r, BinaryRangeTree* temp_tree) {
	int i;
	if (r != NULL)
             {
		for (i=0; i<r->data2.size(); i++)
			 temp_tree->insert(r->data2[i], r->data, r->lines[i]);
                 buildytrees(r->left, temp_tree);
                 buildytrees(r->right, temp_tree);
             }
	
}

void BinaryRangeTree::printytree() {
	root->ytree->preorder();
	cout << " " << endl;
	root->left->ytree->preorder();
}

/* Find splitnode. Used for querying */
BinaryRangeNode* BinaryRangeTree::findSplitNode(BinaryRangeNode* tree, int x1, int x2) {
	BinaryRangeNode *r = root;
	while (!isLeaf(r) & (r->data > x2 || r->data < x1)) {
		if  (r->data >= x1)
			r = r->left;
		else
			r = r->right;
	}
	return r;
}


/* Find splitnode on the Range tree indexed on y-coordinates */
BinaryRangeNode* BinaryRangeTree::findSplitNodeYtree(BinaryRangeNode* tree, int x1, int x2) {
	BinaryRangeNode *r = tree;
	while (!isLeaf(r) & (r->data > x2 || r->data < x1)) {
		if  (r->data >= x1) {
			r = r->left;
			if (r == NULL)
				return NULL;
		}
		else {
			r = r->right;
			if (r == NULL)
				return NULL;
		}
	}
	return r;
}

bool BinaryRangeTree::isLeaf(BinaryRangeNode* r) {
	if (r == NULL)
		return 1;
	if (r->left == NULL & r->right == NULL)
		return 1;
	return 0;
}

void BinaryRangeTree::reportSubtree(BinaryRangeNode* r) {
	if (r != NULL)
		preorder(r);
}

/* report the point as output */
void BinaryRangeTree::reportPoint(BinaryRangeNode *r) {
	int i;	
	for (i=0; i< r->data2.size(); i++) {
		if (r->lines[i]->reported != 1) {
			r->lines[i]->reported = 1;
			cout << " OP4 { (" << r->lines[i]->x1 << " " << r->lines[i]->y1 << ") -- (" << r->lines[i]->x2 << " " << r->lines[i]->y2 << ") } " << endl;
		}
	}
}

void BinaryRangeTree::reportPointYtree(BinaryRangeNode *r) {
	int i;	
	for (i=0; i< r->data2.size(); i++)	 {
		if (r->lines[i]->reported != 1) {
			cout << " OP2 { (" << r->lines[i]->x1 << " " << r->lines[i]->y1 << ") -- (" << r->lines[i]->x2 << " " << r->lines[i]->y2 << ") } " << endl;
			r->lines[i]->reported = 1;
		}
	}
}

/* one dimensional range tree query */
void BinaryRangeTree::onedquery(int x1, int x2) {
	BinaryRangeNode* splitnode = findSplitNode(root, x1, x2);
	BinaryRangeNode* v;
	int i;
	if ((splitnode->data >= x1) & (splitnode->data <= x2)) {
		reportPoint(splitnode);
	}
	if (!isLeaf(splitnode)) {
		// go to left
		v = splitnode->left;
		while (!isLeaf(v)) { // is not a leaf
			if (x1 <= v->data) {
				reportPoint(v); //report the point itself
				reportSubtree(v->right);
				v = v->left;
			}
			else
				v = v->right;
		}
		if (v != NULL) {
			if ((v->data >= x1) & (v->data <= x2))
				reportPoint(v);	// Report the point itself
		}

		// go to right
		v = splitnode->right;
		while (!isLeaf(v)) { // is not a leaf
			if (x2 >= v->data) {
				reportPoint(v);
				reportSubtree(v->left);
				v = v->right;
			}
			else
				v = v->left;
		}
		if (v != NULL) {
			if ((v->data >= x1) & (v->data <= x2))
				reportPoint(v);
		}
	}
}

/* One dimensional query on the range tree indexed on y-coordinates */
void BinaryRangeTree::onedqueryYtree(BinaryRangeTree *r, int x1, int x2) {
	BinaryRangeNode* splitnode = findSplitNodeYtree(r->root, x1, x2);
	if (splitnode == NULL)
		return;
	BinaryRangeNode* v;
	if ((splitnode->data >= x1) & (splitnode->data <= x2))
			reportPointYtree(splitnode);			
	if (!isLeaf(splitnode)) {
		// go to left
		v = splitnode->left;
		while (!isLeaf(v)) { // is not a leaf
			if (x1 <= v->data) {
				reportPointYtree(v);
				reportSubtree(v->right);
				v = v->left;
			}
			else
				v = v->right;
		}
		if (v != NULL) {
			if ((v->data >= x1) & (v->data <= x2))
				reportPointYtree(v);
		}

		// go to right
		v = splitnode->right;
		while (!isLeaf(v)) { // is not a leaf
			if (x2 >= v->data) {
				reportPointYtree(v);	
				reportSubtree(v->left);
				v = v->right;
			}
			else
				v = v->left;
		}
		if (v != NULL) {
			if ((v->data >= x1) & (v->data <= x2))
				reportPointYtree(v);
		}
	}
}

/* Check if the point is in the range, output if yes */
void BinaryRangeTree::isPointInRange(BinaryRangeNode* r, int x1, int x2, int y1, int y2) {
	int i;
	if ((r->data >= x1) & (r->data <= x2)) { // in x range
		for (i=0; i< r->data2.size(); i++) {
			if  ((r->data2[i] >= y1) & (r->data2[i] <= y2) ) {
				if (r->lines[i]->reported != 1) {
					r->lines[i]->reported = 1;
					cout << " OP5 { (" << r->lines[i]->x1 << " " << r->lines[i]->y1 << ") -- (" << r->lines[i]->x2 << " " << r->lines[i]->y2 << ") } " << endl;
				}
			}
		}
	}
}

/* 2D query. */
void BinaryRangeTree::twodquery(int x1, int x2, int y1, int y2) {
	BinaryRangeNode* splitnode = findSplitNode(root, x1, x2);
	BinaryRangeNode* v;
	int i;
	isPointInRange(splitnode, x1, x2, y1, y2);
	if (!isLeaf(splitnode)) {
		// go to left
		v = splitnode->left;
		while (!isLeaf(v)) { // is not a leaf
			if (x1 <= v->data) {
				isPointInRange(v, x1, x2, y1, y2); //report the point itself
				if (v->right != NULL )
					onedqueryYtree(v->right->ytree, y1, y2);
				v = v->left;
			}
			else
				v = v->right;
		}
		if (v != NULL) {
			isPointInRange(v, x1, x2, y1, y2); 
		}

		v = splitnode->right;
		while (!isLeaf(v)) { // is not a leaf
			if (x2 >= v->data) {
				isPointInRange(v, x1, x2, y1, y2); 
				if (v->left != NULL) {
					onedqueryYtree(v->left->ytree, y1, y2);
				}
				v = v->right;
			}
			else
				v = v->left;
		}
		if (v != NULL) {
			isPointInRange(v, x1, x2, y1, y2); 
		}
	}
}


/* Construct the 2D range tree */
BinaryRangeTree* BinaryRangeTree::buildRangeTree(vector<Line> lines, BinaryRangeTree* sbbst) {
	int i;
	for (i=0; i < lines.size() ; i++) {
		sbbst->insert(lines[i].x1, lines[i].y1, &lines[i]);
		sbbst->insert(lines[i].x2, lines[i].y2, &lines[i]);
	}
	sbbst->buildytrees();
	cout << "\n query " << endl;
	sbbst->twodquery(0, 4, 0, 4);
	return sbbst;
}

/* Given a set of line segments, build a 2D range tree using the end points of lines */
BinaryRangeTree* BinaryRangeTree::buildRangeTreeEndPoints(BinaryRangeTree *sbbst, vector<Line*> lines) {
	int i;
	for (i=0; i < lines.size() ; i++) {
		sbbst->insert(lines[i]->x1, lines[i]->y1, lines[i]);
		sbbst->insert(lines[i]->x2, lines[i]->y2, lines[i]);
	}
	sbbst->buildytrees();
	return sbbst;
}


BinaryRangeTree* BinaryRangeTree::buildRangeTree2(BinaryRangeTree *sbbst, vector<Line*> lines) {
	int i;
	for (i=0; i < lines.size() ; i++) {
		sbbst->insert(lines[i]->x1, lines[i]->y1, lines[i]);
		sbbst->insert(lines[i]->x2, lines[i]->y2, lines[i]);
	}
	sbbst->buildytrees();
	return sbbst;
}

