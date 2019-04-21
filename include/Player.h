#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

#include "Bomb.h"

class Player {
private:
    int x, y, speed, health;
    int max_bomb;
    char direction;
    std::vector<Bomb> bomb_bag;

public:
    void init(int _x, int _y, char _direction);
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
