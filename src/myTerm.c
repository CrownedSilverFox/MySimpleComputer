#include "myTerm.h"

int mt_clrscr (void) {
    printf(CLEAR);
    return 1;
}

int mt_gotoXY(int x, int y) {
    printf(SET_ADDR, x, y);
}

int mt_getscreensize(int *rows, int *cols) {

#ifdef TIOCGSIZE
    struct ttysize ts;
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
        cols = ts.ts_cols;
        lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    cols = ts.ws_col;
    rows = ts.ws_row;
#endif /* TIOCGSIZE */
    return 1;
}