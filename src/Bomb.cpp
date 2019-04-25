#include "Bomb.h"
#include "constants.h"

// Constructor
Bomb::Bomb(int _x, int _y, char _direction) {
    x = _x;
    y = _y;
    direction = _direction;
    timer = BOMB_INITIAL_TIME;
    radius = BOMB_INITIAL_RADIUS;
    speed_x = 0;
    speed_y = 0;
    exploded = false;
    thrown = false;
}
int Bomb::getRadius() {
    return radius;
}
int Bomb::getX() {
    return x;
}
int Bomb::getY() {
    return y;
}
void Bomb::setTime(unsigned int _dt) {
    dt = _dt;
}
void Bomb::setPosition(int _x, int _y, char _direction) {
    x = _x;
    y = _y;
    direction = _direction;
}
void Bomb::moveUp() {
    double dy = (speed_y * dt / 1000);
    if (y - dy - radius >= 0){
        y -= dy;
    } else {
        direction = DIRECTION_DOWN;
        moveDown();
    }
}
void Bomb::moveDown() {
    double dy = (speed_y * dt / 1000);
    if (y + dy + radius <= WINDOW_INITIAL_HEIGHT){
        y += dy;
    } else {
        direction = DIRECTION_UP;
        moveUp();
    }
}
void Bomb::moveLeft() {
    double dx = (speed_x * dt / 1000);
    if (x - dx - radius >= 0){
        x -= dx;
    } else {
        direction = DIRECTION_RIGHT;
        moveRight();
    }
}
void Bomb::moveRight() {
    double dx = (speed_x * dt / 1000);
    if (x + dx + radius <= WINDOW_INITIAL_WIDTH){
        x += dx;
    } else {
        direction = DIRECTION_LEFT;
        moveLeft();
    }
}
void Bomb::updatePosition() {
    switch (direction) {
    case DIRECTION_UP:
        moveUp();
        break;
    case DIRECTION_DOWN:
        moveDown();
        break;
    case DIRECTION_LEFT:
        moveLeft();
        break;
    case DIRECTION_RIGHT:
        moveRight();
        break;
    }
}
void Bomb::updateTimer() {
    timer -= dt;
    if (timer <= 0) {
        explode();
    }
}
void Bomb::bombThrow(int _speed_x, int _speed_y, char _direction) {
    speed_x = _speed_x;
    speed_y = _speed_y;
    direction = _direction;
    thrown = true;
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
