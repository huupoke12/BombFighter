#include <iostream>
#include <SDL.h>

#include "Player.cpp"

class MainControl {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    const char* window_title;
    int window_width;
    int window_height;

public:
    // Constructor
    MainControl(const char* _title, int _width, int _height) {
        window = nullptr;
        renderer = nullptr;
        window_title = _title;
        window_width = _width;
        window_height = _height;
    }

    // Destructor
    ~MainControl() {
    }

    // Fuctions
    void logSDLError(const std::string& message, std::ostream& error_stream = std::cerr) {
        error_stream << message << " error: " << SDL_GetError() << std::endl;
    }

    int init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            logSDLError("SDL_Init");
            return 1;
        }

        SDL_Window *window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
        if (window == nullptr) {
            logSDLError("SDL_CreateWindow");
            SDL_Quit();
            return 2;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            logSDLError("SDL_CreateRenderer");
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 3;
        }

        return 0;
    }

    void destroy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void runMainLoop() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
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

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

};
