#include "Miner.h"

Miner::Miner(int x, int y, const std::string& direction)
    : x(x), y(y), direction(direction)
{
}

int Miner::getX() const
{
    return x;
}

int Miner::getY() const
{
    return y;
}

std::string Miner::getDirection() const
{
    return direction;
}
