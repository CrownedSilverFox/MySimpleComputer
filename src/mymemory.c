#include "mymemory.h"

Reg Index_Flags = i_Total;
uint32_t Register = 0;

short int* sc_memoryInit(void) {
    short int* pMemory = malloc(MemSIZE * sizeof(short int));
    if (pMemory)
        for(int i = 0; i < MemSIZE; ++i)
            *(pMemory + i) = 0;
    return pMemory;
}

int sc_memorySet(int address, int  value) {
    if ((address < 0) || (address > MemSIZE)) {
        sc_regSet(i_OME, 1);
        return -1;
    }
    *(pMemory + address) = value;
    return 0;
}

int sc_memoryGet(int address, int* value) {
    if ((address < 0) || (address > MemSIZE)) {
        sc_regSet (i_OME, 1);
        return -1;
    }
    *value = *(pMemory + address);
    return 0;
}

int sc_memorySave(char* filename) {
    FILE *fs = fopen(filename, "wb");
	if (!fs) return -1;
	
	int flag = fwrite(pMemory, sizeof(int), MemSIZE, fs);
	fclose(fs);
	if (flag != MemSIZE) return -2;
    
    return 0;
}

int sc_memoryLoad(char* filename) {
    FILE *fl = fopen(filename, "rb");
    if (!fl) return -1;
    
    int flag = fread(pMemory, sizeof(int), MemSIZE, fl);
    if (flag != MemSIZE) return -2;
    fclose(fl);
    
    for (int i = 0; i < MemSIZE; ++i) pMemory[i] &= 0x7FFF;

    return 0;
}

int sc_regInit(void) {
    Register &= 0;
    return 0;
}

int sc_regSet (int reg, int value) {
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

int sc_regGet (int reg, int* value) {
    if (reg >= 0 && reg < i_Total) {
        *value = 0x1 & (Register >> (reg -1));
        return 0;
    } else 
        sc_regSet(i_OME, 1);
        
    return -1;
}

const int Operation[] = {
    10, 11,
    20,21,
    30,31,32,33,
    40,41,42,43,
    51,52,53,54,55,
    56,57,58,59,60,
    61,62,63,64,65,
    67,68,69,70,71,
    72,73,74,75,76
    };
const int ops_num = sizeof(Operation)/sizeof(int);

int funccmp(const void * x1, const void * x2)
{
  return ( *(int*)x1 - *(int*)x2 );
}

int sc_commandEncode(int command, int operand, int *value) {
	
	void *ops_ptr = bsearch(&command, Operation, ops_num, sizeof(int), funccmp);
	if (ops_ptr) {
		*value = (command << 7) | operand;
		return 0;
	} else { 
        sc_regSet(i_ICS, 1);
    }
	return -1;
}


int sc_commandDecode(int value, int *command, int *operand) {
	void *correct_command;
	int attribute;
	int tmp_command, tmp_operand;
	
	attribute = (value >> 14) & 1;
	if (attribute == 0)	{
		tmp_command = (value >> 7) & 0x7F;
		tmp_operand = value & 0x7F;
		
		correct_command = bsearch(&tmp_command, Operation, ops_num, sizeof(int), funccmp);
		if (correct_command) {
			*command = tmp_command;
			*operand = tmp_operand;
		} else {
             sc_regSet(i_ICS, 1);
			return -1;
	    }
	} else return 1;
	return 0;
}
