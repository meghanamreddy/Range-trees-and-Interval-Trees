#include <iostream>
#include <cstdlib>
#include <vector>
# ifndef Intervaltree_H
# define Intervaltree_H

using namespace std;

class BinaryRangeTree;
class Line;

class IntervalNode
{
    public:
	int x_mid;
	vector<Line*> I_mid;
	IntervalNode *left, *right;
	BinaryRangeTree *rangetree;
	IntervalNode() {
		x_mid = 0;
		left = NULL;
		right = NULL;
		rangetree = NULL;
	}
	IntervalNode(int x) {
		x_mid = x;
		left = NULL;
		right = NULL;
		rangetree = NULL;
	}
	
	
};
	
class IntervalTree {
	public:
	IntervalNode *root;
	IntervalTree() {
		root = NULL;
	}
	vector<int> getSortedEndPointsX(vector<Line*> lines);
	vector<int> getSortedEndPointsY(vector<Line*> lines);
	void constructX(vector<Line*> lines);
	void constructY(vector<Line*> lines);
	IntervalNode* constructX(vector<Line*> lines, IntervalNode *node);
	IntervalNode* constructY(vector<Line*> lines, IntervalNode *node);
	void preorder(IntervalNode *r);
	void preorder();
	void queryX(int maxX, int minX, int x, int y1, int y2, IntervalNode* node);
	void queryX(int maxX, int minX, int x, int y1, int y2);
	void queryY(int maxY, int minY, int y, int x1, int x2, IntervalNode* node);
	void queryY(int maxY, int minY, int y, int x1, int x2);
};

#endif
