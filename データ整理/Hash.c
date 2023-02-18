#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "Hash.h"

int Hash(int n)
{
    return n%MAX;
}

void Initialize(List *n)
{
    int i;
    
    do
    {
        printf("\t+ ハッシュ値を入力してください +\n");
        printf("\tHASH: ");
        scanf("%d",&MAX);
        if (MAX <= 0) {
            printf("\033[31m");
            printf("\t0より大きい値を入力してください。\n\t\t---Enter---");
            printf("\033[39m");
            getch();
            printf("\033[%d;%dH",1,1);
            printf("\033[2J");
        }

    } while (MAX <= 0);
    
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

Node *Make_Data(Node x)
{
    Node *s;
    int len = strlen(x.name); 

    s = calloc(1,sizeof(Node));
    if (s == NULL)
    {
        printf("\033[31m");
        printf("\tメモリを確保出来ませんでした。\n");
        printf("\033[39m");

        printf("\tプログラムを終了します。\n");
        exit(1);
    }

    s->name = (char*)malloc(sizeof(char)*(len+1));
    s->name[0] = '\0';
    strcpy(s->name,x.name);

    s->val = x.val;
    s->next = NULL;

    return s;
}

void Add(List *n,Node *x,int r)
{
    int i;
    int key = Hash(x->val);
    Node *p = n->table[key];

    while (p != NULL)
    {
        if (p->val == x->val) {
            if (r == 1) {
                printf("\033[31m");
                printf("\t既にそのデータは追加済みです。\n");
                printf("\033[39m");
            }
            return;
        }
        p = p->next;
    }

    Node *s = Make_Data(*x);
    s->next = n->table[key];
    n->table[key] = s;
    if (r == 1) {
        printf("\033[32m");
        printf("\tデータを追加しました。\n");
        printf("\033[39m");
    }
}

void Delete(List *n,Node *x)
{
    int i;
    int key = Hash(x->val);
    Node *p = n->table[key];
    Node **pp = &n->table[key];

    while (p != NULL)
    {
        if (p->val == x->val)
        {
            printf("\033[32m");
            printf("\t(%d) %sのデータを削除しました。\n",p->val,p->name);
            printf("\033[39m");
            *pp = p->next;
            free(p);
            return;
        }
        pp = &p->next;
        p = p->next;
    }
    
    printf("\033[31m");
    printf("\tデータが見つかりませんでした。\n");
    printf("\033[39m");
}

void Print_Vec(List *n)
{
    Node *p;
    int i;

    printf("\t----DATA----\n");
    for ( i = 0; i < MAX; i++)
    {
        p = n->table[i];
        printf("\tN.%d: ",i+1);
        while (p != NULL)
        {
            printf("(%d) %s →",p->val,p->name);
            p = p->next;
        }
        printf("NULL\n");
    }
    printf("\t----END----\n");
}

void Search(List *n,Node *x)
{
    int i = 0;
    int key = Hash(x->val);
    Node *p = n->table[key];

    while (p != NULL)
    {
        if (p->val == x->val)
        {
            printf("\033[32m");
            printf("\tナンバーが見つかりました。\n");
            printf("\tHash No.%d\n",i+1);
            printf("\t番号 %d , 氏名 %s\n",p->val,p->name);
            printf("\033[39m");
            return;
        }
        p = p->next;
        i++;
    }

    printf("\033[31m");
    printf("\tデータが見つかりませんでした。\n");
    printf("\033[39m");
}

void Clear(List *n)
{
    Node *p;
    int i;
    
    for ( i = 0; i < MAX; i++)
    {
        p = n->table[i];
        while (p != NULL)
        {
            Node *s = p->next;
            free(s);
            p = s;
        }
        n->table[i] = NULL;
    }
    
    printf("\033[31m");
    printf("\tデータを全て削除しました。\n");
    printf("\033[39m");
}