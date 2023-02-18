#ifndef SYSTEM
#define SYSTEM

#include <Windows.h>
#define sleep(t) Sleep(t*1000)

void Reset(int set);
int Print_table(char *table[],int T);

#endif