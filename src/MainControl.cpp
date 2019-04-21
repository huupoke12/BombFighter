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

    // Playground
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

    player1.init(PLAYER1_INITIAL_X, PLAYER1_INITIAL_Y, PLAYER_DIRECTION_RIGHT);
    player2.init(PLAYER2_INITIAL_X, PLAYER2_INITIAL_Y, PLAYER_DIRECTION_LEFT);

    runMainLoop();

    return 0;

}


void MainControl::runMainLoop() {
    unsigned int delay = 1000/window_fps;
    unsigned int lastTime, currentTime;
    while (!quit) {
        lastTime = SDL_GetTicks();
        handleInput();
        SDL_RenderClear(renderer);
        renderBackground();
        renderPlayer();
        renderBomb();
        SDL_RenderPresent(renderer);

        // Delay
        currentTime = SDL_GetTicks();
        if (currentTime < lastTime + delay) {
            SDL_Delay(lastTime + delay - currentTime);
        }
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
                default:
                    break;
            }
        }
    }
}

void MainControl::renderBackground() {
    SDL_RenderCopy(renderer, background_image_texture, NULL, NULL);
}

void MainControl::renderPlayer() {
}

void MainControl::renderBomb() {
}

