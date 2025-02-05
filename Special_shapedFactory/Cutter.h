#ifndef CUTTER_H
#define CUTTER_H

#include <string>

class Cutter
{
public:
    Cutter(int x, int y, const std::string& direction);

    int getX() const;
    int getY() const;
    std::string getDirection() const;

private:
    int x;
    int y;
    std::string direction;
};

#endif // CUTTER_H
