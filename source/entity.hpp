//#include <string>
//#include "typedefs.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
    Entity(std::string name, int x, int y);
    void Render(ViewPtr view);
    bool HandleInput();
    
    void SetX(int x) { x_ = x; drawX_ = x * 32;}
    void SetY(int y) { y_ = y; drawY_ = y * 32;}
    void SetBlomCount(unsigned int blomcount) { blomCount_ = blomcount; }

    bool IsVisible() { return visible_; }
    int GetX() { return x_; }
    int GetY() { return y_; }
    int GetDrawX() { return drawX_; }
    int GetDrawY() { return drawY_; }
    unsigned int GetBlomCount() { return blomCount_; }

private:
    int x_;
    int y_;
    int drawX_;
    int drawY_;
    int blomCount_;
    bool visible_;
    std::string name_;

    SpritePtr sprite_;
};

#endif // ENTITY_HPP
