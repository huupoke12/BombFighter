#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

#include "Bomb.h"

class Player {
private:
    int x, y, width, height, speed, health;
    int max_bomb;
    char direction;
    std::vector<Bomb> bombs;
    unsigned int dt;

public:
    void init(int _x, int _y, int _width, int _height, int _speed, int _health, int _max_bomb, char _direction);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    char getDirection();
    void setTime(unsigned int dt);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void injure(int damage);
    void createBomb();
    void throwBomb();
    bool isDead();
};


#endif // PLAYER_H_INCLUDED
