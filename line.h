#include <iostream>
# ifndef Line_H
# define Line_H

using namespace std;


class Line {
	public:
	int x1;
	int x2;
	int y1; 
	int y2;
	bool reported;
	Line() {
		x1 = 0; x2 = 0;
		y1 = 0; y2 = 0;
		reported = 0;
	}
	Line(int a1, int a2, int b1, int b2) {
		x1 = a1; x2 = a2;
		y1 = b1; y2 = b2;
		reported = 0;
	}
};



	
#endif
