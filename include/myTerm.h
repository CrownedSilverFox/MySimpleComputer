#ifndef TERM_H
#define TERM_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define CLEAR "\E[H\E[2J"
#define SET_ADDR "\E[%d;%dH"
#define RESET "\033[0m"

typedef enum {
    BLACK   = 30,
    RED     = 31,
    GREEN   = 32,
    YELLOW  = 33,
    BLUE    = 34,
    MAGENTA = 35,
    CYAN    = 36,
    WHITE   = 37,
} COLORS; //background = color + 10

int mt_clrscr (void);

int mt_gotoXY(int x, int y);

int mt_getscreensize(int *rows, int *cols);

int mt_setfgcolor(COLORS color);

int mt_setbgcolor(COLORS color);



#endif
