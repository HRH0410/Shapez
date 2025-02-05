#include "Trash.h"

Trash::Trash(int x, int y, const std::string& direction)
    : x(x), y(y), direction(direction)
{
}

int Trash::getX() const
{
    return x;
}

int Trash::getY() const
{
    return y;
}

std::string Trash::getDirection() const
{
    return direction;
}
