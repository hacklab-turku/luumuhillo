
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
	SpritePtr maturePlumTree = game.getDataStorage()->getSprite("maturePlumTree");
	SpritePtr pineTree = game.getDataStorage()->getSprite("pineTree");
	SpritePtr grass = game.getDataStorage()->getSprite("grass");
	SpritePtr boulder = game.getDataStorage()->getSprite("boulder");


	for (int x = minX; x < maxX; x++){
	for (int y = minY; y < maxY; y++){

		grass->setPosition(32 * x, 32 * y);
		game.getRenderWindow()->draw(*grass);

		switch (world[x][y]){
			case 'P':
				plumTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*plumTree);
				break;
			case 'M':
				maturePlumTree->setPosition(32 * x, 32 * y + 16);
				game.getRenderWindow()->draw(*maturePlumTree);
				break;
			case 'C':
				pineTree->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*pineTree);
				break;
			case 'B':
				boulder->setPosition(32 * x, 32 * y - 16);
				game.getRenderWindow()->draw(*boulder);
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
		if (rand > 90) world[x][y] = 'P';  //Plum
		else if (rand > 85) world[x][y] = 'C';  //Connifer
		else if (rand > 80) world[x][y] = 'B';  //Boulder
		else if (rand > 85) world[x][y] = 'M';  //mature Plum
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

void map::work()
{
	//sprout "random" plum trees
	int x = std::rand() % MAP_SIZE_X;
	int y = std::rand() % MAP_SIZE_Y;
	if(world[x][y]=='P')
		world[x][y] = 'M';
}
