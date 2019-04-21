#include "MainControl.h"
#include "constants.h"

int main(int argc, char *argv[]) {

    MainControl control(GAME_TITLE, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT, WINDOW_INITIAL_FPS);
    int return_code = control.init();
    if (return_code != 0) {
        return return_code;
    }
    return 0;
}

