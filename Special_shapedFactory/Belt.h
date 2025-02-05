#ifndef BELT_H
#define BELT_H

#include <string>

class Belt
{
public:
    Belt(int x, int y, const std::string& direction);

    int getX() const;
    int getY() const;
    std::string getDirection() const;
    void setDirection(const std::string& direction);

private:
    int x;
    int y;
    std::string direction;
};

#endif
