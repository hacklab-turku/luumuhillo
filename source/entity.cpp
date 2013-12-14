#include "entity.hpp"
#include "typedefs.hpp"

Entity::Entity(int x, int y) {
    //name_ = name;
    x_ = x;
    y_ = y;

    blomCount_ = 0;
    visible_ = true;
}
