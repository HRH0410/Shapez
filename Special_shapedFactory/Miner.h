#ifndef MINER_H
#define MINER_H

#include <string>

class Miner
{
public:
    Miner(int x, int y, const std::string& direction);

    int getX() const;
    int getY() const;
    std::string getDirection() const;

private:
    int x;
    int y;
    std::string direction;
};

#endif // MINER_H
