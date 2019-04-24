#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

class Bomb {
private:
    double timer, radius;
    int x, y, dx, dy;
    bool exploded, thrown;
public:
    Bomb(int _x, int _y);
    void bombThrow();
    void explode();
    bool isExploded();
    bool isThrown();
};


#endif // BOMB_H_INCLUDED
