/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             level.h/cpp
PURPOSE:          Level class
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/
#ifndef LEVEL_H_
#define LEVEL_H_

using namespace std;

#include <iostream>
#include <vector>
#include <cmath>
//#include "rectangle.h"
//#include "player.h"
//#include "object.h"
#include "enemy.h"
class Level{
public:
	Level();

	Level(string label,vector <Rectangle> blocks, vector <Enemy> enemies, Player player, Point finish);

	Level(string label, vector <Rectangle> blocks, vector <Enemy> enemies, Player player, Point finish, int laser_limit, int portal_limit);

	/*Dealing w/ Buttons*********************************/
	void draw_buttons();

	bool portal_click(Point click);

	bool laser_click(Point click);

	void reset_click(Point click);

	/*Dealing w/ Portal**********************************/
	void portal_gun();

	vector <Line> get_portals();

	/*Dealing w/ Laser***********************************/
	void shoot_laser();

	void enemies_aligned(string direction);

	/*Dealing w/ Drawing*********************************/
	void draw_portals();

	void draw_finish();

	void draw_menu();

	void draw_all();

	/*Dealing w/ Running Game******************************/
	void start_over();

	bool player_won();

	void player_lost(Enemy enemy);

	void start();

private:
	vector <Rectangle> blocks;
	vector <Enemy> enemies;
	Player player;
	Line portalA;
	Line portalB;
	Point finish;
	string label;
	int laser_limit;
	int portal_limit;

	Circle portal_button;
	Circle laser_button;

	bool message_click(Point click);
	bool menu_click(Point click);
	bool check_outside_click(Point click);

};


#endif /* LEVEL_H_ */
