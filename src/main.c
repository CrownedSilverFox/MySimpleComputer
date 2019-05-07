#include <mymemory.h>
#include <myTerm.h>


void show_m(void);

void show_r(int *p);

int main() {
    int a = 0, tmp = 0, l = 0, c = 0, d = 0;
    int *p = &c, *p2 = &d;
    printf(CLEAR);

    sc_regInit();
    pMemory = sc_memoryInit();
    show_r(p);
    show_m();
    printf("%sInput: [1]Test register [2]Test memory [3]Exit\n%s", CYAN, RESET);
    scanf("%d", &a);

    // Event-loop: цикл для ввода с клавиатуры

    while (a != 5) {

        switch (a) {
            case 1:
                // Установить регистр
                printf("SET register\n<number> <value>\n");
                scanf("%d %d", &l, &tmp);
                printf("%s", GREEN);
                if (sc_regSet(l, tmp)) printf("%s", RED);
                show_r(p);
                printf("%s", RESET);
                printf("%sInput: [1]Test register [2]Test memory [3]Exit\n%s", CYAN, RESET);
                scanf("%d", &a);
                break;
            case 2:
                // Установить значиние для ячейки памяти
                printf("SET memory\n<number> <value>\n");
                scanf("%d %d", &l, &tmp);
                printf("%s", GREEN);
                if (sc_memorySet(l, tmp)) printf("%s", RED);
                show_m();
                show_r(p);
                printf("%s", RESET);
                printf("%sInput: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n%s", CYAN, RESET);
                scanf("%d", &a);
                break;
            case 3:
                // Кодирование комманды в представление для API CU
                printf("Encode\n<command> <operand>\n");
                scanf("%d %d", &l, &tmp);
                printf("%s", GREEN);
                if (sc_commandEncode(l, tmp, p)) printf("%s", RED);
                show_r(p);
                printf(" value=%d\n%s", *p, RESET);
                printf("%sInput: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n%s", CYAN, RESET);
                scanf("%d", &a);
                break;
            case 4:
                // Декодирование команды из API CU
                printf("Decode\n<number>\n");
                scanf("%d", &tmp);
                printf("%s", GREEN);
                if (sc_commandDecode(tmp, p, p2)) printf("%s", RED);
                printf("Comm %d, Date %d %s\n", *p, *p2, RESET);
                show_r(p);
                printf("%sInput: [1]Test register [2]Test memory [3]CEncode [4]CDecode [5]Exit\n%s", CYAN, RESET);
                scanf("%d", &a);
                break;
            default:
                exit(1);
                break;
        }

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

