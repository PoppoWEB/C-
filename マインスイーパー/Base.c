#include "Base.h"

int Clear(void)
{
    int cnt = 0, i, j;
    for ( i = 0; i < Y; i++) {
        for ( j = 0; j < X; j++) {
            if (MAP[i][j] == OPEN) cnt++;
        }
    }
    return X*Y-cnt == COUNT ? 1: 0;  
}

void Search(int i,int j)
{
    int cnt = 0;

    if (0<=i-1 && 0<=j-1) if (MAP[i-1][j-1] == BOMB) cnt++;
    if (0<=i-1)           if (MAP[i-1][j] == BOMB) cnt++;
    if (0<=i-1 && j+1<X)  if (MAP[i-1][j+1] == BOMB) cnt++;
    
    if (0<=j-1)           if (MAP[i][j-1] == BOMB) cnt++;
    if (j+1<X)            if (MAP[i][j+1] == BOMB) cnt++;

    if (i+1<Y && 0<=j-1) if (MAP[i+1][j-1] == BOMB) cnt++;
    if (i+1<Y)           if (MAP[i+1][j] == BOMB) cnt++;
    if (i+1<Y && j+1<X)  if (MAP[i+1][j+1] == BOMB) cnt++;

    MAP[i][j] = cnt;
}

void Initialize(int Hard)
{
    int R, i, j;
    int cnt = 40;
    COUNT = 0;

    srand(time(NULL));
    while (1)
    {
        for ( i = 0; i < Y; i++) {
            for ( j = 0; j < X; j++) {
                R = rand()%30;
                if (R > 27-Hard) {
                    MAP[i][j] = BOMB;
                    cnt--;
                }
                else MAP[i][j] = CLOSE;
            }
        }
        if (cnt <= 0) break;
    }

    for ( i = 0; i < Y; i++) {
        for ( j = 0; j < X; j++) {
            if (MAP[i][j] != BOMB) Search(i,j);
            if (MAP[i][j] == BOMB) COUNT++;
        }
    }
    
    for ( i = 0; i < Y; i++) {
        printf("\t");
        for ( j = 0; j < X; j++) {
            KEY[i][j] = MAP[i][j];
            printf("¡");
        }
        printf("\n");
    }
}