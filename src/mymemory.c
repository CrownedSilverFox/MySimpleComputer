#include <signal.h>
#include <unistd.h>
#include "mymemory.h"

Reg Index_Flags = i_Total;
uint32_t Register = 0;
int inst_counter;

short int *sc_memoryInit(void) {
    // Выделяем память под массив с оперативной памятью
    short int *pMemory = malloc(MemSIZE * sizeof(short int));
    if (pMemory)
        // Зануляем ячейки
        for (int i = 0; i < MemSIZE; ++i)
            *(pMemory + i) = 0;
    return pMemory;
}

int sc_memorySet(int address, int value) {
    // Установка значения в ячейку по адресу
    if ((address < 0) || (address > MemSIZE)) {
        sc_regSet(i_OME, 1);
        return -1;
    }
    *(pMemory + address) = value;
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if ((address < 0) || (address > MemSIZE)) {
        // Если адрес вне пределов массива, вызываем сообщение об ошибке.
        sc_regSet(i_OME, 1);
        return -1;
    }
    // Выставляем указатель на нужную ячейку памяти
    *value = *(pMemory + address);
    return 0;
}

int sc_memorySave(char *filename) {
    // Запись памяти в файл
    FILE *fs = fopen(filename, "wb");
    if (!fs) return -1;

    int flag = fwrite(pMemory, sizeof(int), MemSIZE, fs);
    fclose(fs);
    if (flag != MemSIZE) return -2;

    return 0;
}

int sc_memoryLoad(char *filename) {
    // Загружаем память из файла
    FILE *fl = fopen(filename, "rb");
    if (!fl) return -1;

    int flag = fread(pMemory, sizeof(int), MemSIZE, fl);
    if (flag != MemSIZE) return -2;
    fclose(fl);

    for (int i = 0; i < MemSIZE; ++i) pMemory[i] &= 0x7FFF;

    return 0;
}

int sc_regInit(void) {
    // Инициализация регистра побитовым и.
    Register &= 0;
    return 0;
}

int sc_regSet(int reg, int value) {
    // Установить регистр
    if (reg > 0 && reg < i_Total) {
        if (value == 0) {
            Register &= ~(1 << (reg - 1));
            return 0;
        }
        if (value == 1) {
            Register |= (1 << (reg - 1));
            return 0;
        }
    }
    return -1;
}

int sc_regGet(int reg, int *value) {
    // Получение регистра
    if (reg >= 0 && reg < i_Total) {
        *value = 0x1 & (Register >> (reg - 1));
        return 0;
    } else
        sc_regSet(i_OME, 1);

    return -1;
}

const int Operation[] = {
        10, 11,
        20, 21,
        30, 31, 32, 33,
        40, 41, 42, 43,
        51, 52, 53, 54, 55,
        56, 57, 58, 59, 60,
        61, 62, 63, 64, 65,
        67, 68, 69, 70, 71,
        72, 73, 74, 75, 76
};
const int ops_num = sizeof(Operation) / sizeof(int);

int funccmp(const void *x1, const void *x2) {
    // функция сравнения для поиска по массиву команд
    return (*(int *) x1 - *(int *) x2);
}

int sc_commandEncode(int command, int operand, int *value) {

    // Двоичный поиск по массиву с командами.
    void *ops_ptr = bsearch(&command, Operation, ops_num, sizeof(int), funccmp);
    if (ops_ptr) {
        // Если найдено, выполняем побитовый сдвиг команды на 7 позиций влево
        // Затем при помощи побитового "Или" добавляем туда операнд, получая требуемое значение для команды
        *value = (command << 7) | operand;
        return 0;
    } else {
        // Записывает сообщение о неправильной команде
        sc_regSet(i_ICS, 1);
    }
    return -1;
}


int sc_commandDecode(int value, int *command, int *operand) {
    void *correct_command;
    int attribute;
    int tmp_command, tmp_operand;

    // Сдвиг на 14 позиций вправо для определения признака команды
    attribute = (value >> 14) & 1;
    if (attribute == 0) {
        // Если атрибут положительный, вычленяем команду и операнд
        // 0x7F == 127 == 1111111
        tmp_command = (value >> 7) & 0x7F;
        tmp_operand = value & 0x7F;

        // Ищем команду в массиве
        correct_command = bsearch(&tmp_command, Operation, ops_num, sizeof(int), funccmp);
        if (correct_command) {
            // Если найдена, записываем в указатели
            *command = tmp_command;
            *operand = tmp_operand;
        } else {
            // Запись ошибки
            sc_regSet(i_ICS, 1);
            return -1;
        }
    } else return 1;
    return 0;
}

void set_signals() {
    signal(SIGALRM, timer_handler);
    signal(SIGUSR1, usrsig_handler);
}

void usrsig_handler(int sig)
{
    sc_regInit();
    sc_memoryInit();
}

int redraw;
void timer_handler(int sig)
{
    int ignore;
    sc_regGet(i_ICP, &ignore);
    if (ignore == 1) {
        return;
    }
    redraw = 1;
    inst_counter++;
}
