#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int main() {
    static int ch = 0;
    screenInit(1);
    keyboardInit();
    timerInit(50);
    screenUpdate();

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            screenUpdate();
        }
    if (timerTimeOver() == 1) {
        screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
return 0;
}
