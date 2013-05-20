/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             enemy.h/cpp
PURPOSE:          Enemy class
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/

#ifndef ENEMY_H_
#define ENEMY_H_

#include "object.h"
#include "player.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

class Enemy : public Object{
public:
	 Enemy();

	 Enemy(Point current_location);

	 bool in_bounds(Point p);

	 void move(Player player, vector <Rectangle> blocks);

	 void draw();

	 void death();
};


#endif /* ENEMY_H_ */
