
#ifndef BEAR_H
#define BEAR_H
#include "datastorage.hpp"
#include "typedefs.hpp"
#include "game.hpp"
class bear{

public:
	bear();
	void setPosition(int x, int y) {this->x = x; this->y = y;}
	int getX() {return x;}
	int getY() {return y;}

	void findTo(int targetX, int targetY);
	void render();

private:
	int x;
	int y;

	SpritePtr sprite;

};



#endif
