#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"

FILE *fp;

void FInitial(List *n,int MAX)
{
    int i;

    n->table = calloc(MAX,sizeof(Node*));
    if (n->table == NULL)
    {
        printf("\033[31m");
        printf("\tメモリを確保出来ませんでした。\n");
        printf("\033[39m");

        printf("\tプログラムを終了します。\n");
        exit(1);
    }

    for ( i = 0; i < MAX; i++)
    {
        n->table[i] = NULL;
    }
}

void Save(List *n,char *Fname)
{
    Node *p;
    fp = fopen(Fname,"w");
    if (fp == NULL)
    {
        printf("\033[31m");
        printf("\tファイルをオープンできませんでした。\n");
        printf("\033[39m");
        return;
    }

    fprintf(fp,"%d\n",MAX);
    for (int i = 0; i < MAX; i++)
    {
        p = n->table[i];
        while (p != NULL)
        {
            fprintf(fp,"%d %s ",p->val,p->name);
            p = p->next;
        }
        fprintf(fp,"\n");
    }
        
    fclose(fp);
}

void Load(List *n,char *Fname)
{
    int N;
    char tmp[100];
    Node *p;
    Node s;

    fp = fopen(Fname,"r");

    if (fp == NULL)
    {
        printf("\033[31m");
        printf("\tファイルをオープンできませんでした。\n");
        printf("\033[39m");
        exit(1);
    }

    if (fscanf(fp,"%d",&MAX) == EOF) {
        printf("\033[31m");
        printf("\tデータが存在しません。\n");
        printf("\033[39m");
        exit(1);
    }

    FInitial(n,MAX);

    while (1)
    {

        if (fscanf(fp,"%d",&s.val) == EOF) {
            break;
        }

        fscanf(fp,"%s",tmp);
        s.name = (char*)malloc(sizeof(char)*(strlen(tmp)+1));
        s.name[0] = '\0';
        strcpy(s.name,tmp);
        Add(n,&s,-1);
        
    }

    fclose(fp);
}