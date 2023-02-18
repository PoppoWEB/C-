#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "System.h"

void Reset(int set)
{
    switch (set)
    {
    case 0: // Start 
        printf("\033[%d;%dH",4,1);
        printf("\033[2K");
        break;
    case 1: // add delete search
        printf("\033[%d;%dH",1,1);
        printf("\033[2J");
        break;
    case 2:
        printf("\033[%d;%dH",1,1);
        printf("\033[2J");
        break;
    }
}

int Print_table(char *table[],int T)
{
    int i;
    int cmd = 0;
    int res;

    while (1)
    {
        printf("\t");
        for (i = 0; i < T; i++)
        {
            if (cmd == i) {
                printf("%s <-- ",table[i],i+1);
            }
            else printf("%s     ",table[i],i+1);
        }
        printf("\033[%d;%dH",3,0);

        res = getch();
        if (res == 'd') {
            cmd++;
            if (cmd >= T) cmd = 0;
        }
        if (res == 'a') {
            cmd--;
            if (cmd < 0) cmd = T-1;
        }
        if (res == 13) {
            return cmd;
        }

        Reset(2);
    }
    return 0;
}