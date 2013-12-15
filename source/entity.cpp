#include <string>
#include <stdio.h>

#include "game.hpp"
#include "datastorage.hpp"
#include "typedefs.hpp"
#include "entity.hpp"

Entity::Entity(std::string name, int x, int y) {
    name_ = name;
    sprite_ = game.getDataStorage()->getSprite("player");
    x_ = x;
    y_ = y;

    blomCount_ = 0;
    visible_ = true;
}

void Entity::Render(ViewPtr view) {
    sprite_->setPosition(200, 200);
    game.getRenderWindow()->draw(*sprite_);
}
