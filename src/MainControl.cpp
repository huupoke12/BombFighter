#include <SDL_image.h>
#include "MainControl.h"
#include "Player.h"
#include "Bomb.h"
#include "constants.h"

// Constructor
MainControl::MainControl(const char* _title, int _width, int _height, int _fps) {
    window = nullptr;
    renderer = nullptr;
    window_title = _title;
    window_width = _width;
    window_height = _height;
    window_fps = _fps;
    quit = false;
    lastTime = 0;
    currentTime = 0;
    dt = 0;
}

// Destructor
MainControl::~MainControl() {
    SDL_DestroyTexture(background_image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void MainControl::logSDLError(const std::string& message, std::ostream& error_stream = std::cerr) {
    error_stream << message << " error: " << SDL_GetError() << std::endl;
}

int MainControl::init() {
    // SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError("SDL_Init");
        return 1;
    }

    int IMG_flags = IMG_INIT_JPG|IMG_INIT_PNG;
    int IMG_initted = IMG_Init(IMG_flags);
    if ((IMG_initted & IMG_flags) != IMG_flags) {
        logSDLError("IMG_Init");
        SDL_Quit();
        return 10;
    }

    window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
    if (window == nullptr) {
        logSDLError("SDL_CreateWindow");
        SDL_Quit();
        return 2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError("SDL_CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    // Background Init
    background_image_path = RESOURCE_BACKGROUND_PATH;
    background_image_texture = nullptr;
    SDL_Surface *background_image_surface = nullptr;
    background_image_surface = IMG_Load(background_image_path.c_str());
    if (background_image_surface == nullptr) {
        logSDLError("IMG_Load Background");
        return 11;
    } else {
        background_image_texture = SDL_CreateTextureFromSurface(renderer, background_image_surface);
        SDL_FreeSurface(background_image_surface);
        if (background_image_texture == nullptr) {
            logSDLError("SDL_CreateTextureFromSurface Background");
            return 4;
        }
    }

    // Player Init
    player1_image_path = RESOURCE_PLAYER1_PATH;
    player2_image_path = RESOURCE_PLAYER2_PATH;
    player1_image_texture = nullptr;
    player2_image_texture = nullptr;
    SDL_Surface *player1_image_surface = nullptr;
    SDL_Surface *player2_image_surface = nullptr;
    player1_image_surface = IMG_Load(player1_image_path.c_str());
    player2_image_surface = IMG_Load(player2_image_path.c_str());
    if (player1_image_surface == nullptr || player2_image_surface == nullptr) {
        logSDLError("IMG_Load Player");
        return 11;
    } else {
        player1_image_texture = SDL_CreateTextureFromSurface(renderer, player1_image_surface);
        SDL_FreeSurface(player1_image_surface);
        player2_image_texture = SDL_CreateTextureFromSurface(renderer, player2_image_surface);
        SDL_FreeSurface(player2_image_surface);
        if (player1_image_texture == nullptr || player2_image_texture == nullptr) {
            logSDLError("SDL_CreateTextureFromSurface Player");
            return 4;
        }
    }

    player1.init(PLAYER1_INITIAL_X, PLAYER1_INITIAL_Y, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_SPEED_X, PLAYER_INITIAL_SPEED_Y, PLAYER_INITIAL_HEALTH, PLAYER_INITIAL_MAX_BOMB, PLAYER1_INITIAL_DIRECTION);
    player2.init(PLAYER2_INITIAL_X, PLAYER2_INITIAL_Y, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_SPEED_X, PLAYER_INITIAL_SPEED_Y, PLAYER_INITIAL_HEALTH, PLAYER_INITIAL_MAX_BOMB, PLAYER2_INITIAL_DIRECTION);

    // Bomb Init
    bomb_image_path = RESOURCE_BOMB_PATH;
    bomb_image_texture = nullptr;
    SDL_Surface *bomb_image_surface = nullptr;
    bomb_image_surface = IMG_Load(bomb_image_path.c_str());
    if (bomb_image_surface == nullptr) {
        logSDLError("IMG_Load Bomb");
        return 11;
    } else {
        bomb_image_texture = SDL_CreateTextureFromSurface(renderer, bomb_image_surface);
        SDL_FreeSurface(bomb_image_surface);
        if (bomb_image_texture == nullptr) {
            logSDLError("SDL_CreateTextureFromSurface Bomb");
            return 4;
        }
    }

    runMainLoop();
    return 0;

}


void MainControl::runMainLoop() {
    unsigned int delay = 1000/window_fps;
    lastTime = SDL_GetTicks();
    while (!quit) {
        handleInput();
        updatePlayer();
        updateBomb();
        SDL_RenderClear(renderer);
        renderBackground();
        renderPlayer();
        renderBomb();
        SDL_RenderPresent(renderer);

        // Delay
        currentTime = SDL_GetTicks();
        dt = currentTime - lastTime;
        if (currentTime < lastTime + delay) {
            SDL_Delay(lastTime + delay - currentTime);
            dt = delay;
        }
        lastTime = SDL_GetTicks();
    }
}

void MainControl::handleInput() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    player1.moveUp(player2);
                    break;
                case SDL_SCANCODE_S:
                    player1.moveDown(player2);
                    break;
                case SDL_SCANCODE_A:
                    player1.moveLeft(player2);
                    break;
                case SDL_SCANCODE_D:
                    player1.moveRight(player2);
                    break;
                case SDL_SCANCODE_G:
                    player1.useBomb();
                    break;
                case SDL_SCANCODE_H:
                    player1.useShield();
                    break;
                case SDL_SCANCODE_UP:
                    player2.moveUp(player1);
                    break;
                case SDL_SCANCODE_DOWN:
                    player2.moveDown(player1);
                    break;
                case SDL_SCANCODE_LEFT:
                    player2.moveLeft(player1);
                    break;
                case SDL_SCANCODE_RIGHT:
                    player2.moveRight(player1);
                    break;
                case SDL_SCANCODE_APOSTROPHE:
                    player2.useBomb();
                    break;
                case SDL_SCANCODE_SEPARATOR:
                    player2.useShield();
                    break;
                default:
                    break;
            }
        }
    }
}

void MainControl::updatePlayer() {
    player1.setTime(dt);
    player2.setTime(dt);

    if (player1.isDead()) {
        //Gameover
    }
    if (player2.isDead()) {
        //Gameover
    }
}

void MainControl::updateBomb() {
    int bomb_x, bomb_y;
    for (std::vector<Bomb>::iterator bomb1 = player1.getBombs().begin() ; bomb1 != player1.getBombs().end(); ++bomb1) {
        (*bomb1).setTime(dt);
        if (!(*bomb1).isThrown()) {
            switch (player1.getDirection()) {
            case DIRECTION_UP:
                bomb_x = player1.getX();
                bomb_y = player1.getY() - player1.getHeight() / 2 - (*bomb1).getRadius();
                break;
            case DIRECTION_RIGHT:
                bomb_x = player1.getX() + player1.getWidth() / 2 + (*bomb1).getRadius();
                bomb_y = player1.getY();
                break;
            case DIRECTION_DOWN:
                bomb_x = player1.getX();
                bomb_y = player1.getY() + player1.getHeight() / 2 + (*bomb1).getRadius();
                break;
            case DIRECTION_LEFT:
                bomb_x = player1.getX() - player1.getWidth() / 2 - (*bomb1).getRadius();
                bomb_y = player1.getY();
                break;
            default:
                bomb_x = 0;
                bomb_y = 0;
            }
            (*bomb1).setPosition(bomb_x, bomb_y, player1.getDirection());

        }

        (*bomb1).updatePosition();
        (*bomb1).updateTimer();
        (*bomb1).checkExplode(player1, player2);
        if ((*bomb1).isExploded()) {
            if (bomb1 == player1.getBombs().end() - 1) {
                player1.setHoldingBomb(false);
            }
            player1.getBombs().erase(bomb1);
            --bomb1;
        }
    }
    for (std::vector<Bomb>::iterator bomb2 = player2.getBombs().begin() ; bomb2 != player2.getBombs().end(); ++bomb2) {
        (*bomb2).setTime(dt);
        if (!(*bomb2).isThrown()) {
            switch (player2.getDirection()) {
            case DIRECTION_UP:
                bomb_x = player2.getX();
                bomb_y = player2.getY() - player2.getHeight() / 2 - (*bomb2).getRadius();
                break;
            case DIRECTION_RIGHT:
                bomb_x = player2.getX() + player2.getWidth() / 2 + (*bomb2).getRadius();
                bomb_y = player2.getY();
                break;
            case DIRECTION_DOWN:
                bomb_x = player2.getX();
                bomb_y = player2.getY() + player2.getHeight() / 2 + (*bomb2).getRadius();
                break;
            case DIRECTION_LEFT:
                bomb_x = player2.getX() - player2.getWidth() / 2 - (*bomb2).getRadius();
                bomb_y = player2.getY();
                break;
            default:
                bomb_x = 0;
                bomb_y = 0;
            }
            (*bomb2).setPosition(bomb_x, bomb_y, player2.getDirection());
        }
        (*bomb2).updatePosition();
        (*bomb2).updateTimer();
        (*bomb2).checkExplode(player1, player2);
        if ((*bomb2).isExploded()) {
            if (bomb2 == player2.getBombs().end() - 1) {
                player2.setHoldingBomb(false);
            }
            player2.getBombs().erase(bomb2);
            --bomb2;
        }
    }
}

void MainControl::renderBackground() {
    SDL_RenderCopy(renderer, background_image_texture, NULL, NULL);
}

void MainControl::renderPlayer() {
    double player1_angle = 0;
    player1_rect.x = player1.getX() - player1.getWidth() / 2;
    player1_rect.y = player1.getY() - player1.getHeight() / 2;
    player1_rect.w = player1.getWidth();
    player1_rect.h = player1.getHeight();

    double player2_angle = 0;
    player2_rect.x = player2.getX() - player2.getWidth() / 2;
    player2_rect.y = player2.getY() - player2.getHeight() / 2;
    player2_rect.w = player2.getWidth();
    player2_rect.h = player2.getHeight();

    switch (player1.getDirection()) {
    case DIRECTION_UP:
        player1_angle = ROTATE_UP_ANGLE;
        break;
    case DIRECTION_DOWN:
        player1_angle = ROTATE_DOWN_ANGLE;
        break;
    case DIRECTION_LEFT:
        player1_angle = ROTATE_LEFT_ANGLE;
        break;
    case DIRECTION_RIGHT:
        player1_angle = ROTATE_RIGHT_ANGLE;
        break;
    }

    switch (player2.getDirection()) {
    case DIRECTION_UP:
        player2_angle = ROTATE_UP_ANGLE;
        break;
    case DIRECTION_DOWN:
        player2_angle = ROTATE_DOWN_ANGLE;
        break;
    case DIRECTION_LEFT:
        player2_angle = ROTATE_LEFT_ANGLE;
        break;
    case DIRECTION_RIGHT:
        player2_angle = ROTATE_RIGHT_ANGLE;
        break;
    }
    SDL_RenderCopyEx(renderer, player1_image_texture, NULL, &player1_rect, player1_angle, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, player2_image_texture, NULL, &player2_rect, player2_angle, NULL, SDL_FLIP_NONE);
}

void MainControl::renderBomb() {
    int bomb_x, bomb_y, bomb_radius;
    for (std::vector<Bomb>::iterator it = player1.getBombs().begin() ; it != player1.getBombs().end(); ++it) {
        bomb_x = (*it).getX();
        bomb_y = (*it).getY();
        bomb_radius = (*it).getRadius();
        bomb_rect.x = bomb_x - bomb_radius;
        bomb_rect.y = bomb_y - bomb_radius;
        bomb_rect.w = bomb_radius * 2;
        bomb_rect.h = bomb_radius * 2;
        SDL_RenderCopy(renderer, bomb_image_texture, NULL, &bomb_rect);
    }
    for (std::vector<Bomb>::iterator it = player2.getBombs().begin() ; it != player2.getBombs().end(); ++it) {
        bomb_x = (*it).getX();
        bomb_y = (*it).getY();
        bomb_radius = (*it).getRadius();
        bomb_rect.x = bomb_x - bomb_radius;
        bomb_rect.y = bomb_y - bomb_radius;
        bomb_rect.w = bomb_radius * 2;
        bomb_rect.h = bomb_radius * 2;
        SDL_RenderCopy(renderer, bomb_image_texture, NULL, &bomb_rect);
    }
}

