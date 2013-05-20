

#include "enemy.h"

//Constructors
Enemy::Enemy(){}

Enemy::Enemy(Point current_location){
	setLocation(current_location);
	setStartLocation(current_location);
}

/* PURPOSE: Simple check whether Enemy is still on screen.
   RECEIVES: Point - position of enemy
   RETURNS: bool - true if enemy is in_bounds
 */
bool Enemy::in_bounds(Point p){
	if(p.get_x() > LEFT_BARRIER.get_start().get_x()
			&& p.get_x() < RIGHT_BARRIER.get_start().get_x()
			&& p.get_y() > MENU_LINE.get_start().get_y()
			&& p.get_y() < MESSAGE_LINE.get_start().get_y()){
		return true;
	}
	return false;
}

/* PURPOSE: Set new location of enemy as long as no collision will occur.
   RECEIVES: Player - player, vector<Rectangle> - all walls
 */
void Enemy::move(Player player, vector <Rectangle> blocks){
	double enemy_x=getLocation().get_x();
	double enemy_y=getLocation().get_y();
	double player_x=player.getLocation().get_x();
	double player_y=player.getLocation().get_y();
	double distance=sqrt(pow((enemy_x-player_x),2)+pow((enemy_y-player_y),2));
	if (distance<ENEMY_NEARNESS_MOVEMENT_NECCESARY){
		if(player_x>enemy_x)enemy_x+=ENEMY_STEP;
		if(player_x<enemy_x)enemy_x-=ENEMY_STEP;
		if(player_y>enemy_y)enemy_y+=ENEMY_STEP;
		if(player_y<enemy_y)enemy_y-=ENEMY_STEP;

		Point next_location(enemy_x,enemy_y);
		//check collision with blocks.
		if(!Object::check_collision(next_location, blocks) && in_bounds(next_location)){
			setLocation(Point(enemy_x, enemy_y));
		}
	}
	else {
		double random_integer = (rand()%10)+1;
		if (random_integer<=2.5)enemy_x+=ENEMY_STEP;
		else if (random_integer<=5.0)enemy_x-=ENEMY_STEP;
		else if (random_integer<=7.5)enemy_y+=ENEMY_STEP;
		else enemy_y-=ENEMY_STEP;
		Point next_location(enemy_x,enemy_y);
		if(!Object::check_collision(next_location, blocks) && in_bounds(next_location)){
			setLocation(Point(enemy_x, enemy_y));
		}
	}
}

/* PURPOSE: Draw Enemy to screen.
 */
void Enemy::draw(){
	cwin << Point(getLocation().get_x(), getLocation().get_y(), "red");
}

/* PURPOSE: Move Enemy out of play if dead.
 */
void Enemy::death(){
	setLocation(AFTER_DEATH_LOCATION);
}
