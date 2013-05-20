
#include "object.h"

//Constructors
Object::~Object(){}

Object::Object(){
	this->location = Point(0,0);
}

Object::Object(Point location){
	this->location = location;
	this->start_location = location;
}

/* PURPOSE: Check if object will collide with any of the walls.
   RECEIVES: Point - location object plans to move to, vector<Rectangle> - all walls
   RETURNS: bool - true if object will collide with a wall.
 */
bool Object::check_collision(Point next_location, vector <Rectangle> blocks){
	//check collision with each block
	bool result = false;
	for(unsigned each_block = 0; each_block < blocks.size(); each_block++){
		vector <Line> outline = blocks[each_block].get_outline();
		//go through each line in block
		for(unsigned each_line = 0; each_line < outline.size(); each_line++){
			result = check_line_collision(next_location, outline[each_line]);
			if(result){return result;}
		}
		result = check_line_collision(next_location, MENU_LINE);
		if(result){return result;}
		result = check_line_collision(next_location, MESSAGE_LINE);
		if(result){return result;}
		result = check_line_collision(next_location, LEFT_BARRIER);
		if(result){return result;}
		result = check_line_collision(next_location, RIGHT_BARRIER);
	}
	return result;
}

/* PURPOSE: Check if collision would occur with Point and one Line
   RECEIVES: Point - next location of Object, Line - line to check collision with
   RETURNS: bool - true if object collides with line
   REMARKS: Called by Object::check_collision(...) and Player::check_collision(...)
 */
bool Object::check_line_collision(Point next_location, Line line){
	//		Old initial check -> if(next_location.get_x() == current_line_start.get_x()
	Point current_line_start = line.get_start();
	Point current_line_end = line.get_end();
	if(abs(current_line_start.get_x() - next_location.get_x()) <= COLLISION_CLOSENESS
			&& next_location.get_y() > current_line_start.get_y()
			&& next_location.get_y() < current_line_end.get_y()){
		return true;
	}
	if(abs(current_line_start.get_y() - next_location.get_y()) <= COLLISION_CLOSENESS
			&& next_location.get_x() > current_line_start.get_x()
			&& next_location.get_x() < current_line_end.get_x()){
		return true;
	}
	return false;
}
