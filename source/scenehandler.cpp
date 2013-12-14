#include "scenehandler.hpp"
#include "scene.hpp"
#include "game.hpp"
#include "datastorage.hpp"
#include <algorithm>

/**
* This class keeps track of all created scenes
* It tells the game which scene to update and draw
* and has utility functions for storing and loading scenes
*/

SceneHandler::SceneHandler()
{
}

void SceneHandler::work()
{
    if (activeScene->hasInitialized() == false)
        activeScene->init();
    activeScene->work();
}

/**
* Creates the world and its scenes
*/
int SceneHandler::init()
{
    ScenePtr scene1(new Scene("first scene"));
    sceneContainer.push_back(scene1);
    activeScene = scene1;

   // scene1->appendGraphics(game.getDataStorage()->getSprite("logo"));

    return 0;
}

/**
* Finds the scenecontainer for a scene with matching name
* Returns a shared_ptr to the scene is found, else nullptr
*/
ScenePtr SceneHandler::findScene(std::string name)
{
    std::vector<ScenePtr>::iterator iter;
    iter = std::find_if(sceneContainer.begin(), sceneContainer.end(),
        [name](ScenePtr i)
        {
            return name == i->getName();
        });
    if (iter != sceneContainer.end())
        return (*iter);
    return nullptr;
}

ScenePtr SceneHandler::getActiveScene() { return activeScene; }
