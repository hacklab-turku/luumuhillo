#include "game.hpp"
#include "configreader.hpp"
#include "datastorage.hpp"
#include "input.hpp"
#include "toolbox.hpp"
#include "scenehandler.hpp"
#include "scene.hpp"
#include "audio.hpp"
#include "server.hpp"

/**
* Singleton instance on the game class
* include game.hpp and you can call "game.somethingHere()" freely
* Generally you will want to access the other parts of the game
* by first calling game and then using a getter method for accessing a manager
* For example, game.getAudioStorage()->getSound("cool_song.ogg");
*/
Game game;

Game::Game()
{
    gamestate = GameState::GameState_Loading;

    // Construct all manager classes
    configreader = ConfigReaderPtr(new ConfigReader());
    datastorage = DataStoragePtr(new DataStorage());
    input = InputPtr(new Input());
    toolbox = ToolboxPtr(new Toolbox());
    scenehandler = SceneHandlerPtr(new SceneHandler());
    audiohandler = AudioPtr(new Audio());
    server = ServerPtr(new Server());
}

/**
* Inits all manager classes
* Loads the game's content
* And generally prepares the game for playing
*/
int Game::start()
{

    if (configreader->readConfig() != 0)
        return -1;

    // Init SFML window
    renderwindow = RenderWindowPtr(new sf::RenderWindow());
    renderwindow->create(sf::VideoMode(resolution.x, resolution.y), "Cool game project");
    renderwindow->setFramerateLimit(framerate);

    if (datastorage->loadInitialData() != 0)
        return -1;

    // Insert cool loading screen

    if (datastorage->loadAllData() != 0)
        return -1;

    if (scenehandler->init() != 0)
        return -1;

    running = true;
    return 0;
}

int Game::exit()
{
    // Close systems that refer to SFML

    // Close SFML itself
    if (renderwindow->isOpen())
        renderwindow->close();

    // Close systems that don't refer to SFML

    return 0;
}

int Game::mainloop()
{
    // Timers for recording FPS
    int fps = 0;
    int nextFPS = 3;
    sf::Clock fps_clock;
    sf::Clock main_clock;

    // Enter main loop
    while (isRunning())
    {
        gamestate = GameState::GameState_NewLoop;

        // Calculate FPS
        fps = 1 / fps_clock.getElapsedTime().asSeconds();
        fps_clock.restart();

        if (main_clock.getElapsedTime().asSeconds() > nextFPS)
        {
            // Update FPS once a second
            nextFPS += 1;
            renderwindow->setTitle(toolbox->combineStringAndInt("Current FPS: ", fps));
        }

        gamestate = GameState::GameState_Input;
        input->handleinput();

        // Clear screen for new update
        renderwindow->clear();

        gamestate = GameState::GameState_Logic;
        // Call scenehandler to work on the active scene
        scenehandler->work();

        gamestate = GameState::GameState_Rendering;
        if (renderwindow->isOpen())
            renderwindow->display();

        loopend();
    }

    return 0;
}

bool Game::isRunning()
{
    return running;
}

/**
* Tell we wish to close the game at next loop
*/
void Game::signalGameExit()
{
    running = false;
}

void Game::loopend()
{
    if (running == false)
        exit();
}

void Game::setResolution(sf::Vector2i r) { resolution = r; }
sf::Vector2i Game::getResolution() { return resolution; }
GameState Game::getGameState() { return gamestate; }
RenderWindowPtr Game::getRenderWindow() { return renderwindow; }
ToolboxPtr Game::getToolbox() { return toolbox; }
DataStoragePtr Game::getDataStorage() { return datastorage; }
SceneHandlerPtr Game::getSceneHandler() { return scenehandler; }
AudioPtr Game::getAudioHandler() { return audiohandler; }
ServerPtr Game::getServer() { return server; }

