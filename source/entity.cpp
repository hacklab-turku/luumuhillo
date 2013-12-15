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

    blomCount_ = 0;
    visible_ = true;
}

void Entity::Render(ViewPtr view) {
    sprite_->setPosition(x_, y_);
    game.getRenderWindow()->draw(*sprite_);
}

bool Entity::HandleInput() {
	bool didMove = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x_ -= 32;
		didMove = true;
        // What happens when X is constantly down
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x_ += 32;
		didMove = true;
        // What happens when X is constantly down
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y_ -= 32;
		didMove = true;
        // What happens when X is constantly down
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y_ += 32;
		didMove = true;
        // What happens when X is constantly down
    }
	return didMove;
}
