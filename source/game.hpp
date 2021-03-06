#ifndef __GAME_HPP_
#define __GAME_HPP_

/**
* The main class that runs the main loop
* Contains pointers to all manager classes and asks them to work
* during each loop
*/

#include <memory>
#include "typedefs.hpp"
#include <SFML/Graphics.hpp>

class Game
{
private:
    // Manager classes
    DataStoragePtr datastorage;
    ConfigReaderPtr configreader;
    InputPtr input;
    ToolboxPtr toolbox;
    SceneHandlerPtr scenehandler;
    AudioPtr audiohandler;
    ServerPtr server;
    NetworkedInputPtr networkedInput;

    // Game's current state
    GameState gamestate;

    // SFML stuff
    RenderWindowPtr renderwindow;
    bool running;
    unsigned int framerate;
    sf::Vector2i resolution;

    long gameRunningTime;

    int fps;
    int nextFPS;

    sf::Clock fps_clock;
    sf::Clock main_clock;

    MutexPtr clockMutex;
    MutexPtr networked_input_mutex;

public:
    Game();
    int start();
    int exit();

    int loop();

    void loopend();
    bool isRunning();

    void signalGameExit();
    void setResolution(sf::Vector2i r);
    sf::Vector2i getResolution();
    DataStoragePtr getDataStorage();
    ConfigReaderPtr getConfigReader();
    ToolboxPtr getToolbox();
    GameState getGameState();
    RenderWindowPtr getRenderWindow();
    SceneHandlerPtr getSceneHandler();
    AudioPtr getAudioHandler();
    ServerPtr getServer();
    NetworkedInputPtr getNetworkedInput();

    long getGameRunningTime();
};

extern Game game;

#endif
