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
                printf("��");
            }
            else
            {
                if (Maze[i][j] == 1) printf("��");
                else if (Maze[i][j] == 0) {
                    if (rand()%10 > 7 && tmp > 0 && i > 4) printf("��"), Maze[i][j] = 2,tmp--;
                    else printf("�@");
                }
                else  if (Maze[i][j] == 2) printf("��");
                else if (Maze[i][j] == 3) printf("��");
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
        if (Maze[cpx][i] == 1) printf("��");
        if (Maze[cpx][i] == 0) printf("�@");
        if (Maze[cpx][i] == 2) printf("��");
        if (Maze[cpx][i] == 3) printf("��");
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
            printf("��");
        else {
            if (Maze[px][i] == 1) printf("��");
            if (Maze[px][i] == 0) printf("�@");
            if (Maze[px][i] == 2) printf("��");
            if (Maze[px][i] == 3) printf("��");
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
        printf("��������ɓ��ꂽ\n");
        printf("%s��MP��%d�񕜂���\n",p->nameP,tmp);
        p->C_MP += tmp;
        if (p->C_MP >= p->MP) p->C_MP = p->MP;
    }
    else 
    {
        printf("�i������������\n");
        printf("%s��HP��%d�񕜂���\n",p->nameP,tmp);
        p->C_HP += tmp;
        if (p->C_HP >= p->HP) p->C_HP = p->HP;
    }

    Maze[px][py] = 0;
    sleep(2);
    Cmd_Reset(0);
}