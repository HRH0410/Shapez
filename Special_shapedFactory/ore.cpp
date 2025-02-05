#include "ore.h"

Ore::Ore(int x, int y,const std::string& direction,const std::string& type, const QPixmap& pixmap)
    : x(x), y(y), direction(direction ) ,pixmap(pixmap),type(type){}

int Ore::getX() const { return x; }
int Ore::getY() const { return y; }


QPixmap Ore::getPixmap() const { return pixmap; }
std::string Ore::getDirection() const { return direction; }
std::string Ore::getType() const{return type;}

void Ore::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Ore::setDirection(const std::string& newDirection) {
    direction=newDirection;
}

void Ore::setType(const std::string& Type){
    type=Type;
}

