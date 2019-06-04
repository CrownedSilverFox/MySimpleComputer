#include "myBigChars.h"

int bc_bigcharread(FILE* fd, int *big)
{
    fread(big, sizeof(int)*2, 1, fd);
    return 0;
}

int bc_bigcharwrite(FILE* fd, int *big, int count)
{
    fwrite(big, sizeof(int)*2, 1, fd);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    int tmp;
    int maxx, maxy;
    int i, j;

    if (x1 > x2) {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if (y1 > y2) {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    mt_getscreensize(&maxy, &maxx);
    if ((x1 < 0) || (y1 < 0) || (x2 > maxx) || (y2 > maxy) || (x2 - x1 < 2) ||
        (y2 - y1 < 2))
        return -1;
    mt_gotoXY(x1, y1);
    bc_printA(BOXCHAR_TL);
    for (i = x1 + 1; i < x2; i++)
        bc_printA(BOXCHAR_HOR);
    bc_printA(BOXCHAR_TR);
    for (i = y1 +1; i < y2; i++) {
        mt_gotoXY(x1, i);
        bc_printA(BOXCHAR_VERT);
        mt_gotoXY(x2, i);
        bc_printA(BOXCHAR_VERT);
    }
    mt_gotoXY(x1, y2);
    bc_printA(BOXCHAR_BL);
    for (i = x1 + 1; i < x2; i++)
        bc_printA(BOXCHAR_HOR);
    bc_printA(BOXCHAR_BR);
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return -1;
    if (y <= 3)
        pos = 0;
    else
        pos = 1;
    y = y % 4;
    *value = (big[pos] >> (y*8 + x)) & 1;

    return 0;
}

int bc_printA(char *str)
{
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_printbigchar(int *big, int x, int y, COLORS fg, COLORS bg)
{
    int maxx, maxy;
    int pos, bit;
    int i, j;
    char row[9];

    mt_getscreensize(&maxy, &maxx);
    if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
        return -1;
    row[8] = '\0';
    mt_setfgcolor(fg);
    mt_setbgcolor(bg);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pos = i >> 2;
            bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
            if (bit == 0)
                row[j] = ' ';
            else
                row[j] = BOXCHAR_REC;
        }
        mt_gotoXY(x, y + i);
        bc_printA(row);
    }
    mt_setfgcolor(BLACK);
    mt_setbgcolor(BLACK);
    return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
        return -1;
    if (y <= 3)
        pos = 0;
    else
        pos = 1;
    y = y % 4;
    if (value == 0)
        big[pos] &= ~(1 << (y*8 + x));
    else
        big[pos] |= 1 << (y*8 + x);

    return 0;
}