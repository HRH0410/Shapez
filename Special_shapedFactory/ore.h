#ifndef ORE_H
#define ORE_H

#include <QPixmap>

class Ore {
public:
    Ore(int x, int y, const std::string& direction ,const std::string& type ,const QPixmap& pixmap);

    int getX() const;
    int getY() const;

    QPixmap getPixmap() const;
    std::string getDirection() const;
    std::string getType() const;
    void setPosition(int newX, int newY);
    void setDirection(const std::string& newDirection);
    void setType(const std::string& Type);

private:
    int x;
    int y;
    QPixmap pixmap;
    std::string direction;
    std::string type;

};


#endif // ORE_H
