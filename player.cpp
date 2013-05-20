
using namespace std;
#include "player.h"
#include "level.h"
#include "constants.h"
#include <cmath>
#include <iostream>


//Constructors
Player::Player(){}

Player::Player(Point current_location){
	setLocation(current_location);
	setStartLocation(current_location);
}

/* PURPOSE:  Draws player onto screen
 */
void Player::draw(){
	cwin << Circle (this->getLocation(), .05);
	cwin << Circle (this->getLocation(), .2, "purple");
}

/* PURPOSE:  Handles where player should end up after collision with portal
   RECEIVES: Line portal_from, Line portal_to - Lines representing both portals
   RETURNS:  Point -true if portal button has been clicked.
 */
Point Player::get_jump_point(Line portal_from, Line portal_to){
	//if started from left
	if(getLocation().get_x() <= portal_from.get_start().get_x())
		//output point on right.
		return Point((portal_to.get_start().get_x() + MOVEMENT_STEP), (portal_to.get_start().get_y() + PORTAL_LENGTH / 2));	 //if division to double gives issues,
	else
		//else output point on left.
		return Point((portal_to.get_start().get_x() - MOVEMENT_STEP), (portal_to.get_start().get_y() + PORTAL_LENGTH / 2)); // switch PORTALLGTH/2 to MOVEMENTSTEP
}

/* PURPOSE:  If portal button is clicked, jump to draw portal
   RECEIVES: Point - current portal location, vector <Line> all portals
 */
void Player::teleport(Point portal_location, vector <Line> portals){
	if(abs(portal_location.get_x() - portals[0].get_start().get_x()) <= COLLISION_CLOSENESS
			&& portal_location.get_y() > portals[0].get_start().get_y()
			&& portal_location.get_y() < portals[0].get_end().get_y()){
		Point portal_jump = get_jump_point(portals[0],portals[1]);
		setLocation(portal_jump);
	}
	else{
		Point portal_jump = get_jump_point(portals[1],portals[0]);
		setLocation(portal_jump);
	}
}

/* PURPOSE:  If portal button is clicked, jump to draw portal
   RECEIVES: Point - location player is planning on moving to, vector<Rectangle> - all walls, vector<Line> - all portals.
   RETURNS:  bool -true if player has collided with any portal or wall.
 */
bool Player::check_collision(Point next_location, vector <Rectangle> blocks, vector <Line> portals){
	//check collision with each block
	bool result = false;
	//check collision with the portals
	for(unsigned each_portal = 0; each_portal < portals.size(); each_portal++){
		result = check_line_collision(next_location, portals[each_portal]);
		if(result){
			teleport(next_location, portals);
			return result;
		}
	}
	for(unsigned each_block = 0; each_block < blocks.size(); each_block++){
		vector <Line> outline = blocks[each_block].get_outline();
		//go through each line in block
		for(unsigned each_line = 0; each_line < outline.size(); each_line++){
			result = check_line_collision(next_location, outline[each_line]);
			if(result){return result;}
		}
	}
	return result;
}

/* PURPOSE:  Sets new location of player if not colliding with any object
   RECEIVES: Point - user mouse click, vector <Rectangle> -all walls, vector <Line> -portals
 */
void Player::move(Point click, vector <Rectangle> blocks, vector <Line> portals){
	double click_x=click.get_x();
	double click_y=click.get_y();
	double char_x=getLocation().get_x();
	double char_y=getLocation().get_y();
	//Check location of click, then check collision, move conditionally.

	//upper left click
	Point next_location;
	if (click_y>=char_y && click_x <= char_x){
		//move left
		if(abs(click_x-getLocation().get_x()) > abs(click_y - getLocation().get_y())){
			next_location = Point(char_x - MOVEMENT_STEP, char_y);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
		//move up
		else{
			next_location = Point(char_x, char_y+MOVEMENT_STEP);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
	}
	//upper right click
	else if (click_y>=char_y && click_x >= char_x){
		//move right
		if(abs(click_x-getLocation().get_x()) >= abs(click_y - getLocation().get_y())){
			next_location = Point(char_x + MOVEMENT_STEP, char_y);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
		//move up
		else{
			next_location = Point(char_x, char_y+MOVEMENT_STEP);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
	}
	//bottom left click
	else if (click_y <= char_y && click_x <= char_x){
		//move left
		if(abs(click_x-getLocation().get_x()) > abs(click_y - getLocation().get_y())){
			Point next_location(char_x - MOVEMENT_STEP, char_y);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
		//move down
		else{
			next_location = Point(char_x, char_y-MOVEMENT_STEP);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
	}
	//bottom right click
	else if (click_y <= char_y && click_x >= char_x){
		//move right
		if(abs(click_x-getLocation().get_x()) > abs(click_y - getLocation().get_y())){
			next_location = Point(char_x + MOVEMENT_STEP, char_y);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
		//move down
		else{
			next_location = Point(char_x, char_y-MOVEMENT_STEP);
			if(!check_collision(next_location, blocks, portals)){setLocation(next_location);}
		}
	}
}

