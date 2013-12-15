#include <string>
#include <stdio.h>

#include "game.hpp"
#include "datastorage.hpp"
#include "typedefs.hpp"
#include "entity.hpp"
#include "SFML/System.hpp"

Entity::Entity(std::string name, int x, int y) {
    name_ = name;
    sprite_ = game.getDataStorage()->getSprite("player");
    x_ = x;
    y_ = y;

    drawX_ = x * 32;
    drawY_ = y * 32;

    blomCount_ = 0;
    visible_ = true;
}

void Entity::Render(ViewPtr view) {
    sprite_->setPosition(drawX_, drawY_);
    game.getRenderWindow()->draw(*sprite_);
}

bool Entity::HandleInput() {
   bool didMove = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x_--;
	drawX_ -= 32;
	didMove = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x_++;
	drawX_ += 32;
	didMove = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y_--;
	drawY_ -= 32;
	didMove = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y_++;
	drawY_ += 32;
	didMove = true;
    }
    return didMove;
}
