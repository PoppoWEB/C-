#include "BASE.h"
#include "Print.h"

void For_15(void)
{
    int i;
    for ( i = 0; i < 15; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void Print_Maze(int px,int py)
{
    system("cls");
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (px == i && py == j)
            {
                printf("Åõ");
            }
            else
            {
                if (Maze[i][j] == 1) printf("Å°");
                else if (Maze[i][j] == 0) {
                    if (rand()%10 > 7 && tmp > 0 && i > 4) printf("Åö"), Maze[i][j] = 2,tmp--;
                    else printf("Å@");
                }
                else  if (Maze[i][j] == 2) printf("Åö");
                else if (Maze[i][j] == 3) printf("Åß");
            }
        }
        printf("\n");
    }
}

void Print_Ply_Reset(int px,int py)
{
    printf("\033[%d;%df",cpx+1,0);
    printf("\033[2K");
    for (int i = 0; i < Y ; i++)
    {
        if (Maze[cpx][i] == 1) printf("Å°");
        if (Maze[cpx][i] == 0) printf("Å@");
        if (Maze[cpx][i] == 2) printf("Åö");
        if (Maze[cpx][i] == 3) printf("Åß");
    }
    printf("\033[%d;%df",px+1,0);
    printf("\033[2K");
}

void Map_Reset(void)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (Maze[i][j] == 2) Maze[i][j] = 0;
        }
    }
}

void Print_Point_Maze(int px,int py,int mn)
{
    Print_Ply_Reset(px,py);
    for (int i = 0; i < Y; i++)
    {
        if (py == i)
            printf("Åõ");
        else {
            if (Maze[px][i] == 1) printf("Å°");
            if (Maze[px][i] == 0) printf("Å@");
            if (Maze[px][i] == 2) printf("Åö");
            if (Maze[px][i] == 3) printf("Åß");
        }
    }
    printf("\033[%d;%df",mn,0);
}

int Goal(int px,int py)
{
    if (Maze[px][py] == 3)
        return GOAL;    

    return NEXT;
}

void Item(ply *p,int px,int py)
{
    int tmp = 2+rand()%5;
    Cmd_Reset(0);

    if (tmp > 3)
    {
        printf("âåëêÇéËÇ…ì¸ÇÍÇΩ\n");
        printf("%sÇÃMPÇ™%dâÒïúÇµÇΩ\n",p->nameP,tmp);
        p->C_MP += tmp;
        if (p->C_MP >= p->MP) p->C_MP = p->MP;
    }
    else 
    {
        printf("ãiâåèäÇå©Ç¬ÇØÇΩ\n");
        printf("%sÇÃHPÇ™%dâÒïúÇµÇΩ\n",p->nameP,tmp);
        p->C_HP += tmp;
        if (p->C_HP >= p->HP) p->C_HP = p->HP;
    }

    Maze[px][py] = 0;
    sleep(2);
    Cmd_Reset(0);
}