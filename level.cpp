/*
 * level.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: njenson2
 */

#include "level.h"
#include "constants.h"
//GLOBALS***********************************************
int lasers_used=0;
int portals_used=0;
//******************************************************

Level::Level(){}

Level::Level(string label, vector <Rectangle> blocks, vector <Enemy> enemies, Player player, Point finish){
	this->blocks = blocks;
	this->enemies = enemies;
	this->player = player;
	this->finish = finish;
	this->portal_button = Circle (PORTAL_BUTTON_LOCATION, BUTTON_RADIUS, "blue");
	this->label = label;
	this->laser_limit=LASER_LIMIT;
	this->portal_limit=PORTAL_LIMIT;
	lasers_used=0;
	portals_used=0;
}

Level::Level(string label,vector <Rectangle> blocks, vector <Enemy> enemies, Player player, Point finish, int laser_limit, int portal_limit){
	this->label = label;
	this->blocks = blocks;
	this->enemies = enemies;
	this->player = player;
	this->finish = finish;
	this->portal_button = Circle (PORTAL_BUTTON_LOCATION, BUTTON_RADIUS, "blue");
	this->laser_button=Circle (LASER_BUTTON_LOCATION, BUTTON_RADIUS, "red");
	this->laser_limit=laser_limit;
	this->portal_limit=portal_limit;
	lasers_used=0;
	portals_used=0;
}

/* PURPOSE:  Converts a digit to a string
   RECEIVES: int digit
   RETURNS:  string of the digit given
 */
string digitToString (int digit) {
	static string dummy = "X";
	dummy[0] = '0' + digit;
	return dummy;
}


/* PURPOSE:  Draws all buttons and labels in the menu.
 */
void Level::draw_buttons(){
	Message portal_label = Message(Point(PORTAL_BUTTON_LOCATION.get_x() - BUTTON_RADIUS + TEXT_OFFSET, PORTAL_BUTTON_LOCATION.get_y() + TEXT_HEIGHT), "Portal");
	cwin<<portal_button<<portal_label;

	Message laser_label = Message(Point(LASER_BUTTON_LOCATION.get_x() - BUTTON_RADIUS + TEXT_OFFSET, LASER_BUTTON_LOCATION.get_y() + TEXT_HEIGHT), "LASER");
	cwin<<laser_button<<laser_label;

	Rectangle reset_button(RESET_BOTTOM_LEFT, RESET_WIDTH, RESET_HEIGHT);
	Message reset_label = Message(Point(RESET_BOTTOM_LEFT.get_x() + TEXT_OFFSET, RESET_BOTTOM_LEFT.get_y() + (TEXT_HEIGHT * RESET_HEIGHT * 2)), "Reset");

	reset_button.draw();

	cwin << reset_label;

	string portals_left_string="Portals Left: "+digitToString(portal_limit-portals_used);
	string lasers_left_string="Lasers Left: "+digitToString(laser_limit-lasers_used);
	cwin << Message(PORTALS_LEFT_POINT, portals_left_string);
	cwin << Message(LASERS_LEFT_POINT, lasers_left_string);
	cwin << Message(LEVEL_LABEL_POINT, this->label);
}

/* PURPOSE:  If portal button is clicked, jump to draw portal
   RECEIVES: Point - click
   RETURNS:  bool -true if portal button has been clicked.
 */
bool Level::portal_click(Point click){
	double click_x=click.get_x()-PORTAL_BUTTON_LOCATION.get_x();
	double click_y=click.get_y()-PORTAL_BUTTON_LOCATION.get_y();
	double length_of_hyp=sqrt((pow(click_x,2))+(pow(click_y,2)));
	if (!(length_of_hyp>BUTTON_RADIUS)){
		portal_gun();
		return true;
	}
	else {return false;}
}

/* PURPOSE:  If laser button is clicked, jump to shoot_laser().
   RECEIVES: Point click
   RETURNS:  bool -true if laser button has been clicked.
 */
bool Level::laser_click(Point click){
	double click_x=click.get_x()-LASER_BUTTON_LOCATION.get_x();
	double click_y=click.get_y()-LASER_BUTTON_LOCATION.get_y();
	double length_of_hyp=sqrt((pow(click_x,2))+(pow(click_y,2)));
	if (!(length_of_hyp>BUTTON_RADIUS)){
		shoot_laser();
		return true;
	}
	else {return false;}
}

/* PURPOSE:  If reset button is clicked, jump to start_over().
   RECEIVES: Point click
 */
void Level::reset_click(Point click){
	if(click.get_x() > RESET_BOTTOM_LEFT.get_x()
			&& click.get_x() < (RESET_BOTTOM_LEFT.get_x() + RESET_WIDTH)
			&& click.get_y() < (RESET_BOTTOM_LEFT.get_y() + RESET_HEIGHT)
			&& click.get_y() > RESET_BOTTOM_LEFT.get_y()){
		start_over();
	}
}

/* PURPOSE:  Handles creation of portals on display
   RECEIVES: Point click
 */
void Level::portal_gun(){
	if (portals_used<portal_limit){
		Point portalA_point;
		Point portalB_point;
		do{
			portalA_point=cwin.get_mouse("Click to place the first portal");
		}while(portalA_point.get_y()<MENU_LINE.get_end().get_y());
		//change button to orange
		portal_button = Circle (PORTAL_BUTTON_LOCATION, BUTTON_RADIUS, "orange");
		draw_buttons();

		cwin<<portalA_point;
		//		this->portalA = Line(portalA_point, Point(portalA_point.get_x(),portalA_point.get_y()+PORTAL_LENGTH), "blue");
		this->portalA = Line(Point(portalA_point.get_x(), portalA_point.get_y()-HALF_PORTAL_LENGTH),
				Point(portalA_point.get_x(), portalA_point.get_y()+HALF_PORTAL_LENGTH),"blue");
		double distance;
		double acc=1;
		do{
			do {
				if (acc==1){portalB_point=cwin.get_mouse("Click to place the second portal");}
				else if (portalB_point.get_y()<MENU_LINE.get_end().get_y()){portalB_point=cwin.get_mouse("Invalid click, try again");}
				else {portalB_point=cwin.get_mouse("Click too far away, try again");}
				distance= sqrt(pow((portalA_point.get_x()-portalB_point.get_x()),2)+pow((portalA_point.get_y()-portalB_point.get_y()),2));
				this->portalB = Line(Point(portalB_point.get_x(), portalB_point.get_y()-HALF_PORTAL_LENGTH),
						Point(portalB_point.get_x(), portalB_point.get_y()+HALF_PORTAL_LENGTH),"orange");
				acc++;}while (distance>CLICK_DISTANCE_LIMIT);
		}while (portalB_point.get_y()<MENU_LINE.get_end().get_y());
		portal_button = Circle(PORTAL_BUTTON_LOCATION, BUTTON_RADIUS, "blue");
		draw_buttons();
		portals_used++;
	}
	else{cwin.get_mouse("Already used all of the portals allowed");}

}

/* PURPOSE:  Get portals.
   RETURNS:  Vector of Portals represented in Lines
 */
vector <Line> Level::get_portals(){
	vector <Line> portals;
	portals.push_back(this->portalA);
	portals.push_back(this->portalB);
	return portals;

}

/* PURPOSE:  Handles laser and killing of enemies
   RECEIVES: string - direction of click
 */
void Level::enemies_aligned(string direction){
	double click_x=player.getLocation().get_x();
	double click_y=player.getLocation().get_y();
	if (direction=="left"){
		for (unsigned int i=0; i<enemies.size(); i++){
			if (click_x>enemies[i].getLocation().get_x()){
				if (click_y<enemies[i].getLocation().get_y()+LASER_WIDTH && click_y>enemies[i].getLocation().get_y()-LASER_WIDTH){
					enemies[i].death();
				}
			}
		}
	}
	if (direction=="right"){
		for (unsigned int i=0; i<enemies.size(); i++){
			if (click_x<enemies[i].getLocation().get_x()){
				if (click_y<enemies[i].getLocation().get_y()+LASER_WIDTH && click_y>enemies[i].getLocation().get_y()-LASER_WIDTH){
					enemies[i].death();
				}
			}
		}
	}
	if (direction=="down"){
		for (unsigned int i=0; i<enemies.size(); i++){
			if (click_y>enemies[i].getLocation().get_y()){
				if (click_x<enemies[i].getLocation().get_x()+LASER_WIDTH && click_x>enemies[i].getLocation().get_x()-LASER_WIDTH){
					enemies[i].death();
				}
			}
		}
	}
	if (direction=="up"){
		for (unsigned int i=0; i<enemies.size(); i++){
			if (click_y<enemies[i].getLocation().get_y()){
				if (click_x<enemies[i].getLocation().get_x()+LASER_WIDTH && click_x>enemies[i].getLocation().get_x()-LASER_WIDTH){
					enemies[i].death();
				}
			}
		}
	}
}

/* PURPOSE:  Gets laser click and outputs laser line.
 */
void Level::shoot_laser(){
	if (lasers_used<laser_limit){
		Point laser_direction=cwin.get_mouse("Click what direction you would like to fire");
		double click_x=laser_direction.get_x();
		double click_y=laser_direction.get_y();
		double char_x=player.getLocation().get_x();
		double char_y=player.getLocation().get_y();
		Line left(Point(char_x, char_y), Point(-10, char_y), LASER_COLOR);
		Line right(Point(char_x, char_y), Point(10, char_y),LASER_COLOR);
		Line up(Point(char_x, char_y), Point(char_x, 10), LASER_COLOR);
		Line down(Point(char_x, char_y), Point(char_x, MENU_LINE.get_start().get_y()), LASER_COLOR);

		lasers_used++;
		//Check location of click, then fire laser.

		//upper left click
		if (click_y >= char_y && click_x <= char_x){
			//laser left
			if(abs(click_x-char_x) > abs(click_y - char_y)){cwin<<left; cwin.get_mouse("");
			enemies_aligned("left");}
			//laser up
			else{cwin<<up;cwin.get_mouse("");
			enemies_aligned("up");}
		}
		//upper right click
		else if (click_y >= char_y && click_x >= char_x){
			//laser right
			if(abs(click_x-char_x) > abs(click_y - char_y)){cwin<<right;cwin.get_mouse("");
			enemies_aligned("right");}
			//laser up
			else{cwin<<up;cwin.get_mouse("");
			enemies_aligned("up");}
		}
		//bottom left click
		else if (click_y < char_y && click_x <= char_x){
			//laser left
			if(abs(click_x-char_x) > abs(click_y - char_y)){cwin<<left;cwin.get_mouse("");
			enemies_aligned("left");}
			//laser down
			else{cwin<<down;cwin.get_mouse("");
			enemies_aligned("down");}
		}
		//bottom right click
		else if (click_y <= char_y && click_x >= char_x){
			//laser right
			if(abs(click_x-char_x) > abs(click_y - char_y)){cwin<<right;cwin.get_mouse("");
			enemies_aligned("right");}
			//laser down
			else{cwin<<down;cwin.get_mouse("");
			enemies_aligned("down");}
		}
	}
	else{cwin.get_mouse("Already used all of the laser shots allowed");}
}

/* PURPOSE:  displays portals
 * REMARKS: Left as a function to be able to change drawing easily.
 */
void Level::draw_portals(){
	cwin<<this->portalA<<this->portalB;
}

/* PURPOSE:  Displays finish point for the level
   REMARKS: Left as a function to be able to change drawing easily.
 */
void Level::draw_finish(){
	cwin << this->finish;
}

/* PURPOSE:  Display lines above menu and below message line.
   REMARKS: Left as a function to be able to change drawing easily.
 */
void Level::draw_menu(){
	cwin << MENU_LINE << MESSAGE_LINE;
}

/* PURPOSE: Calls all draw methods
 */
void Level::draw_all(){
	//draw blocks
	for(unsigned i = 0; i < blocks.size(); i++){
		blocks[i].draw();
	}
	//draw ememies
	for(unsigned i = 0; i < enemies.size(); i++){
		enemies[i].draw();
	}
	//draw player
	this->player.draw();

	//draw_portals
	draw_portals();

	draw_finish();

	draw_menu();

	draw_buttons();
}

/* PURPOSE: Reset to beginning of level.
 */
void Level::start_over(){
	draw_all();
	cwin << Message(Point(-5,0), "Click to restart...", "red");
	cwin.get_mouse("");
	cwin.clear();
	this->player.setLocation(player.getStartLocation());
	for(unsigned i = 0; i < enemies.size(); i++){
		enemies[i].setLocation(enemies[i].getStartLocation());
	}
	this->portalA = Line();
	this->portalB = Line();
	lasers_used=0;
	portals_used=0;
}

/* PURPOSE: Check if player has beat the level yet or not.
   RETURNS: bool - true if player has beat the level.
 */
bool Level::player_won(){
	if(abs(player.getLocation().get_x() - this->finish.get_x()) <= COLLISION_CLOSENESS
			&& abs(player.getLocation().get_y() - this->finish.get_y()) <= COLLISION_CLOSENESS){return true;}
	if(abs(player.getLocation().get_x() - this->finish.get_x()) <= COLLISION_CLOSENESS
			&& abs(player.getLocation().get_y() - this->finish.get_y()) <= COLLISION_CLOSENESS){return true;}
	return false;
}

/* PURPOSE: Check if position of current enemy causes player to lose.
   RECEIVES: Enemy enemy
 */
void Level::player_lost(Enemy enemy){
	double enemy_x=enemy.getLocation().get_x();
	double enemy_y=enemy.getLocation().get_y();
	double player_x=player.getLocation().get_x();
	double player_y=player.getLocation().get_y();
	double distance=sqrt(pow((enemy_x-player_x),2)+pow((enemy_y-player_y),2));
	if (distance < ATTACK_NEARNESS){
		cwin.clear();
		draw_all();
		cwin<<Circle((Point(player_x, player_y)), DEATH_RADIUS, "red");
		start_over();
	}
}

/* PURPOSE: Checks if user has clicked on the menu.
   RECEIVES: Point - user mouse click
   RETURNS: bool - true if click is in the menu.
 */
bool Level::menu_click(Point click){
	if(click.get_y() < MENU_LINE.get_start().get_y()){
		return true;
	}
	return false;
}

/* PURPOSE: Checks if user has clicked in the message area.
   RECEIVES: Point - user mouse click
   RETURNS: bool - true if click is in message area.
 */
bool Level::message_click(Point click){
	if(click.get_y() > MESSAGE_LINE.get_start().get_y()){
		return true;
	}
	return false;
}

/* PURPOSE: Check to see if buttons in menu were clicked.
   RECEIVES: Point - user mouse click
   RETURNS: bool - true if click is in menu or message area.
 */
bool Level::check_outside_click(Point click){
	if(menu_click(click) || message_click(click)){
		if(!message_click(click)){
			portal_click(click);
			laser_click(click);
			reset_click(click);
		}
		return true;
	}
	return false;
}

/* PURPOSE: Loop that continues game-play on the level.
   REMARKS: This is where the level is played, as long as the player hasn't beat the level.
 */
void Level::start(){
	portals_used = 0;
	lasers_used = 0;
	draw_all();
	while(!player_won()){
		Point click=cwin.get_mouse("Click what direction you want to move.");
		if(!check_outside_click(click)){
			player.move(click, blocks, get_portals());
			srand((unsigned)time(0));
			for (unsigned int i=0; i<enemies.size(); i++){
				enemies[i].move(player, blocks);
				player_lost(enemies[i]);
			}
		}
		cwin.clear();
		draw_all();
	}
}
