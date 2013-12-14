#ifndef __SCENE_HPP_
#define __SCENE_HPP_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "typedefs.hpp"

class Scene
{
private:
    std::string name;
    std::vector<SpritePtr> graphics;
    ViewPtr mainview;
    Vector2fPtr camera_target;

    long long scenetime;

    sf::Vector2f display_area;
    sf::Vector2f display_ratio;
    sf::Vector2f display_offset;
    float aspect_ratio;

    bool initialized;
public:
    Scene(std::string n);

    void init();
    void work();
    void render();
    void onWindowResize();

    ViewPtr getView();
    Vector2fPtr getCameraTarget();
    void appendGraphics(SpritePtr s);
    std::string getName();
    long long getTime();
    bool hasInitialized();
};

#endif
