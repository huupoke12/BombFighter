#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>

class MainControl {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    std::string window_title;
    int window_width;
    int window_height;
    bool quit;


public:
    MainControl(const char* _title, int _width, int _height);
    ~MainControl();
    void logSDLError(const std::string& message, std::ostream& error_stream);
    int initSDL();
    int initPlayground();
    void runMainLoop();
    void handleInput();
    void renderBackground();
    void renderPlayer();
    void renderBomb();
};


#endif // MAINCONTROL_H_INCLUDED
