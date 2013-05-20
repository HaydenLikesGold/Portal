
#include "level.h"

/* PURPOSE: Prepares window to advance to the next level.
   RECEIVES: vector <Rectangle>& - all walls for the level, vector <Enemy>& - all enemies.
 */
void next_level(vector <Rectangle>& blocks, vector <Enemy>& enemies){
	cwin << Message(Point(-5,0), "You beat the level! Click to continue...");
	cwin.get_mouse("");
	cwin.clear();
	blocks.clear();
	enemies.clear();
}

/* PURPOSE: MAIN function; Calls title screen and each level.
 */
int ccc_win_main(){
	vector <Rectangle> blocks;
	vector <Enemy> enemies;
	string default_color = "DARKMAGENTA";

	//TITLE SCREEN
	for (int i=11; i>0; i--){
		Message title(Point(-10,i), "-- PORTAL COMBAT -- PORTAL COMBAT -- PORTAL COMBAT --", "ORANGE");
		cwin<<title;
	}
	Message finish_msg(Point(-9,-0.5), "Reach green dot to finish the level.", "green");
	Message portal_msg(Point(-9,-1.5), "Press portal button to begin placing portals.", "blue");
	Message enemy_msg(Point(-9, -2.5), "Avoid red enemies, or use laser. DESTROY THEM.", "red");
	Message laser_msg(Point(-9,-4), "Good luck. Click to continue...");
	Line middle_line(Point(-10,0), Point(10,0));
	Line middle_line2(Point(-10,-5), Point(10,-5));
	for (int i=-5; i>-10; i--){
		Message title(Point(-10,i), "-- PORTAL COMBAT -- PORTAL COMBAT -- PORTAL COMBAT --", "ORANGE");
		cwin<<title;
	}

	cwin << finish_msg << portal_msg << enemy_msg << laser_msg << middle_line<<middle_line2;
	cwin.get_mouse("     Hayden Goldstien & Nate Jenson made a game...");
	cwin.clear();

	start_over:
	// LEVEL ONE
	enemies.push_back(Enemy(Point(0,5)));
	enemies.push_back(Enemy(Point(5,-5)));
	enemies.push_back(Enemy(Point(-5,9)));
	blocks.push_back(Rectangle(Point(-10,0),20,1,default_color));
	blocks.push_back(Rectangle(Point(2,-7),1,4.5,default_color));
	blocks.push_back(Rectangle(Point(-7,-6.8),3,3,default_color));
	blocks.push_back(Rectangle(Point(8,7.5),2,1.5, "forest green"));
	Player player(Point(-8,-6));
	Point finish(9,8.25,"green");
	Level level_one("Level 1",blocks, enemies, player, finish, 3, 3);
	level_one.start();

	next_level(blocks, enemies);

	//LEVEL TWO
	blocks.push_back(Rectangle(Point(-10,2.5),2,2, default_color));
	blocks.push_back(Rectangle(Point(8,2.5),2,2, default_color));
	blocks.push_back(Rectangle(Point(-4,-2.5),3,5, default_color));
	blocks.push_back(Rectangle(Point(1,-2.5),3,5, default_color));
	blocks.push_back(Rectangle(Point(-1.5,7),3,2, "forest green"));
	enemies.push_back(Enemy(Point(-2,5)));
	enemies.push_back(Enemy(Point(2,5)));
	enemies.push_back(Enemy(Point(-6,-5)));
	enemies.push_back(Enemy(Point(6,-5)));
	player.setLocation(Point(0, -6.5));
	player.setStartLocation(player.getLocation());
	finish = Point(0,8,"green");
	Level level_two("Level 2", blocks, enemies, player, finish, 3, 1);
	level_two.start();

	next_level(blocks, enemies);

	//LEVEL THREE
	blocks.push_back(Rectangle(Point(-5,2.5),1,3,default_color));
	blocks.push_back(Rectangle(Point(-4,2.5),3,1, default_color));
	blocks.push_back(Rectangle(Point(0,-2.5),1,3,default_color));
	blocks.push_back(Rectangle(Point(1,-2.5),3,1, default_color));
	blocks.push_back(Rectangle(Point(2,7.5),8,1, default_color));
	enemies.push_back(Enemy(Point(-1,5)));
	enemies.push_back(Enemy(Point(-6,-6)));
	enemies.push_back(Enemy(Point(-5,-5)));
	enemies.push_back(Enemy(Point(5,-5)));
	player.setLocation(Point(9,9));
	player.setStartLocation(player.getLocation());
	blocks.push_back(Rectangle(Point(-1.5,-7),3,2, "forest green"));
	finish = Point(0,-6.5,"green");
	Level level_three("Level 3", blocks, enemies, player, finish, 3,3);
	level_three.start();

	next_level(blocks, enemies);

	//LEVEL FOUR
	blocks.push_back(Rectangle(Point(-1.5,-1),3,2, default_color));
	blocks.push_back(Rectangle(Point(-10,1.5),8,8.5, default_color));
	blocks.push_back(Rectangle(Point(2,1.5),8,8.5, default_color));
	blocks.push_back(Rectangle(Point(-10,-7),8,5.5, default_color));
	blocks.push_back(Rectangle(Point(2,-7),8,5.5, default_color));
	blocks.push_back(Rectangle(Point(-10,-7),1.5,1.5, default_color));
	blocks.push_back(Rectangle(Point(-10,-1.5),1.5,3, default_color));
	blocks.push_back(Rectangle(Point(-8,-4),1.5,1.5, default_color));

	enemies.push_back(Enemy(Point(-7,0)));
	enemies.push_back(Enemy(Point(0,7)));
	enemies.push_back(Enemy(Point(7,0)));
	enemies.push_back(Enemy(Point(0,-6)));
	enemies.push_back(Enemy(Point(5,-5)));
	enemies.push_back(Enemy(Point(-5,5)));
	enemies.push_back(Enemy(Point(5,5)));
	enemies.push_back(Enemy(Point(-5,-5)));
	enemies.push_back(Enemy(Point(-3,-2.5)));
	enemies.push_back(Enemy(Point(-9,-3)));

	finish = Point(-9.25,-6.25,"green");
	player.setLocation(Point(0,0));
	player.setStartLocation(player.getLocation());
	Level level_four("Level 4", blocks, enemies, player, finish, 4, 4);
	level_four.start();

	next_level(blocks, enemies);

	//END - RESTART
	cwin << Message(Point(-5,0), "ALL LEVELS COMPLETE!!!!", "Forest Green");
	cwin << Message(Point(-5,-1.5), "Click to restart!", "ORANGE");
	cwin << Line(Point(-5,-.8), Point(2, -.8));
	cwin.get_mouse("");
	cwin.clear();
	goto start_over;
	exit(0);
}
