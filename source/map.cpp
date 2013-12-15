
#include "map.hpp"
#include "game.hpp"
#include "typedefs.hpp"
#include "datastorage.hpp"
#include <random>
#include <vector>


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
	SpritePtr bloomingPlumTree = game.getDataStorage()->getSprite("bloomingPlumTree");
	SpritePtr maturePlumTree = game.getDataStorage()->getSprite("maturePlumTree");
	SpritePtr pineTree = game.getDataStorage()->getSprite("pineTree");
	SpritePtr grass = game.getDataStorage()->getSprite("grass");
	SpritePtr boulder = game.getDataStorage()->getSprite("boulder");
	//render grass
	for (int x = minX; x < maxX; x++){
	for (int y = minY; y < maxY; y++){
		grass->setPosition(32 * x, 32 * y);
		game.getRenderWindow()->draw(*grass);
	}
	}
	
	for (int x = minX; x < maxX; x++){
	for (int y = minY; y < maxY; y++){

		switch (world[x][y]){
			case PLUM_TREE:
				plumTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*plumTree);
				break;
			case BLOOMING_PLUM_TREE:
				bloomingPlumTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*bloomingPlumTree);
				break;
			case MATURE_PLUM_TREE:
				maturePlumTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*maturePlumTree);
				break;
			case PINE_TREE:
				pineTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*pineTree);
				break;
			case BOULDER:
				if(((x<MAP_SIZE_X-1)&&world[x+1][y]==BOULDER) || (y>0&&world[x][y-1]==BOULDER))	//draw an additional boulder if one is nearby
				{
					boulder->setPosition(32 * x-8, 32 * y-16);
					game.getRenderWindow()->draw(*boulder);
					
					boulder->setPosition(32 * x+8, 32 * y);
					game.getRenderWindow()->draw(*boulder);
				}
				else
				{
					boulder->setPosition(32 * x, 32 * y);
					game.getRenderWindow()->draw(*boulder);
				}
				break;

		}	
	}
	}

	
	if (drawGrid){
		std::vector<sf::Vertex> lines;
		int i = 0;
		for (int x = minX; x < maxX; x++){
			lines.push_back(sf::Vertex(sf::Vector2f(x * 32, 0)));
			lines.push_back(sf::Vertex(sf::Vector2f(x * 32, MAP_SIZE_Y * 32)));
			i++;
		}
		game.getRenderWindow()->draw(lines.data(), i * 2, sf::Lines);


		lines.clear();
		i = 0;

		for (int y = minY; y < maxY; y++){
			lines.push_back(sf::Vertex(sf::Vector2f(0, y * 32)));
			lines.push_back(sf::Vertex(sf::Vector2f(MAP_SIZE_X * 32, y * 32)));
			i++;
		}
		game.getRenderWindow()->draw(lines.data(), i * 2, sf::Lines);
	}

}


void map::generate()
{

	for (int x = 0; x < MAP_SIZE_X; x++){
	for (int y = 0; y < MAP_SIZE_Y; y++){
		int rand = std::rand() % 100;
		if (rand > 90) world[x][y] = PLUM_TREE;
		else if (rand > 85) world[x][y] = BLOOMING_PLUM_TREE;
		else if (rand > 80) world[x][y] = PINE_TREE;
		else if (rand > 75) genBoulders(x,y);
		else  world[x][y] = GRASS;
	}
	}

}

void map::genBoulders(int x, int y)	//generate a wall of boulders
{
	while(1)
	{
		world[x][y]=BOULDER;
		int rand = std::rand() % 5;
		switch(rand)
		{
			case 0:		//end the boulder wall
				return;
			case 1:
				x++;
				if(x>MAP_SIZE_X) return;
				break;
			case 2:
				x--;
				if(x<0) return;
				break;
			case 3:
				y++;
				if(y>MAP_SIZE_Y) return;
				break;
			case 4:
				y--;
				if(y<0) return;
				break;
		}
	}
}

bool map::isSolid(int x, int y)
{
	if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y)
		return true;
	if(world[x][y]==BOULDER) return true; 
	if(world[x][y]==PINE_TREE) return true;
	return false;
}


char map::getCellData(int x, int y)
{
	if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y)
		return 'E'; //Off edge
	return world[x][y];

}

void map::work()
{
	//mature a plum tree at a random location
	int x = std::rand() % MAP_SIZE_X;
	int y = std::rand() % MAP_SIZE_Y;
	if(world[x][y]==BLOOMING_PLUM_TREE)
		world[x][y] = MATURE_PLUM_TREE; 
	if(world[x][y]==PLUM_TREE)
		world[x][y] = BLOOMING_PLUM_TREE;
}
