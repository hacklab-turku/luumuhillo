#include "scene.hpp"
#include "game.hpp"
#include "audio.hpp"
#include "toolbox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity.hpp"
#include "map.hpp"

Scene::Scene(std::string n)
{
    scenetime = 0;
    aspect_ratio = 1.77; // 16:9 ratio
    name = n;
    initialized = false;
}

void Scene::work()
{
    scenetime++;

    // Do things that the game does on each loop
    for (auto iter = graphics.begin(); iter != graphics.end(); iter++)
    {
        // random movement code to give an idea on updating stuff
        sf::Vector2f tempPos = (*iter)->getPosition();
        tempPos.x = sin(((float)scenetime)*0.01)*10;
        (*iter)->setPosition(tempPos);
    }
	
    static int moveTime;
    if(moveTime < scenetime){
    if(player->HandleInput())
	moveTime = scenetime + 5;
    } 

    gameMap.work();   //modify the map
<<<<<<< HEAD
    gameMap.setDrawGrid(true);
=======
>>>>>>> 3ba78d7c78f19562966b0c007d407bbc4cf5a517

    gameGui.setPlayerPosition(player->GetX(), player->GetY());
    gameGui.setScore(player->GetBlomCount());


	
    // Then render
    render();
}

void Scene::init()
{
    // Initialize a camera view by taking the game's y resolution, and multiplying that by aspect ratio for x size
    mainview = ViewPtr(new sf::View(sf::FloatRect(0, 0,  game.getResolution().y*aspect_ratio, game.getResolution().y)));
    initialized = true;

    player = new Entity("luumunkeraaja", 0, 0);
 
    gameMap.generate();
    gameGui.init();

    // For derps, play a sound
    game.getAudioHandler()->playsound("biisi");
}

void Scene::render()
{   
    mainview->setCenter(player->GetDrawX(), player->GetDrawY());

    game.getRenderWindow()->setView(*mainview);

    gameMap.render(mainview);
    player->Render(mainview);

    // March through the graphics container and render graphics
    for (auto iter = graphics.begin(); iter != graphics.end(); iter++)
    {
        if (*iter == nullptr)
            continue;
        SpritePtr temp = *iter;
        // Don't render what is outside the render area
        if (((*iter)->getPosition().x - (*iter)->getTexture()->getSize().x > mainview->getCenter().x + mainview->getSize().x/2)
            ||
            ((*iter)->getPosition().x + (*iter)->getTexture()->getSize().x < mainview->getCenter().x - mainview->getSize().x/2)
            ||
            
            ((*iter)->getPosition().y + (*iter)->getTexture()->getSize().y < mainview->getCenter().y - mainview->getSize().y/2)
            ||
            ((*iter)->getPosition().y - (*iter)->getTexture()->getSize().y > mainview->getCenter().y + mainview->getSize().y/2)
            )
        {
            continue;
        }
        game.getRenderWindow()->draw(*(*iter));
    }

	gameGui.render(mainview);

}


void Scene::handleInput(const sf::Event &e)
{   
	if (e.type == sf::Event::KeyPressed)
	{

		switch (e.key.code)
		{
		    case sf::Keyboard::G:
				gameMap.setDrawGrid(!gameMap.getDrawGrid());
				break;

		}
	}

}






/**
* Add some graphics to this scene
*/
void Scene::appendGraphics(SpritePtr s)
{
    graphics.push_back(s);
}

/**
* When the window is resized
*/
void Scene::onWindowResize()
{
}


std::string Scene::getName() { return name; }
ViewPtr Scene::getView() { return mainview; }
Vector2fPtr Scene::getCameraTarget() { return camera_target; }
long long Scene::getTime() { return scenetime; }
bool Scene::hasInitialized() { return initialized; }
