#include <stdio.h>
#include "Title.h"

void Title_Print()
{
    int press;

    system("cls");
    printf("\n\t 2021  8/7\n");
    sleep(1);
    printf("\tONODA  TERUAKI\n");
    sleep(2);
    system("cls");
    printf("\n\t\n");
    printf("--- TEST GAME ---\n");
    sleep(2);
    printf("      �e�X�g\n\n");
    sleep(1);
    printf("<< Press button to start >>\n");

    press = getch();

    system("cls");
    sleep(3);
}

void init_setter(void) // title
{
    int i,j;
    int cmd = 0;
    int res;
    int data;

    Title_Print();
    while (1)
    {
        RE:
        printf("+--------------+\n");
        cmd==0? printf("+ ���߂��� <-- +\n") : printf("+ ���߂���     +\n");
        cmd==1? printf("+ �������� <-- +\n") : printf("+ ��������     +\n");
        cmd==2? printf("+ ��߂�   <-- +\n"): printf("+ ��߂�       +\n");
        printf("+--------------+\n\n");
        printf("(W...UP / S...DOWN)\n");

        res =  getch();
        if (res == 'w') {
            cmd == 0 ? cmd = 2 : cmd--;
        }
        if (res == 's') {
            cmd == 2 ? cmd = 0 : cmd++;
        }
        else if (res == 13) {
            break;
        }

        Cmd_Reset(1);
    }

    if (cmd == 1) { 
        if (Data_Load() == 1) {
            system("cls");
            goto RE;
        }
        else 
            file_flg = 1;
    }
    if (cmd == 2) exit(0);
}

void DOWN_SLOW(int res)
{
    Cmd_Reset(1);
    sleep(1);
    // printf("\n\n\n\t << %d �K >> \n",res);
    printf("\n\n\n\t << Start >> \n");
    sleep(2);
    system("cls");
}