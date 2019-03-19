#ifndef MEMORY_H
#define MEMORY_H
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define MemSIZE 100

extern uint16_t AC; //Accumulator
extern uint8_t  PC; //Program_Counter

typedef enum {
    i_POO = 1, //Performing the_Operation Overflow
    i_EDZ,     //Error Division by_Zero
    i_OME,     //Out of_Memory Error
    i_ICP,     //Ignoring Clock Pulses
    i_ICS,     //Invalid Command Specifed
    i_BP,      //Break Point
    i_Total    //Total flags count
} Reg;

extern Reg Index_Flags;
extern uint32_t Register;

short int* pMemory; //global pointer

short int* sc_memoryInit(void);             // Инициализирует Оперативную Память, все ячейки == NULL
int sc_memorySet(int address, int  value);  // Задает значение ячейки памяти !Er Flag(address_memory limit)
int sc_memoryGet(int address, int* value);  // Возвращает значение ячейки в value !Er Flag(address_memory limit)
int sc_memorySave(char* filename);          // Сохраняет содержимое памяти в бинарный файл
int sc_memoryLoad(char* filename);          // Загружает из файла содержимое памяти
int sc_commandEncode(int command, int operand, int* value); // Кодирует команду с номером и операндом, результат в value
int sc_commandDecode(int value, int* command, int* operand);// Декодирует значение как команду S_C !Er Flag(invalid command)

int sc_regInit(void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int* value);
#endif
