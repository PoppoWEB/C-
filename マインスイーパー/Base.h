#ifndef BASE
#define BASE

#include <stdio.h>

#define OPEN  -1
#define CLOSE  0
#define NUMBER 1
#define BOMB   8
#define FLAG   9
#define X      24
#define Y      20
#define sleep(t) Sleep(t*1000)

int MAP[Y][X];
int KEY[Y][X];

int cpx,cpy, COUNT, GAME;

int Clear(void);
void Search(int i,int j);
void Initialize(int Hard);

#endif