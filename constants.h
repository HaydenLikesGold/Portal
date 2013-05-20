/*****************************************************************
PROJECT:          MCS 273 Final Project : Portals
FILE:             constants.h
PURPOSE:          Constants
COMPILER:         g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)
TARGET:           i686-apple-darwin11-llvm-
PROGRAMMERS:      Hayden Goldstien & Nate Jenson
*****************************************************************/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/*GUI Constants************************************/
const Point PORTAL_BUTTON_LOCATION=Point(8.25,-8.5);
const double BUTTON_RADIUS=1.25;
const Point LASER_BUTTON_LOCATION=Point(5, -8.5);
const Point RESET_BOTTOM_LEFT = Point(-9.5,-9.25);
const double RESET_WIDTH = 2.5;
const double RESET_HEIGHT = 1.5;
const double TEXT_HEIGHT = 0.35;
const double TEXT_OFFSET = 0.2;
//Label Points
const Point LEVEL_LABEL_POINT = Point(-6.5, -8);
const Point LASERS_LEFT_POINT = Point(-3, -8.75);
const Point PORTALS_LEFT_POINT= Point(-3, -7.5);

const Line MENU_LINE = Line(Point(-10,-7),Point(10,-7));
const Line MESSAGE_LINE = Line(Point(-10, 9.3), Point(10, 9.3));
const Line LEFT_BARRIER = Line(Point(-9.8, -7 ), Point(-9.8, 9.3));
const Line RIGHT_BARRIER= Line(Point(9.8,-7), Point(9.8, 9.3));

/*Object Constants************************************/
const double COLLISION_CLOSENESS = 0.4;
//Player Constants
const double MOVEMENT_STEP = 0.5;
//Enemy Constants
const double ENEMY_STEP= 0.8;
const double ENEMY_NEARNESS_MOVEMENT_NECCESARY=6;
const double BAR_INCREMENT = 0.05;
const double ATTACK_NEARNESS=.6;
const double DEATH_RADIUS=ATTACK_NEARNESS*2;
const int BULLET_DAMAGE=25;
const Point AFTER_DEATH_LOCATION=Point(-10, 10);

/*Portal & Laser Constants***************************/
//Portal Constants
const double PORTAL_LENGTH=1.0;
const double HALF_PORTAL_LENGTH=PORTAL_LENGTH/2;
const double CLICK_DISTANCE_LIMIT=5;
const int PORTAL_LIMIT=3;
//Laser Constants
const double LASER_WIDTH=.3;
const int LASER_LIMIT=3;
const string LASER_COLOR = "RED";


#endif /* CONSTANTS_H_ */
