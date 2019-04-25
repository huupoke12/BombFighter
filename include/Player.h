#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

#include "Bomb.h"

class Player {
private:
    int x, y, width, height, speed_x, speed_y, health;
    int max_bomb;
    char direction;
    bool holding_bomb;
    std::vector<Bomb> bombs;
    unsigned int dt;

public:
    void init(int _x, int _y, int _width, int _height, int _speed_x, int _speed_y, int _health, int _max_bomb, char _direction);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    char getDirection();
    std::vector<Bomb>& getBombs();
    void setTime(unsigned int dt);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void injure(int damage);
    void createBomb();
    void throwBomb();
    void useBomb();
    void useShield();
    bool isDead();
};


#endif // PLAYER_H_INCLUDED
