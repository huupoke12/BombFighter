#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>

class MainControl {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    const char* window_title;
    int window_width;
    int window_height;

public:
    MainControl(const char* _title, int _width, int _height);
    ~MainControl();
    void logSDLError(const std::string& message, std::ostream& error_stream);
    int init();
    void runMainLoop();
};


#endif // MAINCONTROL_H_INCLUDED
