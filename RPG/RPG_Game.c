#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define X     11
#define Y     11
#define OVER  -1
#define GOAL   0
#define NEXT   1
#define MAGICS 4
#define DATA   9
#define sleep(t) Sleep(t*1000)

FILE *fp;
int file_flg = 0;
int cpy,cpx, tmp = 3;

typedef struct PLY
{
    int LV;
    int HP;
    int MP;
    int ATK;
    int DEF;
    int MTK;

    int C_HP;
    int C_MP;
    int C_LV;

    char nameP[8];
    char *cmds[3];
} ply;

typedef struct ENEMY
{
    int HP;
    int MP;
    int ATK;
    int DEF;
    int MTK;

    int EXP;

    char *Grap;
    char *name;
}emy;

typedef struct MAGIC
{
    char *MAG[4];
} mgi;

int Maze[X][Y] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,1,1,1,1},
    {1,1,1,1,1,3,1,1,1,1,1},
};

void Cmd_Reset(int res)
{
    switch (res)
    {
        case 0: // battle cmd 用
            printf("\033[%d;%dH" ,12,0);
            printf("\033[0J");
            break;
        case 1: // maze 用
            printf("\033[%d;%dH" ,0,0);
            printf("\033[0J");
            break;
        case 2: // name set 用
            printf("\033[%d;%dH" ,9,0);
            printf("\033[0J");
            break;
        case 3:
            printf("\033[%d;%dH" ,21,0);
            printf("\033[0J");
            break;
    }
}

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
/* Print */

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
                printf("○");
            }
            else
            {
                if (Maze[i][j] == 1) printf("■");
                else if (Maze[i][j] == 0) {
                    if (rand()%10 > 7 && tmp > 0 && i > 4) printf("★"), Maze[i][j] = 2,tmp--;
                    else printf("　");
                }
                else  if (Maze[i][j] == 2) printf("★");
                else if (Maze[i][j] == 3) printf("〒");
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
        if (Maze[cpx][i] == 1) printf("■");
        if (Maze[cpx][i] == 0) printf("　");
        if (Maze[cpx][i] == 2) printf("★");
        if (Maze[cpx][i] == 3) printf("〒");
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
            printf("○");
        else {
            if (Maze[px][i] == 1) printf("■");
            if (Maze[px][i] == 0) printf("　");
            if (Maze[px][i] == 2) printf("★");
            if (Maze[px][i] == 3) printf("〒");
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

/* Print */

/* Battle */

void Atk_Attack(emy *e, ply *p,int flg, int Def)
{
    int tmp;

    switch (flg)
    {
        case 0: // ATK
            tmp = (p->ATK-e->DEF/2)*(99+rand()%55)/256;
            printf("\033[36m"); //color blue
            printf("%d ダメージを与えた!\n",tmp);
            e->HP -= tmp;
            printf("\033[37m");
            break;
        case 1: // OUT
            tmp = (e->ATK-Def/2)*(99+rand()%55)/256;
            if (tmp < 0) tmp = 0;
            printf("\033[33m"); //color red
            printf("%s は %d ダメージ受けた\n",p->nameP,tmp);
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
        cmd == 4 ? printf("戻る:  <--\n\n") : printf("戻る: \n\n");

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
        printf("%d 回復した!\n",tmp);
        return;
    }
    else printf("%d ダメージを与えた!\n",tmp);

    printf("\033[37m"); // whit
    printf("\033[%d;%df",3,0);
    printf("+ HP: %d MP: %d ",p->C_HP,p->C_MP);

    sleep(1);
    printf("\033[%d;%df",20,0);
    printf("\033[2K");

    e->HP -= tmp;
}

int UPS_DATA() { return 1+rand()%5; }

void LEVEL_UP(ply *p)
{
    int UPS;
    p->C_LV = 0;
    printf("--- LEVEL UP ---\n\n");
    printf("LV %d → %d \n",p->LV++,p->LV);
    
    UPS = UPS_DATA();
    printf("HP %d → %d\n",p->HP,p->HP+UPS);
    p->HP += UPS;

    UPS = UPS_DATA();
    printf("MP %d → %d\n",p->MP,p->MP+UPS);
    p->MP += UPS;

    UPS = UPS_DATA();
    printf("ATK %d → %d\n",p->ATK,p->ATK+UPS);
    p->ATK += UPS;

    UPS = UPS_DATA();
    printf("DEF %d → %d\n",p->DEF,p->DEF+UPS);
    p->DEF += UPS;

    UPS = UPS_DATA();
    printf("MTK %d → %d\n",p->MTK,p->MTK+UPS);
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
            cmd == 0 ? printf("攻撃: <--\n") : printf("攻撃:\n");
            cmd == 1 ? printf("逃走: <--\n") : printf("逃走:\n");
            cmd == 2 ? printf("防御: <--\n") : printf("防御:\n");
            cmd == 3 ? printf("特技: <--\n\n") : printf("特技:\n\n");

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

        if (cmd == 0)  printf("%sの攻撃\n",p->nameP),Atk_Attack(e, p, 0,DEF);
        else if (cmd == 1) {
            printf("%sは逃げた\n",p->nameP);
            init_emy(e);
            sleep(2);
            return NEXT;
        }
        else if (cmd == 2) printf("%sの防御\n",p->nameP), DEF *= 2;
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
        printf("EXP%dを手に入れた\n",GET);
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

/* Battle */

/* title */

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
    printf("      テスト\n\n");
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
        cmd==0? printf("+ 初めから <-- +\n") : printf("+ 初めから     +\n");
        cmd==1? printf("+ 続きから <-- +\n") : printf("+ 続きから     +\n");
        cmd==2? printf("+ やめる   <-- +\n"): printf("+ やめる       +\n");
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
    // printf("\n\n\n\t << %d 階 >> \n",res);
    printf("\n\n\n\t << Start >> \n");
    sleep(2);
    system("cls");
}

void Item(ply *p,int px,int py)
{
    int tmp = 2+rand()%5;
    Cmd_Reset(0);

    if (tmp > 3)
    {
        printf("煙草を手に入れた\n");
        printf("%sのMPが%d回復した\n",p->nameP,tmp);
        p->C_MP += tmp;
        if (p->C_MP >= p->MP) p->C_MP = p->MP;
    }
    else 
    {
        printf("喫煙所を見つけた\n");
        printf("%sのHPが%d回復した\n",p->nameP,tmp);
        p->C_HP += tmp;
        if (p->C_HP >= p->HP) p->C_HP = p->HP;
    }

    Maze[px][py] = 0;
    sleep(2);
    Cmd_Reset(0);
}

int main(void) 
{
    int cmd;
    int px = 1, py = 1;
    int goal = 3;
    int flg = 0;
    int res = 1;
    int down = 1;
    int try;
    ply pl;
    emy em;
    mgi mi;

    int mn = 12;
    
    RESET:
    system("cls");
    init_setter();
    init_mgi(&mi);
    init_ply(&pl,&px,&py);
    init_emy(&em);
    DOWN_SLOW(down);
    Print_Maze(px,py);
    
    while (res == NEXT)
    {
        flg = 0;
        cpx = px;
        cpy = py;

        printf("\n+-------------+\n");
        printf("HP: %d / MP: %d\n",pl.C_HP,pl.C_MP);
        printf("   A.← / D.→\n");
        printf("   W.↑ / S.↓\n");
        printf("   R == セーブ\n");
        printf("+-------------+\n");
        printf("Player (M)\n");
        printf("壁 (1) , 道 (0)\n");

        while(flg != 1) {
            cmd = getch();
            if (cmd == 'w') {
                if (Maze[px-1][py] != 1) {
                    px--;
                    flg = 1;
                }
            }

            if (cmd == 's') {
                if (Maze[px+1][py] != 1) {
                    px++;
                    flg = 1;
                }
            }
            
            if (cmd == 'a') {
                if (Maze[px][py-1] != 1) {
                    py--;
                    flg = 1;
                }
            }

            if (cmd == 'd') {
                if (Maze[px][py+1] != 1) {
                    py++;
                    flg = 1;
                }
            }

            if (cmd == 'r') {
                Data_Save(pl,px,py);
                Cmd_Reset(3);
            }
        }

        if (Maze[px][py] == 2) Item(&pl,px,py), flg = 0,Print_Point_Maze(px, py, mn);
        else if (Maze[px][py] == 0 || Maze[px][py] == 3){
            Print_Point_Maze(px, py, mn);
            res = Goal(px,py);
            if (res == GOAL) goto END;

            if (rand()%10 > 7 && flg != 0) {
                res = Battle(&em,&pl,mi);
                Print_Maze(px, py);
                if (res == OVER) goto END;
            }
        }
    }

    END:

    system("cls");
    if (res == OVER) printf("\n<< Game Over... >>\n");
    if (res == GOAL) printf("\n<< Game Clear!! >>\n");

    printf("もう一度やりますか\n(YES.1 / NO.0) : ");
    try = getch();
    if (try == '1') {
        px = 1, py = 1;
        goal = 3;
        flg = 0;
        res = 1;
        down = 1;
        tmp = 3;
        Map_Reset();
        goto RESET;
    }
    
    return 0;
}