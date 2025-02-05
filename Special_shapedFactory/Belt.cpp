#include "Belt.h"

Belt::Belt(int x, int y, const std::string& direction)
    : x(x), y(y), direction(direction)
{
}

int Belt::getX() const
{
    return x;
}

int Belt::getY() const
{
    return y;
}

std::string Belt::getDirection() const
{
    return direction;
}

void Belt::setDirection(const std::string& direction)
{
    this->direction = direction;
}
