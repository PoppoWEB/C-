#include <stdio.h>
#include "Print.h"

void Open_Oll(void)
{
    int i,j;

    for ( i = 0; i < Y; i++) {
        printf("\t");
        for ( j = 0; j < X; j++) {
            if (KEY[i][j] != FLAG) Combination(i,j);

            if (KEY[i][j] == BOMB || MAP[i][j] == BOMB) {
                printf("\033[41m");
                printf("??");
                printf("\033[49m");
            }
            else if (1<=KEY[i][j] && KEY[i][j] <= 8) Point(i,j);
            else printf("?@");
        }
        printf("\n");
    }
}

void Point(int i,int j)
{
    switch (KEY[i][j])
    {
    case 1:
        printf("?P");
        break;
    case 2:
        printf("?Q");
        break;
    case 3: 
        printf("?R");
        break;
    case 4:
        printf("?S");
        break;
    case 5:
        printf("?T");
        break;
    case 6:
        printf("?U");
        break;
    case 7:
        printf("?V");
        break;
    case 8:
        printf("?W");
        break;
    }
}

void Reprint(int y,int x)
{
    int i,j;

    for ( i = 0; i < Y; i++) {
        printf("\t");
        for ( j = 0; j < X; j++) {
            if (KEY[i][j] == FLAG) {
                printf("\033[41m");
                printf("?˜");
                printf("\033[49m");
            }
            else if (MAP[i][j] == OPEN) {
                if (1<=KEY[i][j] && KEY[i][j] <= 8) Point(i,j);
                else printf("?@");
            }
            else printf("??");
        }
        printf("\n");
    }
}

void Flag_Point(int y,int x)
{
    if (MAP[y][x] == OPEN) return;
    else if (KEY[y][x] == FLAG)
        KEY[y][x] = MAP[y][x];

    else KEY[y][x] = FLAG;
}

void RePoint(int x,int y)
{
    int j;
    printf("\033[%d;%dH" ,cpy+1,0);
    printf("\033[2K");
    printf("\t");
    for (j = 0; j < X ; j++) {
        if (KEY[cpy][j] == FLAG) { 
            printf("\033[41m");
            printf("?˜");
            printf("\033[49m");
        }
        else if (MAP[cpy][j] == OPEN) {
            if (1<=KEY[cpy][j] && KEY[cpy][j] <= 8) Point(cpy,j);
            else printf("?@");
        }
        else printf("??");
    }

    printf("\033[%d;%dH" ,y+1,0);
    printf("\033[2K");
    printf("\t");
    for (j = 0; j < X ; j++) {
        if (KEY[y][j] == FLAG) { 
            printf("\033[41m");
            printf("?˜");
            printf("\033[49m");
        }
        else if (x == j) {
            printf("\033[44m");
            printf("??");
            printf("\033[49m");
        }
        else if (MAP[y][j] == OPEN) {
            if (1<=KEY[y][j] && KEY[y][j] <= 8) Point(y,j);
            else printf("?@");
        }
        else printf("??");
    }   
    printf("\033[%d;%dH" ,Y,0);
}

void Combination(int i,int j)
{
    if (1<=MAP[i][j] && MAP[i][j] <= 8) MAP[i][j] = OPEN;
    else if (MAP[i][j] == CLOSE) {
        MAP[i][j] = OPEN;
        if (i+1 < Y) Combination(i+1,j); //up
        if (0<=i-1)  Combination(i-1,j); //down
        if (j+1<X)   Combination(i,j+1); //right
        if (0<=j-1)  Combination(i,j-1); //left

        if (0<=i-1 && 0<=j-1) Combination(i-1,j-1);
        if (i+1<Y && 0<=j-1) Combination(i+1,j-1);

        if (0<=i-1 && j+1<X) Combination(i-1,j+1);
        if (i+1<Y && j+1<X) Combination(i+1,j+1);
    }
    else return;
}

void Tmp_Screen(char *s)
{
    int x = 60, y = 1;
    char TMP[][45] = {
        {"?{?|?|?|?|?|?|?|?|?|?|?|?|?{"},
        {"?bE?@Flag?@P?@End?@?@?@?@ ?b"},
        {"?bW ???@S ???@A ???@D ?N?@?b"},       
        {"?{?|?|?|?|?|?|?|?|?|?|?|?|?{"},

    };

    for (int i = 0; i < 4 ; i++)
    {
        printf("\033[%d;%dH" ,y++,x);
        printf("%s\n",TMP[i]);
    }
    printf("\033[%d;%dH" ,y++,x);
    printf("\t  [ %s Mode ]\n",s);
}