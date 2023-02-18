#ifndef BATTLE
#define BATTLE

void Atk_Attack(emy *e, ply *p,int flg, int Def);
int Command_Mgi(mgi m);
void Mgi_Attack(mgi m,emy *e, ply *p,int res);
int UPS_DATA(void);
void LEVEL_UP(ply *p);
int battle_Set(emy *e,ply *p,mgi m);
int Battle(emy *e,ply *p,mgi m);

#endif