#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "Save.h"
#include "System.h"

void Title(void)
{
    system("cls");
    int ch;
    char state[] = "2021 8/13";
    char name[] = "Onoda Teruaki";
    char str[] = "| Hash Data |";

    printf("\t");
    for (int i = 0; state[i] != '\0'; i++)
    {
        if(kbhit()) 
            if (getch()) goto GG;
        printf("%c",state[i]);
        sleep(0.1);
    }
    printf("\n\t");
    for (int i = 0; name[i] != '\0'; i++)
    {
        if(kbhit()) 
            if (getch()) goto GG;
        printf("%c",name[i]);
        sleep(0.1);
    }
    sleep(1);
    GG:

    system("cls");
    printf("\t");
    for (int i = 0; str[i] != '\0'; i++)
    {
        if(kbhit()) 
            if (getch()) break;
        printf("%c",str[i]);
        sleep(0.1);
    }
    sleep(1);
}

Node Set_Data(char *p)
{
    Node n;
    char name[100];

    printf("\t%s����l����͂��Ă��������B\n",p);
    printf("\t�i���o�[: ");
    scanf("%d",&n.val);
    printf("\t���������: ");
    scanf("%s",name);

    n.name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if (n.name == NULL)
    {
        printf("\033[31m");
        printf("\t���������m�ۏo���܂���ł����B\n");
        printf("\033[39m");

        printf("\t�v���O�������I�����܂��B\n");
        exit(1);
    }
    n.name[0] = '\0';
    strcpy(n.name,name);

    return n;
}

int main(int argc,char *argv[])
{
    int cmd = 0;
    int res;
    char *table[] = {"Add","Delete","Print","Search","Clear","Save","End"};
    List li;
    
    Title();
    system("cls");
    if (argc >= 2)
    {
        printf("\t�t�@�C����: %s\n",argv[1]);
        printf("\t�f�[�^�����[�h���܂���?\n");
        printf("\tA �� / D ��\n");

        while(1) {
            cmd == 0 ? printf("\tYes <-- ") : printf("\tYes ");
            cmd == 1 ? printf("\tNo  <-- \n") : printf("No \n");

            res = getch();
            if (res == 'd') { 
                cmd++;
                if (cmd == 2) cmd = 0;
            }
            if (res == 'a') { 
                cmd--;
                if (cmd == -1) cmd = 1;
            }
            if (res == 13) break;
            Reset(0);
        }
        if (cmd == 0) Load(&li,argv[1]);
        else Initialize(&li);
    }
    else
    {
        Initialize(&li);
    }

    system("cls");
    do
    {
        Node n;
        switch (cmd = Print_table(table,7))
        {
        case 0:
            n = Set_Data("�ǉ�");
            Add(&li,&n,1);
            break;
        case 1:
            n = Set_Data("�폜");
            Delete(&li,&n);
            break;
        case 2:
            Print_Vec(&li);
            break;
        case 3:
            n = Set_Data("�T��");
            Search(&li,&n);
            break;
        case 4:
            Clear(&li);
            break;
        case 5:
            if (argc >= 2) Save(&li,argv[1]),printf("\033[32m"), printf("\tSave���������܂����B\n"),printf("\033[39m");
            else printf("\033[31m") ,printf("\tSave�͂ł��܂���B\n"), printf("\033[39m");
            break;
        case 6:
            printf("\t�v���O�������I�����܂��B\n");
            exit(1);
        }
        
        printf("\n\t---Enter---\n");
        getch();
        Reset(1);
    } while (cmd != 7);
    
    return 0;
}