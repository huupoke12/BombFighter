#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

class Player;

class Bomb {
private:
    double timer, blast_factor, speed_x, speed_y;
    int x, y, damage, radius;
    bool exploded, thrown;
    char direction;
    unsigned int dt;
public:
    Bomb(int _x, int _y, char _direction);
    int getRadius();
    int getX();
    int getY();
    double getTimer();
    void setTime(unsigned int _dt);
    void setPosition(int _x, int _y, char _direction);
    void updatePosition();
    void updateTimer();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void bombThrow(int _speed_x, int _speed_y, char _direction);
    void checkExplode(Player &player1, Player &player2);
    void explode(Player &player1, Player &player2);
    bool isExploded();
    bool isThrown();
};


#endif // BOMB_H_INCLUDED
