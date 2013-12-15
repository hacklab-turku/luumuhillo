#include "input.hpp"
#include "scene.hpp"
#include "scenehandler.hpp"
#include "game.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

Input::Input()
{
}

/**
* Handles input for the game's main renderwindow
*/
void Input::handleinput()
{
    sf::Event e;

    while (game.getRenderWindow()->pollEvent(e))
    {
        switch (e.type)
        {
            case sf::Event::Closed:
                game.signalGameExit();
                break;
            case sf::Event::Resized:
                game.getSceneHandler()->getActiveScene()->onWindowResize();
                break;
            case sf::Event::KeyReleased:
                switch (e.key.code)
                {
                    case sf::Keyboard::T:
                        // What happens on key RELEASE
                        break;
                }
                break;
            case sf::Event::KeyPressed:
                switch (e.key.code)
                {
                    case sf::Keyboard::Escape:
                        // What happens on key press
                        game.signalGameExit();
                        break;
                }
            break;
        }
    }

    // Events for things like "X is constantly being pressed down"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        int i;
        // What happens when X is constantly down
    }
    else
    {
        // What about when up
    }
}
