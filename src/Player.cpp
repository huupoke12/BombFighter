#include "Player.h"
#include "constants.h"

void Player::init(int _x, int _y, int _width, int _height, int _speed_x, int _speed_y, int _health, int _max_bomb, char _direction) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    speed_x = _speed_x;
    speed_y = _speed_y;
    health = _health;
    max_bomb = _max_bomb;
    direction = _direction;
    holding_bomb = false;
}
int Player::getX() {
    return x;
}
int Player::getY() {
    return y;
}
int Player::getWidth() {
    return width;
}
int Player::getHeight() {
    return height;
}
char Player::getDirection() {
    return direction;
}
void Player::setTime(unsigned int _dt) {
    dt = _dt;
}

// TODO: Replace the constants by variables
void Player::moveLeft() {
    double dx = (speed_x * dt / 1000);
    if (x - dx - width / 2 >= 0){
        x -= dx;
    }
    direction = DIRECTION_LEFT;
}
void Player::moveRight() {
    double dx = (speed_x * dt / 1000);
    if (x + dx + width / 2 <= WINDOW_INITIAL_WIDTH){
        x += dx;
    }
    direction = DIRECTION_RIGHT;
}
void Player::moveUp() {
    double dy = (speed_y * dt / 1000);
    if (y - dy - height / 2 >= 0){
        y -= dy;
    }
    direction = DIRECTION_UP;
}
void Player::moveDown() {
    double dy = (speed_y * dt / 1000);
    if (y + dy + height / 2 <= WINDOW_INITIAL_HEIGHT){
        y += dy;
    }
    direction = DIRECTION_DOWN;
}
void Player::injure(int damage) {
    health -= damage;
}
void Player::createBomb() {
    bombs.push_back(Bomb(x, y));
}
void Player::throwBomb() {
    int bomb_dx = 0;
    int bomb_dy = 0;
    switch (direction) {
    case DIRECTION_LEFT:
        bomb_dx = -BOMB_INITIAL_SPEED;
        break;
    case DIRECTION_RIGHT:
        bomb_dx = BOMB_INITIAL_SPEED;
        break;
    case DIRECTION_UP:
        bomb_dy = -BOMB_INITIAL_SPEED;
        break;
    case DIRECTION_DOWN:
        bomb_dy = BOMB_INITIAL_SPEED;
        break;
    default:
        break;
    }
    //bomb_bag.back().bombThrow(bomb_dx, bomb_dy);
}
void Player::useBomb() {
    if (holding_bomb) {
        bombs.back().bombThrow();
        holding_bomb = false;
    } else {
        bombs.push_back(Bomb(x, y));
        holding_bomb = true;
    }
}
void Player::useShield() {
}
bool Player::isDead() {
    return (health <= 0) ? true : false;
}
