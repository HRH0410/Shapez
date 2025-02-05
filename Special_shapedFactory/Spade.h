#ifndef SPADE_H
#define SPADE_H

class Spade
{
public:
    Spade(int x, int y);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
};

#endif // SPADE_H
