#include "Bomb.h"
#include "constants.h"

// Constructor
Bomb::Bomb(int _x, int _y) {
    x = _x;
    y = _y;
    timer = BOMB_INITIAL_TIME;
    radius = BOMB_INITIAL_RADIUS;
    exploded = false;
    thrown = false;
}
void Bomb::bombThrow() {
}
void Bomb::explode() {
    //player1.injure();
    //player2.injure();
    exploded = true;
}
bool Bomb::isExploded() {
    return exploded;
}
bool Bomb::isThrown() {
    return thrown;
}
