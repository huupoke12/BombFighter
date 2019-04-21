#include "MainControl.h"
#include "constants.h"

int main(int argc, char *argv[]) {

    MainControl control(GAME_TITLE, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
    if (control.initSDL() != 0 && control.initPlayground() != 0) {
        return 1;
    }

    control.runMainLoop();
    return 0;
}

