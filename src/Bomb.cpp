#include "Bomb.h"
#include "constants.h"

// Constructor
Bomb::Bomb(int _x, int _y) {
    x = _x;
    y = _y;
    timer = BOMB_INITIAL_TIME;
    radius = BOMB_INITIAL_RADIUS;
    exploded = false;
}
void Bomb::explode() {
    //player1.injure();
    //player2.injure();
    exploded = true;
}
bool Bomb::isExploded() {
    return exploded;
}
void Bomb::beingThrown(int _dx, int _dy) {
    dx = _dx;
    dy = _dy;
}
