#include "Player.h"
#include "constants.h"

// Constructor
Player::Player(int _x, int _y, char _direction) {
    health = PLAYER_INITIAL_HEALTH;
    speed = PLAYER_INITIAL_SPEED;
    max_bomb = PLAYER_INITIAL_MAX_BOMB;
    direction = _direction;
}
void Player::moveLeft() {
    x -= speed;
    direction = PLAYER_DIRECTION_LEFT;
}
void Player::moveRight() {
    x += speed;
    direction = PLAYER_DIRECTION_RIGHT;
}
void Player::moveUp() {
    y -= speed;
    direction = PLAYER_DIRECTION_UP;
}
void Player::moveDown() {
    y += speed;
    direction = PLAYER_DIRECTION_DOWN;
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
    case PLAYER_DIRECTION_LEFT:
        bomb_dx = -BOMB_INITIAL_SPEED;
        break;
    case PLAYER_DIRECTION_RIGHT:
        bomb_dx = BOMB_INITIAL_SPEED;
        break;
    case PLAYER_DIRECTION_UP:
        bomb_dy = -BOMB_INITIAL_SPEED;
        break;
    case PLAYER_DIRECTION_DOWN:
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
