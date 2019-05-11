#include <cmath>
#include <iostream>
#include "Bomb.h"
#include "Player.h"
#include "constants.h"

// Constructor
Bomb::Bomb(int _x, int _y, char _direction) {
    x = _x;
    y = _y;
    direction = _direction;
    timer = BOMB_INITIAL_TIME;
    damage = BOMB_INITIAL_DAMAGE;
    radius = BOMB_INITIAL_RADIUS;
    blast_factor = BOMB_INITIAL_BLAST_FACTOR;
    decel_x = BOMB_INITIAL_DECELERATION_X;
    decel_y = BOMB_INITIAL_DECELERATION_Y;
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
int Bomb::getTimer() {
    return timer;
}
void Bomb::setTime(unsigned int _dt) {
    dt = _dt;
}
void Bomb::setPosition(int _x, int _y, char _direction) {
    x = _x;
    y = _y;
    direction = _direction;
}
void Bomb::updateSpeed() {
    double new_speed_x = speed_x - decel_x * dt / 1000;
    double new_speed_y = speed_y - decel_y * dt / 1000;
    if (new_speed_x > 0) {
        speed_x = new_speed_x;
    } else {
        speed_x = 0;
    }
    if (new_speed_y > 0) {
        speed_y = new_speed_y;
    } else {
        speed_y = 0;
    }
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
}
void Bomb::bombThrow(int _speed_x, int _speed_y, char _direction) {
    speed_x = _speed_x;
    speed_y = _speed_y;
    direction = _direction;
    thrown = true;
}
void Bomb::checkExplode(Player &player1, Player &player2) {
    bool collide1 = ((abs(player1.getX() - x) - radius - player1.getWidth() / 2) < 0) && ((abs(player1.getY() - y) - radius - player1.getHeight() / 2) < 0);
    bool collide2 = ((abs(player2.getX() - x) - radius - player2.getWidth() / 2) < 0) && ((abs(player2.getY() - y) - radius - player2.getHeight() / 2) < 0);
    if ((thrown && (collide1 || collide2) ) || timer <= 0) {
        explode(player1, player2);
    }
}
void Bomb::explode(Player &player1, Player &player2) {
    double distance1 = sqrt(pow(abs(player1.getX() - x), 2) + pow(abs(player1.getY() - y), 2));
    double distance2 = sqrt(pow(abs(player2.getX() - x), 2) + pow(abs(player2.getY() - y), 2));
    int damage1 = damage * (blast_factor * radius / pow(distance1, 1.5));
    int damage2 = damage * (blast_factor * radius / pow(distance2, 1.5));
    if (damage1 > 0) {
        player1.injure(damage1);
    }
    if (damage2 > 0) {
        player2.injure(damage2);
    }
    exploded = true;

    std::cout << "Player1's HP: " << player1.getHealth() << std::endl;
    std::cout << "Player2's HP: " << player2.getHealth() << std::endl;
}
bool Bomb::isExploded() {
    return exploded;
}
bool Bomb::isThrown() {
    return thrown;
}
