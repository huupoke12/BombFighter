#include <cmath>

#include "Player.h"
#include "Bomb.h"
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
int Player::getHealth() {
    return health;
}
std::vector<Bomb>& Player::getBombs() {
    return bombs;
}
void Player::setTime(unsigned int _dt) {
    dt = _dt;
}
void Player::setHoldingBomb(bool _holding_bomb) {
    holding_bomb = _holding_bomb;
}
// TODO: Replace the constants by variables
void Player::moveLeft(Player &enemy) {
    double dx = (speed_x * dt / 1000);
    bool x_collide = ((x - dx - width / 2) <= (enemy.getX() + enemy.getWidth() / 2)) && ((x - dx - width / 2) >= (enemy.getX() - enemy.getWidth() / 2));
    bool enemy_collide = (x_collide && (abs(y - enemy.getY()) - height / 2 - enemy.getHeight() / 2) <= 0);
    if ((x - dx - width / 2 >= 0) && !enemy_collide) {
        x -= dx;
    }
    direction = DIRECTION_LEFT;
}
void Player::moveRight(Player &enemy) {
    double dx = (speed_x * dt / 1000);
    bool x_collide = ((x + dx + width / 2) >= (enemy.getX() - enemy.getWidth() / 2)) && ((x + dx + width / 2) <= (enemy.getX() + enemy.getWidth() / 2));
    bool enemy_collide = (x_collide && (abs(y - enemy.getY()) - height / 2 - enemy.getHeight() / 2) <= 0);
    if ((x + dx + width / 2 <= WINDOW_INITIAL_WIDTH) && !enemy_collide) {
        x += dx;
    }
    direction = DIRECTION_RIGHT;
}
void Player::moveUp(Player &enemy) {
    double dy = (speed_y * dt / 1000);
    bool y_collide = ((y - dy - height / 2) <= (enemy.getY() + enemy.getHeight() / 2)) && ((y - dy - height / 2) >= (enemy.getY() - enemy.getHeight() / 2));
    bool enemy_collide = (y_collide && (abs(x - enemy.getX()) - width / 2 - enemy.getWidth() / 2) <= 0);
    if ((y - dy - height / 2 >= 0) && !enemy_collide) {
        y -= dy;
    }
    direction = DIRECTION_UP;
}
void Player::moveDown(Player &enemy) {
    double dy = (speed_y * dt / 1000);
    bool y_collide = ((y + dy + height / 2) >= (enemy.getY() - enemy.getHeight() / 2)) && ((y + dy + height / 2) <= (enemy.getY() + enemy.getHeight() / 2));
    bool enemy_collide = (y_collide && (abs(x - enemy.getX()) - width / 2 - enemy.getWidth() / 2) <= 0);
    if ((y + dy + height / 2 <= WINDOW_INITIAL_HEIGHT) && !enemy_collide) {
        y += dy;
    }
    direction = DIRECTION_DOWN;
}
void Player::injure(int damage) {
    health -= damage;
}

void Player::useBomb() {
    if (holding_bomb) {
        bombs.back().bombThrow(BOMB_INITIAL_SPEED_X, BOMB_INITIAL_SPEED_Y, direction);
        holding_bomb = false;
    } else if (bombs.size() < max_bomb) {
        int bomb_x, bomb_y;
        switch (direction) {
        case DIRECTION_UP:
            bomb_x = x;
            bomb_y = y - height / 2 - BOMB_INITIAL_RADIUS;
            break;
        case DIRECTION_RIGHT:
            bomb_x = x + width / 2 + BOMB_INITIAL_RADIUS;
            bomb_y = y;
            break;
        case DIRECTION_DOWN:
            bomb_x = x;
            bomb_y = y + height / 2 + BOMB_INITIAL_RADIUS;
            break;
        case DIRECTION_LEFT:
            bomb_x = x - width / 2 - BOMB_INITIAL_RADIUS;
            bomb_y = y;
            break;
        default:
            bomb_x = 0;
            bomb_y = 0;
        }
        bombs.push_back(Bomb(bomb_x, bomb_y, direction));
        holding_bomb = true;
    }
}
void Player::useShield() {
}
bool Player::isDead() {
    return (health <= 0) ? true : false;
}
