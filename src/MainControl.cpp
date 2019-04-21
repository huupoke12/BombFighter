#include <SDL_image.h>
#include "MainControl.h"
#include "Player.h"
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

    player1.init(PLAYER1_INITIAL_X, PLAYER1_INITIAL_Y, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_SPEED, PLAYER_INITIAL_HEALTH, PLAYER_INITIAL_MAX_BOMB, PLAYER1_INITIAL_DIRECTION);
    player2.init(PLAYER2_INITIAL_X, PLAYER2_INITIAL_Y, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_SPEED, PLAYER_INITIAL_HEALTH, PLAYER_INITIAL_MAX_BOMB, PLAYER2_INITIAL_DIRECTION);

    runMainLoop();
    return 0;

}


void MainControl::runMainLoop() {
    unsigned int delay = 1000/window_fps;
    lastTime = SDL_GetTicks();
    while (!quit) {
        handleInput();
        updatePlayer();
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
                    player1.moveUp();
                    break;
                case SDL_SCANCODE_S:
                    player1.moveDown();
                    break;
                case SDL_SCANCODE_A:
                    player1.moveLeft();
                    break;
                case SDL_SCANCODE_D:
                    player1.moveRight();
                    break;
                case SDL_SCANCODE_UP:
                    player2.moveUp();
                    break;
                case SDL_SCANCODE_DOWN:
                    player2.moveDown();
                    break;
                case SDL_SCANCODE_LEFT:
                    player2.moveLeft();
                    break;
                case SDL_SCANCODE_RIGHT:
                    player2.moveRight();
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
}

void MainControl::renderBackground() {
    SDL_RenderCopy(renderer, background_image_texture, NULL, NULL);
}

void MainControl::renderPlayer() {
    player1_rect.x = player1.getX() - player1.getWidth() / 2;
    player1_rect.y = player1.getY() - player1.getHeight() / 2;
    player1_rect.w = player1.getWidth();
    player1_rect.h = player1.getHeight();

    player2_rect.x = player2.getX() - player2.getWidth() / 2;
    player2_rect.y = player2.getY() - player2.getHeight() / 2;
    player2_rect.w = player2.getWidth();
    player2_rect.h = player2.getHeight();

    SDL_RenderCopy(renderer, player1_image_texture, NULL, &player1_rect);
    SDL_RenderCopy(renderer, player2_image_texture, NULL, &player2_rect);
}

void MainControl::renderBomb() {
}

