#ifndef BIG_H
#define BIG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "myTerm.h"

#define BOXCHAR_REC 'a'
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_TR "k"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_HOR "q"

int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x, int y, COLORS fg, COLORS bg);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(FILE* fd, int *big, int count);
int bc_bigcharread(FILE* fd, int *big);
int arr_to_big(int *big, char *arr);


#endif /* BIG_H */
