#include "Player.h"
#include "constants.h"

void Player::init(int _x, int _y, int _width, int _height, int _speed, int _health, int _max_bomb, char _direction) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    speed = _speed;
    health = _health;
    max_bomb = _max_bomb;
    direction = _direction;
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
// TODO: Replace the constants by present width and height
void Player::moveLeft() {
    if (x - speed - width / 2 >= 0){
        x -= speed;
    }
    direction = DIRECTION_LEFT;
}
void Player::moveRight() {
    if (x + speed + width / 2 <= WINDOW_INITIAL_WIDTH){
        x += speed;
    }
    direction = DIRECTION_RIGHT;
}
void Player::moveUp() {
    if (y - speed - height / 2 >= 0){
        y -= speed;
    }
    direction = DIRECTION_UP;
}
void Player::moveDown() {
    if (y + speed + height / 2 <= WINDOW_INITIAL_HEIGHT){
        y += speed;
    }
    direction = DIRECTION_DOWN;
}
void Player::injure(int damage) {
    health -= damage;
}
void Player::createBomb() {
    bomb_bag.push_back(Bomb(x, y));
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
    bomb_bag.back().beingThrown(bomb_dx, bomb_dy);
}
bool Player::isDead() {
    return (health <= 0) ? true : false;
}
