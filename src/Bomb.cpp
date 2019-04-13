#include "../include/constants.h"

class Bomb {
private:
    float timer, radius;
    int x, y, dx, dy;
public:
    Bomb(int _x, int _y, int _dx, int _dy) {
        x = _x;
        y = _y;
        timer = BOMB_INITIAL_TIME;
        radius = BOMB_INITIAL_RADIUS;
    }
    void explode() {
    }
};
