#ifndef HASH_CLASS
#define HASH_CLASS

int MAX;

typedef struct _Node
{
    int val;
    char *name;
    struct _Node *next;
}Node;

typedef struct List
{
    Node **table;
}List;

int Hash(int n);
void Initialize(List *n);
Node *Make_Data(Node x);
void Add(List *n,Node *x,int r);
void Delete(List *n,Node *x);
void Print_Vec(List *n);
void Search(List *n,Node *x);
void Clear(List *n);

#endif