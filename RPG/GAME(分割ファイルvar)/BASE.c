#include "BASE.h"
#include <stdio.h>

FILE *fp;

void init_mgi(mgi *m)
{
    m->MAG[0] = "根性焼き";
    m->MAG[1] = "一服";
    m->MAG[2] = "唾を吐く";
    m->MAG[3] = "ライターで燃やす";
}

void init_ply(ply *p,int *px,int *py)
{
    int tmp;
    int try;

    if (file_flg == 0)
    {
        p->LV = 1;
        p->HP = 50;
        p->MP = 15;
        p->ATK = 10;
        p->DEF = 5;
        p->MTK = 15;

        p->C_LV = 0;
        p->C_HP = 50;
        p->C_MP = 15;
        printf("プレイヤーの名前を決めてください(7文字)\n");
        do 
        {
            scanf("%s",p->nameP);
            tmp = strlen(p->nameP);
            if (tmp >= 7) {
                printf("名前が長すぎです。\n");
                sleep(1);
                Cmd_Reset(2);
            }
            else {
                printf("名前: %s でよろしいですか?\n",p->nameP);
                printf("YES.1 / NO.0 : ");
                try = getch();
                if (try == '0') Cmd_Reset(2);
            }

        }while(tmp >= '7' || try == '0');
    }
    else 
    {
        for (int i = 0; i < DATA; i++)
        {
            fscanf(fp,"%d",&tmp);

            i == 0 ? p->HP = tmp :
            i == 1 ? p->MP = tmp :
            i == 2 ? p->ATK = tmp:
            i == 3 ? p->DEF = tmp:
            i == 4 ? p->MTK = tmp:
            i == 5 ? p->C_LV = tmp:
            i == 6 ? p->C_HP = tmp:
            i == 7 ? p->C_MP = tmp:
            i == 8 ? p->LV = tmp : 0;
        }
        fscanf(fp,"%s",p->nameP);
        fscanf(fp,"%d",px);
        fscanf(fp,"%d",py);
        fclose(fp);
    }

    p->cmds[0] = "攻撃";
    p->cmds[1] = "逃走";
    p->cmds[2] = "防御";
}

void init_emy(emy *e)
{
    int tmp = rand()%3;
    if (tmp == 0)
    {
        e->HP = 15;
        e->MP = 10;
        e->ATK = 7;
        e->DEF = 3;
        e->MTK = 7;
        e->Grap = "('ω')";
        e->name = "Type A";
    }
    if (tmp == 1)
    {
        e->HP = 30;
        e->MP = 5;
        e->ATK = 9;
        e->DEF = 5;
        e->MTK = 1;
        e->Grap = "('Д')";
        e->name = "Type B";
    }
    if (tmp == 2)
    {
        e->HP = 25;
        e->MP = 15;
        e->ATK = 10;
        e->DEF = 2;
        e->MTK = 8;
        e->Grap = "(?_?)";
        e->name = "Type C";
    }
}

int Data_Load(void)
{
    int tmp;
    fp = fopen("Data.txt","r");
    if (fp == NULL) {
        printf("セーブデータファイルが存在しません。\n");
        printf("同じディレクトリ内に\"Data.txt\"ファイルを作成してください。\n");
        fclose(fp);
        sleep(1);
        return 1;
    }
    else if (fscanf(fp,"%d",&tmp) == EOF) {
        printf("セーブデータが存在しません。\n");
        fclose(fp);
        sleep(1);
        return 1;
    }
    
    return 0;
}

void Data_Save(ply p,int px,int py)
{
    fp = fopen("Data.txt","w");
    fprintf(fp,"%d ",p.LV);
    fprintf(fp,"%d ",p.HP);
    fprintf(fp,"%d ",p.MP);
    fprintf(fp,"%d ",p.ATK);
    fprintf(fp,"%d ",p.DEF);
    fprintf(fp,"%d ",p.MTK);
    fprintf(fp,"%d ",p.C_LV);
    fprintf(fp,"%d ",p.C_HP);
    fprintf(fp,"%d ",p.C_MP);
    fprintf(fp,"%d ",p.LV);
    fprintf(fp,"%s ",p.nameP);
    fprintf(fp,"%d %d ",px,py);
    fclose(fp);

    printf("データをSaveしました。\n");
    sleep(1);
}