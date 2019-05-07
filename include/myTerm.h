#ifndef TERM_H
#define TERM_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define CLEAR "\E[H\E[2J"
#define SET_ADDR "\E[%d;%d"
#define WHITE_CUBE "\033[01;38;05;15;48;05;15m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define CYAN  "\033[1;36m"

//enum color {};

int mt_clrscr (void);

int mt_gotoXY(int x, int y);

int mt_getscreensize(int *rows, int *cols);

//int mt_setfgcolor(enum colors);


#endif
