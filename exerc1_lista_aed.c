#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "bib.h"

void criar_lista();
int comparar(char* novo_nome);
void inserir();
void remover();
void ler_string(char* nome);
void listar();
int livre();

int main()
{
	setlocale(LC_ALL, "portuguese");

	char escolha;
	criar_lista();

	do
	{
		printf("--Menu--\n");
		printf("\tInserir nome: Digite (1)\n");
		printf("\tRemover nome: Digite (2)\n");
		printf("\tListar nomes: Digite (3)\n");
		printf("\tSair: Digite (0)\n");
		printf("\nDigite a opção desejada: ");
		scanf("%c", &escolha);
		system("cls");
		
		switch(escolha)
		{
		case '1':
	
			inserir();
			system("pause");
			break;

		case '2':
			remover();
			system("pause");
			break;

		case '3':
			listar();
			system("pause");
			break;
		case '0':
			exit(1);
			break;
		}
	} while(escolha != 0);

	return 0;

}