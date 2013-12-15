#ifndef __SCENE_HPP_
#define __SCENE_HPP_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "typedefs.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "gui.hpp"

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


    map gameMap;
    Entity *player;
	gui gameGui;


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

	void handleInput(const sf::Event &e);
};

#endif
