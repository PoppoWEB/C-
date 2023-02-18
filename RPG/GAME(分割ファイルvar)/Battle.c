#include "BASE.h"
#include "Battle.h"
#include <stdio.h>

void Atk_Attack(emy *e, ply *p,int flg, int Def)
{
    int tmp;

    switch (flg)
    {
        case 0: // ATK
            tmp = (p->ATK-e->DEF/2)*(99+rand()%55)/256;
            printf("\033[36m"); //color blue
            printf("%d É_ÉÅÅ[ÉWÇó^Ç¶ÇΩ!\n",tmp);
            e->HP -= tmp;
            printf("\033[37m");
            break;
        case 1: // OUT
            tmp = (e->ATK-Def/2)*(99+rand()%55)/256;
            if (tmp < 0) tmp = 0;
            printf("\033[33m"); //color red
            printf("%s ÇÕ %d É_ÉÅÅ[ÉWéÛÇØÇΩ\n",p->nameP,tmp);
            p->C_HP -= tmp;
            if (p->C_HP <= 0) p->C_HP = 0;
            
            printf("\033[37m"); // whit
            printf("\033[%d;%df",3,0);
            printf("+ HP: %d MP: %d ",p->C_HP,p->C_MP);
            break;
    }
    sleep(1);
    printf("\033[%d;%df",20,0);
    printf("\033[2K");
}

int Command_Mgi(mgi m)
{
    int cmd = 0;
    int res, i;

    Cmd_Reset(0);
    while (1)
    {
        printf("< Command > \n");
        for (int i = 0; i < MAGICS; i++ )
        {
            printf("%s:",m.MAG[i]);
            if (i == cmd) printf("  <--");
            printf("\n");
        }
        cmd == 4 ? printf("ñﬂÇÈ:  <--\n\n") : printf("ñﬂÇÈ: \n\n");

        res =  getch();
        if (res == 'w') {
            cmd == 0 ? cmd = 4 : cmd--;
        }
        if (res == 's') {
            cmd == 4 ? cmd = 0 : cmd++;
        }
        else if (res == 13) {
            break;
        }

        Cmd_Reset(0);
    }

    return cmd;
}

void Mgi_Attack(mgi m,emy *e, ply *p,int res)
{
    int tmp;
    switch (res)
    {
        case 0:
            tmp = p->MTK*0.4+5;
            p->C_MP -= 1;
            break;
        case 1:
            tmp = 1+rand()%30;
            p->C_HP += tmp;
            if (p->C_HP >= p->HP) p->C_HP = p->HP;
            p->C_MP -= 2;
            break;
        case 2:
            tmp = p->MTK*0.8+1;
            p->C_MP -= 3;
            break;
        case 3:
            tmp = p->MTK*1;
            p->C_MP -= 4;
            break;
        case 4:
            return;
    }

    printf("\033[36m"); //color blue
    if (res == 1) { 
        printf("%d âÒïúÇµÇΩ!\n",tmp);
        return;
    }
    else printf("%d É_ÉÅÅ[ÉWÇó^Ç¶ÇΩ!\n",tmp);

    printf("\033[37m"); // whit
    printf("\033[%d;%df",3,0);
    printf("+ HP: %d MP: %d ",p->C_HP,p->C_MP);

    sleep(1);
    printf("\033[%d;%df",20,0);
    printf("\033[2K");

    e->HP -= tmp;
}

int UPS_DATA(void) { return 1+rand()%5; }

void LEVEL_UP(ply *p)
{
    int UPS;
    p->C_LV = 0;
    printf("--- LEVEL UP ---\n\n");
    printf("LV %d Å® %d \n",p->LV++,p->LV);
    
    UPS = UPS_DATA();
    printf("HP %d Å® %d\n",p->HP,p->HP+UPS);
    p->HP += UPS;

    UPS = UPS_DATA();
    printf("MP %d Å® %d\n",p->MP,p->MP+UPS);
    p->MP += UPS;

    UPS = UPS_DATA();
    printf("ATK %d Å® %d\n",p->ATK,p->ATK+UPS);
    p->ATK += UPS;

    UPS = UPS_DATA();
    printf("DEF %d Å® %d\n",p->DEF,p->DEF+UPS);
    p->DEF += UPS;

    UPS = UPS_DATA();
    printf("MTK %d Å® %d\n",p->MTK,p->MTK+UPS);
    p->MTK += UPS;

    sleep(3);
}

int battle_Set(emy *e,ply *p,mgi m)
{
    int i,j;
    int cmd = 0;
    int res;
    int DEF = p->DEF;

    // Start

    system("cls");
    // LV HP MP 
    printf("+");
    For_15();
    printf("+ Lv : %d\n",p->LV);
    printf("+ HP: %d MP: %d \n+",p->C_HP,p->C_MP);

    For_15();

    // battle field
    printf("< Ememy: %s >\n",e->name);
    printf("\n\n\n\n");
    printf("     %s\n",e->Grap);
    printf("+---------------+\n");

    while (e->HP > 0 & cmd != 1 & p->HP > 0)
    {
        // cmd
        DEF = p->DEF;

        while (1)
        {
            printf("< Command > \n");
            cmd == 0 ? printf("çUåÇ: <--\n") : printf("çUåÇ:\n");
            cmd == 1 ? printf("ì¶ëñ: <--\n") : printf("ì¶ëñ:\n");
            cmd == 2 ? printf("ñhå‰: <--\n") : printf("ñhå‰:\n");
            cmd == 3 ? printf("ì¡ãZ: <--\n\n") : printf("ì¡ãZ:\n\n");

            res =  getch();
            if (res == 'w') {
                cmd == 0 ? cmd = 3 : cmd--;
            }
            if (res == 's') {
                cmd == 3 ? cmd = 0 : cmd++;
            }
            else if (res == 13) {
                if (cmd == 3) { 
                    res = Command_Mgi(m);
                }
                break;
            }

            Cmd_Reset(0);
        } // cmd set
        
        // battle set 

        if (cmd == 0)  printf("%sÇÃçUåÇ\n",p->nameP),Atk_Attack(e, p, 0,DEF);
        else if (cmd == 1) {
            printf("%sÇÕì¶Ç∞ÇΩ\n",p->nameP);
            init_emy(e);
            sleep(2);
            return NEXT;
        }
        else if (cmd == 2) printf("%sÇÃñhå‰\n",p->nameP), DEF *= 2;
        else if (cmd == 3) Mgi_Attack(m, e,p,res);

        if (res != 4) sleep(1), Atk_Attack(e, p, 1,DEF);

        Cmd_Reset(0);
    }

    printf("<< Battle End >> \n");
    res = e->HP <= 0 ? NEXT : p->HP <= 0 ? OVER : NEXT;

    if (res == NEXT) {
        printf("\033[%d;%df",10,0); 
        printf("\033[2K");       
        printf("\033[%d;%df",14,0); 
        printf("   %s WIN !!\n",p->nameP);
        int GET = 1+rand()%10;
        printf("EXP%dÇéËÇ…ì¸ÇÍÇΩ\n",GET);
        p->C_LV += GET;
        if (p->C_LV >= 10) {
            LEVEL_UP(p);
        }
    }
    if (res == OVER) printf("\t%s LOSE...\n",p->nameP);

    sleep(3);
    init_emy(e);

    return res;
}

int Battle(emy *e,ply *p,mgi m)
{
    system("cls");
    return battle_Set(e,p,m);
}