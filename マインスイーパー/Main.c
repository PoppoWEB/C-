#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "Print.h"

void Reset(void) 
{
    printf("\033[%d;%dH" ,7,0);
    printf("\033[J");
}

int Title(void)
{
    int ch;
    int cmd = 0;
    char take[] = "2021 8/12 - 8/17";
    char name[] = "Å{ Onoda Teruaki\n\t       Åó Abc404Hz";
    char str[] = "| MINESWEEPER |";

    system("cls");
    printf("\n\n\n\t\t");
    for (int i = 0; take[i] != '\0'; i++)
    {
        if (kbhit()) {
            if (ch = getch())
            goto TT;
        } 

        printf("%c",take[i]);
        sleep(0.05);
    }
    printf("\n\t       ");
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (kbhit()) {
            if (ch = getch())
            goto TT;
        }

        printf("%c",name[i]);
        sleep(0.05);
    }
    sleep(2);

    TT:
    system("cls");
    printf("\n\n\n\t\t");
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c",str[i]);
        sleep(0.05);
    }
    printf("\n\t\t\t\tver 3.1.2");
    printf("\n\n");

    TT2:
    cmd = 0;
    while (1)
    {
        if (cmd == 0) { 
            printf("\033[32m");
            printf("\t\t  + START <--\n");
        }
        else          printf("\t\t  + START\n");
        printf("\033[39m");
        
        if (cmd == 1) {
            printf("\033[32m");
            printf("\t\t  + END   <--\n");
        }
        else          printf("\t\t  + END  \n");
        printf("\033[39m");
        
        ch = getch();
        if (ch == 'w') {
            cmd--;
            if (cmd < 0) cmd = 1;
        }
        else if (ch == 's') {
            cmd++;
            if (cmd > 1) cmd = 0;
        }
        else if (ch == 13) {
            if (cmd == 1) exit(1);
            else break;
        }
        Reset();
    }

    cmd = 0;
    Reset();
    while (1)
    {
        if (cmd == 0) { 
            printf("\033[32m");
            printf("\t  + Easy <--");
        }
        else          printf("\t  + Easy");
        printf("\033[39m");
        
        if (cmd == 1) {
            printf("\033[32m");
            printf("\t+ Normal   <--");
        }
        else          printf("\t+ Normal  ");
        printf("\033[39m");

        if (cmd == 2) {
            printf("\033[32m");
            printf("\t+ Hard   <--");
        }
        else          printf("\t+ Hard  ");
        printf("\033[39m");

        if (cmd == 3) {
            printf("\033[32m");
            printf("\t+ Back   <--");
        }
        else          printf("\t+ Back  ");
        printf("\033[39m");

        ch = getch();
        if (ch == 'a') {
            cmd--;
            if (cmd < 0) cmd = 3;
        }
        else if (ch == 'd') {
            cmd++;
            if (cmd > 3) cmd = 0;
        }
        else if (ch == 13) {
            if (cmd == 3) { 
                Reset();
                goto TT2;
            }
            else break;
        }
        Reset();
    }
 
    system("cls");
    printf("\n\n\n\t\t");
    printf("| Game Start |");
    printf("\n\t\t   -Enter-\n");
    getch();
    sleep(1);

    return cmd;
}

int main(int argc,char *argv[])
{
    int x, y;
    int ch, flg;
    int cmd,res;
    int Hard;
    char *p;
    clock_t Start, End;

    Hard = Title();
    p = Hard==0?"Easy":Hard==1?"Normal":"Hard";
    RE:
    system("cls");
    Initialize(Hard);
    
    x = 0,y = 0;
    cmd = 0,res = 0, flg = 0;
    Start = clock();
    RePoint(x,y);
    Tmp_Screen(p);

    while (flg != 1 && res != 1)
    {
        if (kbhit())
        {
            Tmp_Screen(p);
            cpx = x;
            cpy = y;

            ch = getch();
            if (ch == 'd') {
                x++;
                if (x >= X) x = 0;
            }
            else if (ch == 'a') {
                x--;
                if (x < 0) x = X-1;
            }
            else if (ch == 'w') {
                y--;
                if (y < 0) y = Y-1;
            }
            else if (ch == 's') {
                y++;
                if (y >= Y) y = 0;
            }
            else if (ch == 'e') {
                Flag_Point(y,x);
            }
            else if (ch == 'p') res = 1;

            if (ch == 13 && res != 1) {
                if (MAP[y][x] == BOMB && KEY[y][x] != FLAG) res = 1;
                else if (KEY[y][x] != FLAG) Combination(y,x);
                system("cls");
                Reprint(y,x);
            }
            else 
            {
                RePoint(x,y);
            }
            Tmp_Screen(p);
            flg = Clear();
        }
        printf("\033[%d;%dH" ,6,60);
        printf("Time: %.2lfs",(double)(clock()-Start)/CLOCKS_PER_SEC);
    }
    system("cls");
    Open_Oll();
    End = clock();

    if (flg == 1) printf("\033[%d;%dH" ,Y,0),printf("\n\t<< Game Clear! >> "),printf(" Time: %.2lfs\n",(double)(End-Start)/CLOCKS_PER_SEC);
    if (res == 1) printf("\033[%d;%dH" ,Y+1,0),printf("\n\t<< Game Over! >>"), printf(" Time: %.2lfs",(double)(End-Start)/CLOCKS_PER_SEC);

    printf("\n\t + Ç‡Ç§àÍìxÉvÉåÉCÇµÇ‹Ç∑Ç© +\n\n");
    while (1)
    {
        cmd == 0 ? printf("\033[32m"),printf("\t - YES <--\n") : printf("\t - YES\n");
        printf("\033[39m");

        cmd == 1 ? printf("\033[32m"),printf("\t - NO  <--\n") : printf("\t - NO\n");
        printf("\033[39m");
        
        res = getch();

        if (res == 'w') {
            cmd--;
            if (cmd < 0) cmd = 1;
        }
        if (res == 's') {
            cmd++;
            if (cmd > 1) cmd = 0;
        }

        printf("\033[%d;%dH" ,25,0);
        printf("\033[J");

        if (res == 13) {
            if (cmd == 0) goto RE;
            if (cmd == 1) exit(1);
        }
    }

    return 0;
}