#include "BASE.h"
#include "Print.h"
#include "Battle.h"
#include "Title.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int cpy,cpx;
extern FILE *fp;
extern int file_flg;
extern int tmp = 3;

extern int Maze[X][Y] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,1,1,1,1},
    {1,1,1,1,1,3,1,1,1,1,1},
};

void Cmd_Reset(int res)
{
    switch (res)
    {
        case 0: // battle cmd 用
            printf("\033[%d;%dH" ,12,0);
            printf("\033[0J");
            break;
        case 1: // maze 用
            printf("\033[%d;%dH" ,0,0);
            printf("\033[0J");
            break;
        case 2: // name set 用
            printf("\033[%d;%dH" ,9,0);
            printf("\033[0J");
            break;
        case 3:
            printf("\033[%d;%dH" ,21,0);
            printf("\033[0J");
            break;
    }
}

int main(void) 
{
    int cmd;
    int px = 1, py = 1;
    int goal = 3;
    int flg = 0;
    int res = 1;
    int down = 1;
    int try;
    ply pl;
    emy em;
    mgi mi;

    int mn = 12;
    
    RESET:
    system("cls");
    init_setter();
    init_mgi(&mi);
    init_ply(&pl,&px,&py);
    init_emy(&em);
    DOWN_SLOW(down);
    Print_Maze(px,py);
    
    while (res == NEXT)
    {
        flg = 0;
        cpx = px;
        cpy = py;

        printf("\n+-------------+\n");
        printf("HP: %d / MP: %d\n",pl.C_HP,pl.C_MP);
        printf("   A.← / D.→\n");
        printf("   W.↑ / S.↓\n");
        printf("   R == セーブ\n");
        printf("+-------------+\n");
        printf("Player (M)\n");
        printf("壁 (1) , 道 (0)\n");

        while(flg != 1) {
            cmd = getch();
            if (cmd == 'w') {
                if (Maze[px-1][py] != 1) {
                    px--;
                    flg = 1;
                }
            }

            if (cmd == 's') {
                if (Maze[px+1][py] != 1) {
                    px++;
                    flg = 1;
                }
            }
            
            if (cmd == 'a') {
                if (Maze[px][py-1] != 1) {
                    py--;
                    flg = 1;
                }
            }

            if (cmd == 'd') {
                if (Maze[px][py+1] != 1) {
                    py++;
                    flg = 1;
                }
            }

            if (cmd == 'r') {
                Data_Save(pl,px,py);
                Cmd_Reset(3);
            }
        }

        if (Maze[px][py] == 2) Item(&pl,px,py), flg = 0,Print_Point_Maze(px, py, mn);
        else if (Maze[px][py] == 0 || Maze[px][py] == 3){
            Print_Point_Maze(px, py, mn);
            res = Goal(px,py);
            if (res == GOAL) goto END;

            if (rand()%10 > 7 && flg != 0) {
                res = Battle(&em,&pl,mi);
                Print_Maze(px, py);
                if (res == OVER) goto END;
            }
        }
    }

    END:

    system("cls");
    if (res == OVER) printf("\n<< Game Over... >>\n");
    if (res == GOAL) printf("\n<< Game Clear!! >>\n");

    printf("もう一度やりますか\n(YES.1 / NO.0) : ");
    try = getch();
    if (try == '1') {
        px = 1, py = 1;
        goal = 3;
        flg = 0;
        res = 1;
        down = 1;
        tmp = 3;
        Map_Reset();
        goto RESET;
    }
    
    return 0;
}