#include "Cutter.h"

Cutter::Cutter(int x, int y, const std::string& direction)
    : x(x), y(y), direction(direction)
{
}

int Cutter::getX() const
{
    return x;
}

int Cutter::getY() const
{
    return y;
}

std::string Cutter::getDirection() const
{
    return direction;
}
