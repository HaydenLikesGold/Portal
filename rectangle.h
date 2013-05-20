/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             rectangle.h/cpp
PURPOSE:          Rectangle class
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "ccc_win.h"
#include <vector>

class Rectangle{
public:
	Rectangle();

	Rectangle(Point bottom_left, double width, double height);

	Rectangle(Point bottom_left, double width, double height, string color);

	void draw();

	vector <Line> get_outline();

private:
	Point bottom_left;
	double width;
	double height;

	Line bottom_line;
	Line top_line;
	Line right_line;
	Line left_line;

	vector <Line> outline;
};


#endif /* RECTANGLE_H_ */
