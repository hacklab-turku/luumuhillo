
#include "map.hpp"
#include "game.hpp"
#include "typedefs.hpp"
#include "datastorage.hpp"
#include <random>


map::map()
{


}

void map::render(ViewPtr view)
{
	int minX = (view->getCenter().x - view->getSize().x/2)/32;
	if (minX < 0) minX = 0;
	
	int minY = (view->getCenter().y - view->getSize().y/2)/32;
	if (minY < 0) minY = 0;

	int maxX = (view->getCenter().x + view->getSize().x/2)/32 + 1 ;
	if (maxX > MAP_SIZE_X) maxX = MAP_SIZE_X;

	int maxY = (view->getCenter().y + view->getSize().y/2)/32 + 1;
	if (maxY > MAP_SIZE_Y) maxY = MAP_SIZE_Y;

	SpritePtr plumTree = game.getDataStorage()->getSprite("plumTree");
	SpritePtr pineTree = game.getDataStorage()->getSprite("pineTree");
	SpritePtr grass = game.getDataStorage()->getSprite("grass");
	SpritePtr boulder = game.getDataStorage()->getSprite("boulder");

	for (int x = minX; x < maxX; x++){
	for (int y = minY; y < maxY; y++){
		grass->setPosition(32 * x, 32 * y);
		game.getRenderWindow()->draw(*grass);
	}
	}

	for (int x = minX; x < maxX; x++){
	for (int y = minY; y < maxY; y++){
		switch (world[x][y]){
			case 'P':
				plumTree->setPosition(32 * x, 32 * y + 16);
				game.getRenderWindow()->draw(*plumTree);
				break;
			case 'C':
				pineTree->setPosition(32 * x, 32 * y + 16);
				game.getRenderWindow()->draw(*pineTree);
				break;
			case 'B':
				boulder->setPosition(32 * x, 32 * y + 16);
				game.getRenderWindow()->draw(*boulder);
				break;
		}	
	}
	}



}


void map::generate()
{

	for (int x = 0; x < MAP_SIZE_X; x++){
	for (int y = 0; y < MAP_SIZE_Y; y++){
		int rand = std::rand() % 100;
		if (rand > 90) world[x][y] = 'P';  //Plum
		else if (rand > 85) world[x][y] = 'C';  //Connifer
		else if (rand > 80) world[x][y] = 'B';  //Boulder
		else  world[x][y] = 'G';	//Grass
	}
	}

}

bool map::isSolid(int x, int y)
{
	if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y)
		return true;
	return false;
}


char map::getCellData(int x, int y)
{
	if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y)
		return 'E'; //Off edge
	return world[x][y];

}



