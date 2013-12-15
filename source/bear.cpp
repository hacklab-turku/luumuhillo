

#include "bear.hpp"

bear::bear()
{
	sprite = game.getDataStorage()->getSprite("bear");
}

void bear::render()
{
	sprite->setPosition(x * 32, y * 32);
	game.getRenderWindow()->draw(*sprite);

}

void bear::findTo(int targetX, int targetY)
{
	if (targetX < x) x--;
	if (targetX > x) x++;


	if(targetY < y) y--;
	if(targetY > y) y++;
}
