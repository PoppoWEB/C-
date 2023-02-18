#ifndef BASE
#define BASE

#include <Windows.h>

#define X     11
#define Y     11
#define OVER  -1
#define GOAL   0
#define NEXT   1
#define MAGICS 4
#define DATA   9
#define sleep(t) Sleep(t*1000)

int file_flg;

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

void init_mgi(mgi *m);
void init_ply(ply *p,int *px,int *py);
void init_emy(emy *e);

int Data_Load(void);
void Data_Save(ply p,int px,int py);

#endif