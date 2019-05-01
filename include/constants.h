#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


const char GAME_TITLE[] = "Bomb Fighter";

// Window

const int WINDOW_INITIAL_WIDTH = 1280;
const int WINDOW_INITIAL_HEIGHT = 720;
const int WINDOW_INITIAL_FPS = 120;

// Direction
const char DIRECTION_UP = '2';
const char DIRECTION_LEFT = '4';
const char DIRECTION_RIGHT = '6';
const char DIRECTION_DOWN = '8';

const double ROTATE_UP_ANGLE = 0;
const double ROTATE_RIGHT_ANGLE = 90;
const double ROTATE_DOWN_ANGLE = 180;
const double ROTATE_LEFT_ANGLE = 270;

// Player

const int PLAYER_INITIAL_HEALTH = 100;
const int PLAYER_INITIAL_SPEED_X = WINDOW_INITIAL_WIDTH / 2;
const int PLAYER_INITIAL_SPEED_Y = PLAYER_INITIAL_SPEED_X;
const int PLAYER_INITIAL_MAX_BOMB = 3;

const int PLAYER_INITIAL_WIDTH = 100;
const int PLAYER_INITIAL_HEIGHT = 100;

const char PLAYER1_INITIAL_DIRECTION = DIRECTION_RIGHT;
const char PLAYER2_INITIAL_DIRECTION = DIRECTION_LEFT;

const int PLAYER1_INITIAL_X = WINDOW_INITIAL_WIDTH / 4;
const int PLAYER1_INITIAL_Y = WINDOW_INITIAL_HEIGHT / 2;
const int PLAYER2_INITIAL_X = WINDOW_INITIAL_WIDTH - PLAYER1_INITIAL_X;
const int PLAYER2_INITIAL_Y = PLAYER1_INITIAL_Y;

// Bomb
const int BOMB_INITIAL_TIME = 5000; // Milisecond
const int BOMB_INITIAL_RADIUS = PLAYER_INITIAL_WIDTH / 4;
const int BOMB_INITIAL_BLAST_FACTOR = 4;
const int BOMB_INITIAL_DAMAGE = 100;
const int BOMB_INITIAL_SPEED_X = WINDOW_INITIAL_WIDTH / 4;
const int BOMB_INITIAL_SPEED_Y = BOMB_INITIAL_SPEED_X;

// Explosion
const int EXPLOSION_INITIAL_DURATION = 200;

// Resources
const char RESOURCE_BACKGROUND_PATH[] = "res/image/background.jpg";
const char RESOURCE_PLAYER1_PATH[] = "res/image/player1.png";
const char RESOURCE_PLAYER2_PATH[] = "res/image/player2.png";
const char RESOURCE_BOMB_PATH[] = "res/image/bomb.png";
const char RESOURCE_EXPLOSION_PATH[] = "res/image/explosion.png";

#endif // CONSTANTS_H_INCLUDED
