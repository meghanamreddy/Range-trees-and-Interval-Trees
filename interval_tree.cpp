#include <iostream>
#include <cstdlib>
#include <vector>
# include <fstream>
# include <sstream>
#include <algorithm>
#include "interval_tree.h"
#include "binaryRangeTree.h"
#include "line.h"
using namespace std;

bool myfunction (int i,int j) { return (i<j); }


/* sort the end points of the lines - sort by x end points*/
vector<int> IntervalTree::getSortedEndPointsX(vector<Line*> lines) {
	vector<int> endpoints;
	int i;
	for (i=0; i<lines.size(); i++) {
		endpoints.push_back(lines[i]->x1);
		endpoints.push_back(lines[i]->x2);
	}
	sort (endpoints.begin(), endpoints.end(), myfunction);
	return endpoints;
}

/* sort the end points of the lines - sort by y end points*/
vector<int> IntervalTree::getSortedEndPointsY(vector<Line*> lines) {
	vector<int> endpoints;
	int i;
	for (i=0; i<lines.size(); i++) {
		endpoints.push_back(lines[i]->y1);
		endpoints.push_back(lines[i]->y2);
	}
	sort (endpoints.begin(), endpoints.end(), myfunction);
	return endpoints;
}

/* preorder traversal */
void IntervalTree::preorder()
         {
             preorder(root);
         }

void IntervalTree::preorder(IntervalNode *r)
{
	int i;
        if (r != NULL)
        {
	       	cout<< " [[[ ";
		for (i=0; i<r->I_mid.size(); i++)
			cout << " {" << r->I_mid[i]->y1 << "  " << r->I_mid[i]->y2 << "} " ;
		cout << " ]]] ";
		if (r->rangetree != NULL)
			r->rangetree->preorder();
                preorder(r->left);
                preorder(r->right);
	}
}


void IntervalTree::constructX(vector<Line*> lines) {
	root = constructX(lines, root);
}
 

void IntervalTree::constructY(vector<Line*> lines) {
	root = constructY(lines, root);
}

/* construct the interval tree indexed using x values of end points. Input is the set of lines */
IntervalNode* IntervalTree::constructX(vector<Line*> lines, IntervalNode *node) {
	if (node == NULL)
                 node = new IntervalNode();
	int j;
	vector<int> endpoints = getSortedEndPointsX(lines);
	int x_mid = endpoints[(endpoints.size()/2)-1];
	vector<Line*> I_left;
	vector<Line*> I_right;
	vector<Line*> I_mid;
	node->x_mid = x_mid;
	int i;
	for (i=0; i<lines.size(); i++) {
		if (lines[i]->x2 < x_mid)
			I_left.push_back(lines[i]);
		else if (lines[i]->x1 > x_mid)
			I_right.push_back(lines[i]);
		else
			I_mid.push_back(lines[i]);
	}

	if (I_left.size() > 0)
		node->left = constructX(I_left, node->left);
	if (I_right.size() > 0)
		node->right = constructX(I_right, node->right);
	node->I_mid = I_mid;
	if (I_mid.size() > 0) {
		BinaryRangeTree *sbbst = new BinaryRangeTree();
		node->rangetree = sbbst->buildRangeTree2(sbbst, I_mid);
	}
	return node;
}

/* construct the interval tree indexed using =y values of end points. Input is the set of lines */
IntervalNode* IntervalTree::constructY(vector<Line*> lines, IntervalNode *node) {
	if (node == NULL)
                 node = new IntervalNode();
	int j;
	
	vector<int> endpoints = getSortedEndPointsY(lines);
	int x_mid = endpoints[(endpoints.size()/2)-1];
	vector<Line*> I_left;
	vector<Line*> I_right;
	vector<Line*> I_mid;
	node->x_mid = x_mid;
	int i;
	for (i=0; i<lines.size(); i++) {
		if (lines[i]->y2 < x_mid)
			I_left.push_back(lines[i]);
		else if (lines[i]->y1 > x_mid)
			I_right.push_back(lines[i]);
		else
			I_mid.push_back(lines[i]);
	}
	
	if (I_left.size() > 0)
		node->left = constructY(I_left, node->left);
	if (I_right.size() > 0)
		node->right = constructY(I_right, node->right);
	node->I_mid = I_mid;
	if (I_mid.size() > 0) {
		BinaryRangeTree *sbbst = new BinaryRangeTree();
		node->rangetree = sbbst->buildRangeTree2(sbbst, I_mid);
	}
	return node;
}



void IntervalTree::queryX(int maxX, int minX, int x, int y1, int y2) {
	if (root == NULL)
		return;
	queryX(maxX, minX, x, y1, y2, root);
}

void IntervalTree::queryY(int maxY, int minY, int y, int x1, int x2) {
	if (root == NULL)
		return;
	queryY(maxY, minY, y, x1, x2, root);
}

/* Query on the interval tree */
void IntervalTree::queryX(int maxX, int minX, int x, int y1, int y2, IntervalNode* node) {
	if (x < node->x_mid) {
		node->rangetree->twodquery(minX, x, y1, y2);
		if (node->left != NULL)
			queryX(maxX, minX, x, y1, y2, node->left);
	}
	else if (x > node->x_mid) {
		node->rangetree->twodquery(x, maxX, y1, y2);
		if (node->right != NULL)
			queryX(maxX, minX, x, y1, y2, node->right);
	}
	else {
		node->rangetree->twodquery(x, x, y1, y2);
	}
}

/* Query on the interval tree */
void IntervalTree::queryY(int maxY, int minY, int y, int x1, int x2, IntervalNode* node) {
	if (y < node->x_mid) {
		node->rangetree->twodquery(x1, x2, minY, y);
		if (node->left != NULL)
			queryY(maxY, minY, y, x1, x2, node->left);
	}
	else if (y > node->x_mid) {
		node->rangetree->twodquery(x1, x2, y, maxY);
		if (node->right != NULL)
			queryY(maxY, minY, y, x1, x2, node->right);
	}
	else {
		node->rangetree->twodquery(x1, x2, y, y);
	}
}
