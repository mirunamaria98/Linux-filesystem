//STOIAN MIRUNA MARIA
//315 CB
//Linux Filesystem
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "lista.h"

int main()
{

	int nr_comenzi;
	char comanda[20];
	Trie var = aloca();		//aloc arborele 
	char *token;
	char nume_director[100];
	char nume_director1[100];
	char nume_director2[100];
	char nume_fisier[100];
	char *s = "..";

	char cale[100];
	strcpy(cale, "/"); //initializez calea
	int i;

	scanf("%d", &nr_comenzi);	//citesc numarul de comenzi
	for (i = 0; i < nr_comenzi; i++) {
		scanf("%s", comanda);
		if (strcmp(comanda, "mkdir") == 0) {

			scanf("%[^\n]", nume_director);	//citesc pana la finalul randului
			token = strtok(nume_director, " \n");
			while (token != NULL) {

				//verific daca numele directorului incepe cu /
				if ((verifica_alfa(token) == 1	
				     && SearchDirector(&var, token + 1) != 1)
				    || (verifica_alfa(token) != 1
					&& SearchDirector(&var, token) != 1)) {
					char *p = strrchr(token, '/');	//caut ultima locatie a caracterului 

				//iau fiecare director in parte pentru a efectua operatiile
					if (p == NULL) {
						char aux[100];
						strcpy(aux, cale);
						strcat(aux, token);
						InsertDirector(&var, aux);
					} 
					else 
						if (p == token) {
						InsertDirector(&var, token + 1);
					} 
					else {
						char dir[100];
						strcpy(dir, token);

						int lung = strlen(dir) - 1;
						while (lung > 0
						       && dir[lung] != '/')
							lung--;
						dir[lung] = '\0';

						if ((verifica_alfa(dir) == 1
						     && SearchDirector(&var,
								       dir +
								       1) == 1)
						    || (verifica_alfa(dir) != 1
							&& SearchDirector(&var,
									  dir)
							== 1)) {
							InsertDirector(&var,
								       token);
						} 

						else {
							fprintf(stderr,
								"%s: No such file or directory\n",
								token);
						}
					}
				} 
				//verific existenta directorului 
				else {
					fprintf(stderr, "%s: already exists\n",
						nume_director + 1);
				}
				
				//preiau urmatorul director 
				token = strtok(NULL, " \n");
			}

		}
		if (strcmp(comanda, "cd") == 0) {
			scanf("%s", nume_director);	//citesc numele directorului
			if (strcmp(nume_director, s) != 0) {
				if (strcmp(nume_director, "../..") == 0) {
					int lung = strlen(cale);	//verific dimensiunea caii
					if (lung == 1) {
							//afisez mesajul de eroare
						fprintf(stderr,
							"../..: No such file or directory\n");
					} 
					else {
						lung -= 2;
						while (lung > 0
						       && cale[lung] != '/')
							lung--;
						cale[lung + 1] = '\0';
						//gasesc lunf=gimea caii si verific daca 
						//se poate efectua operatia
						lung = strlen(cale);
						if (lung == 1) {
							fprintf(stderr,
								"../..: No such file or directory\n");
						} 
						//se poate efectua operatia si modific calea
						else {
							lung =lung - 2;
							while (lung > 0
							       && cale[lung] !=
							       '/')
								lung--;
							cale[lung + 1] = '\0';
						}
					}
				} 
				else if (verifica_alfa(nume_director) == 1) {
					if (SearchDirector
					    (&var, nume_director + 1) == 1) {
						strcpy(cale, nume_director);	//adaug in cale locatia curenta
						strcat(cale, "/");				//daca directorul exista
					} 
					else {
						fprintf(stderr,	//afisez mesajul de eroare
							"%s: No such file or directory\n",
							nume_director);
					}
				} 
				else {
					char aux[100];
					strcpy(aux, cale);
					strcat(aux, nume_director);
						//verific existenta directorului si il adaug in cale
					if (SearchDirector(&var, aux) == 1) {
						strcat(cale, nume_director);
						strcat(cale, "/");
					} 
					else {
						fprintf(stderr,
							"%s: No such file or directory\n",
							nume_director);
					}
				}
			}
			 else {
				int lung = strlen(cale);
				if (lung == 1) 
				{	//verific daca se poate efectua operatia
					fprintf(stderr,
						"..: No such file or directory\n");
				} 
				else {
					lung = lung - 2;
					while (lung > 0 && cale[lung] != '/')
						lung--;
					cale[lung + 1] = '\0';

				}
			}
		}
		if (strcmp(comanda, "ls") == 0) {
			//apelez functia pentru a aprcurge si afisa fii directorului 
			List(var, cale);
		}
		if (strcmp(comanda, "pwd") == 0) {
			//afisez calea absoluta a directorului curent
			if (strlen(cale) == 1)
				printf("/\n");	
			else {
				char aux[100];
				strcpy(aux, cale);
				aux[strlen(aux) - 1] = '\0';
				fprintf(stdout, "%s\n", aux);
			}
		}
		if (strcmp(comanda, "mv") == 0) {
			//citesc pana la sfarsitul randului
			scanf("%[^\n]", nume_director);
			//delimitez pentru a efectua operatii cu fiecare
			//fisier 
			token = strtok(nume_director, " \n");
			int ok = 0;
			while (token != NULL) {
				strcpy(nume_director1, token);
				token = strtok(NULL, " \n");
				if (token == NULL) {
					//verific lipsa parametrilor
					fprintf(stderr,
						"%s %s: missing operand\n",
						comanda, nume_director1);
					ok = 1;

				}

				if (ok != 1) {
					strcpy(nume_director2, token);
					token = strtok(NULL, " \n");
					//verific existenta
					if (SearchFile(&var, nume_director2) ==
					    1) {
						fprintf(stderr,
							"%s: No such file or directory\n",
							nume_director2);
						ok = 1;
					}
					token = NULL;
				}
			}
			
			if (ok == 0) {
				//verific existenta 
				if (SearchFile(&var, nume_director1) != 1) {
					fprintf(stderr,
						"%s: No such file or directory\n",
						nume_director1);
				} else if (SearchDirector(&var, nume_director2)
					   != 1) {
					fprintf(stderr,
						"%s: No such file or directory\n",
						nume_director2);
				}
			}
			ok = 0;
		}
		if (strcmp(comanda, "touch") == 0) {
			//citesc pana la sfarsitul randului
			scanf("%[^\n]", nume_director); 
			//delimitez parametrii
			token = strtok(nume_director, " \n");
			while (token != NULL) {
				//verific existenta parametrilor 
				if (SearchFile(&var, token) != 1) {
					//adaug fisierele
					InsertFile(&var, token);
				}
				token = strtok(NULL, " \n");
			}

		}
		if (strcmp(comanda, "cp") == 0) {
			//cistesc pana la sfarsitul randului
			scanf("%[^\n]", nume_director);
			//delimitez parametrii
			token = strtok(nume_director, " \n");
			while (token != NULL) {
				strcpy(nume_fisier, token);
				token = strtok(NULL, " \n");
				strcpy(nume_director1, token);
				//verific existenta
				if (SearchDirector(&var, nume_director1) == 0) {
					fprintf(stderr,
						"%s: No such file or directory\n",
						nume_director1);
				}
				token = NULL;
			}
		}
	}
	FreeAll(var);
	return 0;

}
