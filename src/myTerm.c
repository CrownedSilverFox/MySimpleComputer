#include "myTerm.h"

int mt_clrscr (void) {
    printf(CLEAR);
    return 1;
}

int mt_gotoXY(int x, int y) {
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    if ((x < 0 || x > rows) || (y < 0 || y > cols))
        return -1;
    else
        printf(SET_ADDR, y, x);
    return 0;

}

int mt_setfgcolor(COLORS color) {
    if (color < BLACK || color > WHITE)
        return -1;
    printf("\E[%dm", color);
    return 0;
}

int mt_setbgcolor(COLORS color) {
    if (color < BLACK || color > WHITE)
        return -1;
    printf("\E[%dm", color + 10);
    return 0;
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
    *cols = ts.ws_col;
    *rows = ts.ws_row;
#endif /* TIOCGSIZE */
    return 1;
}