#ifndef __SCENEHANDLER_HPP_
#define __SCENEHANDLER_HPP_

#include <vector>
#include "typedefs.hpp"
#include <string>

class Scene;

class SceneHandler
{
private:
    std::vector<ScenePtr> sceneContainer;
    ScenePtr activeScene;
public:
    SceneHandler();

    int init();
    void work();

    ScenePtr findScene(std::string name);
    ScenePtr getActiveScene();
};

#endif
