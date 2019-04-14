#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


// Window

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Bomb Fighter";

// Player

const int PLAYER_INITIAL_HEALTH = 100;
const int PLAYER_INITIAL_SPEED = 50;
const int PLAYER_INITIAL_MAX_BOMB = 2;

const char PLAYER_DIRECTION_UP = '2';
const char PLAYER_DIRECTION_LEFT = '4';
const char PLAYER_DIRECTION_RIGHT = '6';
const char PLAYER_DIRECTION_DOWN = '8';

// Bomb
const float BOMB_INITIAL_TIME = 5;
const float BOMB_INITIAL_RADIUS = 10;
const int BOMB_INITIAL_SPEED = 100;

#endif // CONSTANTS_H_INCLUDED
