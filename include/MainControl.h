#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>
#include "Player.h"

class MainControl {
private:
    // SDL
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    std::string window_title;
    int window_width;
    int window_height;
    int window_fps;
    bool quit;

    // Resources
    std::string background_image_path;
    SDL_Texture *background_image_texture;

    // Player
    Player player1;
    Player player2;


public:
    MainControl(const char* _title, int _width, int _height, int _fps);
    ~MainControl();
    void logSDLError(const std::string& message, std::ostream& error_stream);
    int init();
    void runMainLoop();
    void handleInput();
    void renderBackground();
    void renderPlayer();
    void renderBomb();
};


#endif // MAINCONTROL_H_INCLUDED
