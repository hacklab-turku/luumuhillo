
#include "gui.hpp"
#include <iostream>
#include <string>
#include <sstream>
gui::gui()
{

}

void gui::init()
{
	if (!font.loadFromFile("./data/CosmicSansNeueMono.ttf"))
	{
		std::cout << "Font loading failed!" << std::endl;

	}

	position.setFont(font);
	position.setPosition(600,0);
	score.setFont(font);
	score.setPosition(20,0);
}

void gui::render(ViewPtr view)
{
	position.setPosition(view->getCenter());
	position.move(-500, -300);
	game.getRenderWindow()->draw(position);
	
	score.setPosition(view->getCenter());
	score.move(300, -300);
	game.getRenderWindow()->draw(score);

}

void gui::setPlayerPosition(int x, int y)
{
    std::stringstream ss;
    ss << "Position: x:" << x << " y: " << y ;
	
	position.setString(ss.str());
}

void gui::setScore(int score)
{
    std::stringstream ss;
    ss << "Score:" << score ;
	
	this->score.setString(ss.str());
}

