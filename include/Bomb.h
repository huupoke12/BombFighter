#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

class Bomb {
private:
    float timer, radius;
    int x, y, dx, dy;
    bool exploded;
public:
    Bomb(int _x, int _y);
    void explode();
    bool isExploded();
    void beingThrown(int _dx, int _dy);
};


#endif // BOMB_H_INCLUDED
