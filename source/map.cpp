
#include "map.hpp"
#include "game.hpp"
#include "typedefs.hpp"
#include "datastorage.hpp"
#include <random>

map::map()
{


}

void map::render()
{

	SpritePtr plumTree = game.getDataStorage()->getSprite("plumTree");
	SpritePtr grass = game.getDataStorage()->getSprite("grass");

	for (int x = 0; x < MAP_SIZE_X; x++){
	for (int y = 0; y < MAP_SIZE_Y; y++){
		switch (world[x][y]){
			case 'P':
				plumTree->setPosition(32 * x, 32 * y + 16);
				game.getRenderWindow()->draw(*plumTree);
				break;

			case 'G':

				grass->setPosition(32 * x, 32 * y);
				game.getRenderWindow()->draw(*grass);
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



