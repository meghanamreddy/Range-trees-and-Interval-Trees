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




int main(int argc, char* argv[]) {
	// Read in line segment data //
	vector<Line*> line_segments;

	// read the input of line segments
	ifstream infile;
	if (argc > 1)
		infile.open(argv[1]);
	else
		infile.open("input.txt");

	string line;
	int num = 0, i, numquery=0, j;
	getline(infile, line);
    	istringstream iss(line);
	iss >> num; iss >> numquery;
	int x1, x2, y1, y2;
	int maxX=0, minX=0, maxY=0, minY=0;
	Line *temp;


	for (i=0; i<num; i++) {
		getline(infile, line);
    		istringstream iss(line);
		iss >> x1; iss >> y1;
		iss >> x2; iss >> y2;
		temp = new Line(x1, x2, y1, y2);
		line_segments.push_back(temp);

		if (x1 < minX) minX = x1;
		if (x2 > maxX) maxX = x2;
		if (y1 < minY) minY = y1;
		if (y2 > maxY) maxY = y2;
	}

	vector<Line*> lines_x;
	vector<Line*> lines_y;
	for (i=0; i<line_segments.size(); i++) {
		if (line_segments[i]->y1 == line_segments[i]->y2)
			lines_x.push_back(line_segments[i]);
		else if (line_segments[i]->x1 == line_segments[i]->x2)
			lines_y.push_back(line_segments[i]);
	}		

	BinaryRangeTree* rangeTreeEndPoints = new BinaryRangeTree();
	rangeTreeEndPoints = rangeTreeEndPoints->buildRangeTreeEndPoints(rangeTreeEndPoints, line_segments);
	IntervalTree treeX;
	IntervalTree treeY;
	if (lines_x.size() > 0)
		treeX.constructX(lines_x);
	if (lines_y.size() > 0)
		treeY.constructY(lines_y);


	//Read queries //

	for (i=0; i<numquery; i++) {
		// set the flags of all lines back to 0
		for (j=0; j<line_segments.size(); j++)
			line_segments[j]->reported = 0;

		getline(infile, line);
    		istringstream iss(line);
		iss >> x1; iss >> y1;
		iss >> x2; iss >> y2;
		if ((x1 != x2) & (y1 != y2)) {
		cout << " Query rectangle :: (" <<  x1 << " " << y1 << ") (" << x2 << " " << y2 << ") " << endl;
		rangeTreeEndPoints->twodquery(x1, x2, y1, y2);
		treeX.queryX(maxX,minX, y1, y1, y2);
		treeY.queryY(maxY, minY, x1, x1, x2);
		cout << endl;
		}
	}
}


