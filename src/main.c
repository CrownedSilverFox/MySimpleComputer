#include <mymemory.h>
#include <myTerm.h>
#include <myBigChars.h>
#include <myReadkey.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

int inst_counter;

void print_key(enum keys key)
{
    switch (key) {
        case KEY_l:
            printf("l\n");
            break;
        case KEY_s:
            printf("s\n");
            break;
        case KEY_r:
            printf("r\n");
            break;
        case KEY_t:
            printf("t\n");
            break;
        case KEY_i:
            printf("i\n");
            break;
        case KEY_q:
            printf("q\n");
            break;
        case KEY_up:
            printf("up\n");
            break;
        case KEY_down:
            printf("down\n");
            break;
        case KEY_left:
            printf("left\n");
            break;
        case KEY_right:
            printf("right\n");
            break;
        case KEY_f5:
            printf("F5\n");
            break;
        case KEY_f6:
            printf("F6\n");
            break;
        default:
            break;
    }
}

void show_m(void);

void show_r(int *p);

int redraw;
int main() {
    int a = 0, tmp = 0, l = 0, c = 0, d = 0;
    int *p = &c, *p2 = &d;


    // bigs
//    int bigs[17][2]; // In file: ABCDEF01234567890+
//    int rows, cols;
//    int x = 1, y = 1;
//    FILE *fd;
//    fd = fopen("../bigchars", "rb");
//    mt_clrscr();
//    for (int i = 0; i < 17; ++i) {
//        bc_bigcharread(fd, bigs[i]);
//    }
//    fclose(fd);

//  rk
//    struct termios options;
//    enum keys key;
//    char buf[100];
//
//    rk_mytermsave();
//    rk_mytermregime(0, 0, 1, 0, 1);
//    printf("ECHO disabled\n");
//    read(STDIN_FILENO, &buf, 10);
//    rk_mytermrestore();
//    printf("Terminal settings restored\n");
//    read(STDIN_FILENO, &buf, 10);
//    if (rk_mytermregime(0, 0, 0, 0, 2) == -1)
//        printf("rk_mytermregime returned -1\n");
//    else
//        printf("Wrong rk_mytermregime return value\n");
//    do {
//        rk_readkey(&key);
//        print_key(key);
//    } while (key != KEY_q);
////    rk_readkey(&key);
////    scanf("%d", &x);
////    mt_clrscr();
//    exit(0);
    sc_regInit();
    sc_regSet(i_BP, 1);
    inst_counter = 0;
    set_signals();
    struct itimerval tval;
    timerclear(&tval.it_interval);
    timerclear(&tval.it_value);
    tval.it_interval.tv_sec = 1;
    tval.it_value.tv_sec = 1;
    redraw = 1;
    setitimer(ITIMER_REAL, &tval, NULL);
    while (1) {
        if (inst_counter == 10) {
            raise(SIGUSR1);
        }
        if (redraw == 1) {
            mt_clrscr();
            printf("%d\n", inst_counter);
            show_r(p);
            redraw = 0;
        }
        if (inst_counter == 100) {
            break;
        }
    }
    exit(0);


    sc_regInit();
    pMemory = sc_memoryInit();
    show_r(p);
    show_m();
    mt_setfgcolor(CYAN);
    printf("Input: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n");
    mt_setfgcolor(WHITE);
    scanf("%d", &a);

    // Event-loop: цикл для ввода с клавиатуры

    while (a != 5) {

        switch (a) {
            case 1:
                // Установить регистр
                printf("SET register\n<number> <value>\n");
                scanf("%d %d", &l, &tmp);
                mt_setfgcolor(GREEN);
                if (sc_regSet(l, tmp)) mt_setfgcolor(RED);
                show_r(p);
                mt_setfgcolor(CYAN);
                printf("Input: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n");
                mt_setfgcolor(WHITE);
                scanf("%d", &a);
                break;
            case 2:
                // Установить значиние для ячейки памяти
                printf("SET memory\n<number> <value>\n");
                scanf("%d %d", &l, &tmp);
                mt_setfgcolor(GREEN);
                if (sc_memorySet(l, tmp)) mt_setfgcolor(RED);
                show_m();
                show_r(p);
                mt_setfgcolor(CYAN);
                printf("Input: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n");
                mt_setfgcolor(WHITE);
                scanf("%d", &a);
                break;
            case 3:
                // Кодирование комманды в представление для API CU
                printf("Encode\n<command> <operand>\n");
                scanf("%d %d", &l, &tmp);
                mt_setfgcolor(GREEN);
                if (sc_commandEncode(l, tmp, p)) mt_setfgcolor(RED);
                printf(" value=%d\n", *p);
                show_r(p);
                mt_setfgcolor(CYAN);
                printf("Input: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n");
                mt_setfgcolor(WHITE);
                scanf("%d", &a);
                break;
            case 4:
                // Декодирование команды из API CU
                printf("Decode\n<number>\n");
                scanf("%d", &tmp);
                mt_setfgcolor(GREEN);
                if (sc_commandDecode(tmp, p, p2)) mt_setfgcolor(RED);
                printf("Comm %d, Date %d \n", *p, *p2);
                mt_setfgcolor(WHITE);
                show_r(p);
                mt_setfgcolor(CYAN);
                printf("Input: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n");
                mt_setfgcolor(WHITE);
                scanf("%d", &a);
                break;
            default:
                exit(1);
                break;
        }
        mt_clrscr();
        mt_gotoXY(10, 5);

    }
    return 0;
}

void show_m(void) {
    // Вывод оперативной памяти
    printf("Mem");
    for (int i = 0; i < 10; ++i)
        // Индексы столбцов
        printf(" %2d", i);
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        // Индексы строк
        printf("\n%2d ", i);
        // Содержимое
        for (int j = 0; j < 10; ++j) {
            printf(" %2d", *(pMemory + (i * 10 + j)));
        }
    }
    printf("\n");
}

void show_r(int *p) {
    // Вывод регистра
    printf("\nRegister: ");
    for (int i = 1; i < i_Total; ++i) {
        sc_regGet(i, p);
        printf("[%d]%d ", i, *p);
    }
    printf("\n\n");
}

