//STOIAN MIRUNA MARIA
//315 CB
//Linux Filesystem
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "lista.h"
#define MAX 40
Trie aloca(){
	//incerc alocarea
	Trie aux=(Trie)malloc(sizeof(TNod)); 

	if(!aux)	//verific alocarea
		return NULL;
	int i;
	//initializez toate campurilw
	aux->isDir = 0;
	aux->isFile = 0;
	aux->isStart = 0;
		for(i=0; i< MAX; i++)
	{
		aux->copii[i]=NULL;
	}

	return aux;
}

int GetContor(char c)
{
	//verific natura caracterului
	if(c >= 'a' && c <= 'z')
		return c-'a';
	if(c >= '0' && c <= '9')
		return 27 + (c - '0');
	if(c == '.')
		return 37;
	return 0;
}

char GetChar(int i)
{
	//verific natura variabilei
	if(i >= 0 && i <= 26)
		return i + 'a';
	if(i <= 36)
		return (i-27) + '0';
	return '.';
}
//inserez director
void InsertDirector(Trie *var, char *string){
	Trie aux= *var;	//construiesc o variabila auxiliara
	int contor, i = 0;
	while(*string)
	{
		if(*string != '/')
		{
			//initializez contorul
			contor=GetContor(*string);	//adaug in trie
			if(aux->copii[contor]== NULL){
				aux->copii[contor] = aloca();
				if(aux->copii[contor] ==  NULL )
					return;
			}
			aux=aux->copii[contor];
			if(i == 0)
				aux->isStart = 1;
			i++;
		}
		else
		{
			i = 0;
		}
		string++;
	}
	aux->isDir=1;	//setez ca director
}
//inserez fisier
void InsertFile(Trie *var, char *string){
	Trie aux= *var;
	int contor;
	while(*string)
	{
		//initializez contorul
		contor=GetContor(*string);
		if(aux->copii[contor]== NULL){
			aux->copii[contor] = aloca();	//adaug in trie
			if(aux->copii[contor] ==  NULL )
				return;
		}
		aux=aux->copii[contor];
		string++;
	}
	aux->isFile=1;	//setez ca fisier
}
//caut director
int SearchDirector(Trie *var, char *string){
	int contor;
	if(var == NULL)
		return 0;
	Trie aux = *var;	//initializez variabila auxiliara
	while(*string)
	{
		if(*string != '/')
		{
			//initializez contorul si caut directorul
			contor=GetContor(*string);
			aux=aux->copii[contor];
			if(aux == NULL )
				return 0;
		}
		string++;
	}
	//returnez 1 daca este gasit  si 0 altfel
	return aux->isDir;
}
//cauta fisier 
int SearchFile(Trie *var, char *string){
	int contor;
	if(var == NULL)
		return 0;
	Trie aux = *var;
	while(*string)
	{
		if(*string != '/')
		{
			//initializez contorul si caut fisierul
			contor=GetContor(*string);
			aux=aux->copii[contor];
			if(aux == NULL )
				return 0;
		}
		string++;
	}	
	//returnez 1 daca este gasit  si 0 altfel
	return aux->isFile;
}
//caut calea 
Trie CautaCale(Trie var, char *cale)
{
	Trie arb = var; //initializez variabila auxiliara
	int lung = strlen(cale), contor; 
	int i;
	for( i = 0; i < lung; i++)
	{
		if(cale[i] != '/')
		{
			//parcurg arborele
			contor=GetContor(cale[i]);
			arb = arb->copii[contor];
			if(arb == NULL)
				return NULL;
		}
	}

	return arb;
}
//afisare 
void PrintTrie(Trie arb, char *string, int nivel)
{
	//verific daca variabila este director sau fisier
	if(arb->isDir == 1) 
	{
		string[nivel] = '\0';
		printf("%s ", string);
	}
	if(arb->isFile == 1){
		string[nivel] = '\0';
		printf("%s ",string );
	}
	int i;
	for(i = 0; i < MAX; i++)
	{
		//daca exista si nu este inceput 
		if(arb->copii[i] && arb->copii[i]->isStart != 1)
		{
			//preiau caracterul si alezez recursiv 
			string[nivel] = GetChar(i);
			PrintTrie(arb->copii[i], string, nivel+1);
		}
	}
}

void List(Trie var, char *cale)
{
	Trie arb = CautaCale(var, cale);

	char string[100];
	int i;
	for( i = 0; i < MAX; i++)
	{
		//cat timp exista afisez fii
		if(arb->copii[i])
		{
			string[0] = GetChar(i);
			string[1] = '\0';

			PrintTrie(arb->copii[i], string, 1);
		}
	}

	printf("\n");
}
//verific daca parametrul incepe cu caracteru "/"
int verifica_alfa(char string[10]){
	if(string[0] == '/' )
		return 1;
	else return 0;
 }
//dezaloc memoria folosita recursiv 
void FreeAll(Trie var){
	if(!var)
		return;
	int i;
	for(i=0;i<MAX;i++)
		if(var->copii[i] != NULL)
			FreeAll(var->copii[i]);
	
	free(var);
}