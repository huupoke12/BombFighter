#include <vector>

#include "Bomb.cpp"

class Player {
private:
    int x, y, speed, health;
    size_t max_bomb;
    char direction;
    std::vector<Bomb> bomb_bag;

public:
    Player(int _x, int _y, int _direction) {
        health = PLAYER_INITIAL_HEALTH;
        speed = PLAYER_INITIAL_SPEED;
        max_bomb = PLAYER_INITIAL_MAX_BOMB;
        direction = _direction;
    }
    void moveLeft() {
        x -= speed;
        direction = PLAYER_DIRECTION_LEFT;
    }
    void moveRight() {
        x += speed;
        direction = PLAYER_DIRECTION_RIGHT;
    }
    void moveUp() {
        y -= speed;
        direction = PLAYER_DIRECTION_UP;
    }
    void moveDown() {
        y += speed;
        direction = PLAYER_DIRECTION_DOWN;
    }
    void injure(int damage) {
        health -= damage;
    }
    void createBomb() {
        bomb_bag.push_back(Bomb(x, y, 0, 0));
    }
    void throwBomb() {

    }
    bool isDead() {
        return (health <= 0) ? true : false;
    }
};
