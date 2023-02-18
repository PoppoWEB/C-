#ifndef SAVE
#define SAVE

#include "Hash.h"
#include <stdio.h>

FILE *fp;

void FInitial(List *n,int MAX);
void Save(List *n,char *name);
void Load(List *n,char *name);

#endif SAVE