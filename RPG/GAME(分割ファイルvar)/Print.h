#ifndef PRINT
#define PRINT

#include "BASE.h"

int cpy,cpx;
int tmp;
int Maze[X][Y];

void For_15(void);
void Print_Maze(int px,int py);
void Print_Ply_Reset(int px,int py);
void Map_Reset(void);
void Print_Point_Maze(int px,int py,int mn);
int Goal(int px,int py);
void Item(ply *p,int px,int py);

#endif