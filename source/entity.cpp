#include "entity.hpp"
#include "typedefs.hpp"
#include <stdio.h>
#include <string>

Entity::Entity(std::string name, int x, int y) {
    name_ = name;
    x_ = x;
    y_ = y;

    blomCount_ = 0;
    visible_ = true;
}
