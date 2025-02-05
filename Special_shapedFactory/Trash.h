#ifndef TRASH_H
#define TRASH_H

#include <string>

class Trash
{
public:
    Trash(int x, int y, const std::string& direction);

    int getX() const;
    int getY() const;
    std::string getDirection() const;

private:
    int x;
    int y;
    std::string direction;
};

#endif // TRASH_H
