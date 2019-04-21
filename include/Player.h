#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

#include "Bomb.h"

class Player {
private:
    int x, y, width, height, speed, health;
    int max_bomb;
    char direction;
    std::vector<Bomb> bomb_bag;

public:
    void init(int _x, int _y, int _width, int _height, int speed, int _health, int max_bomb, char _direction);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
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
