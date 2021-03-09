//STOIAN MIRUNA MARIA
//315 CB
//Linux Filesystem
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 40

typedef struct nod_trie {
	int isDir, isFile;
	int isStart;
	struct nod_trie *copii[MAX]; 
}TNod,*Trie;

Trie aloca();
void InsertDirector(Trie *var, char *string);
void InsertFile(Trie *var, char *string);
int SearchDirector(Trie *var, char *string);
int SearchFile(Trie *var, char *string);
int verifica_alfa(char string[10]);
void FreeAll(Trie var);

Trie CautaCale(Trie var, char *cale);
void PrintTrie(Trie arb, char *string, int nivel);
void List(Trie var, char *cale);
