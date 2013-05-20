/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             player.h/cpp
PURPOSE:          Player class
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "object.h"
#include "rectangle.h"
#include <vector>

using namespace std;

class Player : public Object{
public:
	Player();

	Player(Point current_location);

	Point get_jump_point(Line portal_from, Line portal_to);

	void draw();

	void move(Point click, vector <Rectangle> blocks, vector <Line> portals);

	virtual bool check_collision(Point next_location, vector <Rectangle> blocks, vector <Line> portals);

	void teleport(Point portal_location, vector <Line> portals);

};



#endif /* PLAYER_H_ */
