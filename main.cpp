#include "MainControl.h"
#include "constants.h"

int main(int argc, char *argv[]) {

    MainControl control(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (control.init() != 0) {
        return 1;
    }

    control.runMainLoop();
    return 0;
}

