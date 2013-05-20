/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             object.h/cpp
PURPOSE:          Object class
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/
#ifndef OBJECT_H_
#define OBJECT_H_

#include "ccc_win.h"
#include "rectangle.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Object{
public:
	Object();

	Object(Point location);

	virtual ~Object();

	virtual bool check_collision(Point next_location, vector <Rectangle> blocks);

	bool check_line_collision(Point next_location, Line line);

	Point getLocation() const {
		return location;
	}

	void setLocation(Point location) {
		this->location = location;
	}

	Point getStartLocation(){
		return start_location;
	}

	void setStartLocation(Point p){
		this->start_location = p;
	}


private:
	Point start_location;
	Point location;
};


#endif /* OBJECT_H_ */
