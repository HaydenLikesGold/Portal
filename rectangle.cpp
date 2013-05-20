
#include "rectangle.h"

//draws all Rectangles from bottom left, with lines starting on the bottom and left points.

//Constructors
Rectangle::Rectangle(){}

Rectangle::Rectangle(Point bottom_left, double width, double height){
	this->bottom_left =  bottom_left;
	this->width = width;
	this->height = height;

	Point bottom_right = Point(this->bottom_left.get_x() + width, this->bottom_left.get_y());
	Point top_right = Point(bottom_right.get_x(),bottom_right.get_y() + height);
	Point top_left = Point(this->bottom_left.get_x(), bottom_left.get_y() + height);

	this->left_line = Line(this->bottom_left,top_left);
	this->right_line = Line(bottom_right, top_right);
	this->top_line = Line(top_left, top_right);
	this->bottom_line = Line(this->bottom_left, bottom_right);

	this->outline.push_back(left_line);
	this->outline.push_back(right_line);
	this->outline.push_back(top_line);
	this->outline.push_back(bottom_line);

}

//same as previous, but implementing color.
Rectangle::Rectangle(Point bottom_left, double width, double height, string color){
	this->bottom_left =  bottom_left;
	this->width = width;
	this->height = height;

	Point bottom_right = Point(this->bottom_left.get_x() + width, this->bottom_left.get_y());
	Point top_right = Point(bottom_right.get_x(),bottom_right.get_y() + height);
	Point top_left = Point(this->bottom_left.get_x(), bottom_left.get_y() + height);

	this->left_line = Line(this->bottom_left,top_left, color);
	this->right_line = Line(bottom_right, top_right, color);
	this->top_line = Line(top_left, top_right, color);
	this->bottom_line = Line(this->bottom_left, bottom_right, color);

	this->outline.push_back(left_line);
	this->outline.push_back(right_line);
	this->outline.push_back(top_line);
	this->outline.push_back(bottom_line);

}

/* PURPOSE: Draw all lines of the rectangle to the screen.
 */
void Rectangle::draw(){
	cwin << left_line << right_line << top_line << bottom_line;
}

/* PURPOSE: Get all the lines of the rectangle
 * RETURNS: vector <Line> - all lines of rectangle
 */
vector <Line> Rectangle::get_outline(){
	return this->outline;
}
