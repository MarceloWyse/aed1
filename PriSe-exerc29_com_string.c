#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

char* inserir(char* dest, char* orig);
int existe(char*, char* duvidoso);
char* remover(char* nome, char* remocao);

int main()
{
	char* nome = (char*) malloc(sizeof(char) * 20); 

	setlocale(LC_ALL, "portuguese");
	int choice = 0;
	int cont = 0;
	char nome2[20];
	nome2[0] = '\0';
	
	while(1)
	{

		printf("Menu: \n");
		printf("\tAdicionar nome:(1)\n");
		printf("\tRemover nome:(2)\n");
		printf("\tListar nomes:(3)\n");
		printf("\tSair:(0)\n");
		printf("\nDigite a opção desejada: ");

		scanf("%d", &choice);

		if(choice == 1)
		{
			
			if(cont == 0)
			{
				printf("Qual nome deseja inserir? ");
				scanf("%s", nome);
			}
			else
			{
				printf("Qual nome deseja inserir?\n");
				scanf("%s", nome2);
				
				nome = (char*) realloc(nome, sizeof(char) * (strlen(nome) + strlen(nome2) + 2));
				nome = inserir(nome, nome2);

			}
			cont++;
			system("pause");
			system("cls");
		}
		else if(choice == 2)
		{
			if(cont == 0)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("Qual nome deseja remover? ");
				scanf("%s", nome2);

				int tentativa = existe(nome, nome2);

				if(tentativa == 1)
				{
					nome = remover(nome, nome2);
					printf("Nome removido com sucesso\n");

				}
				else
				{
					printf("O nome %s não consta na lista!\n", nome2);
				}
			}
			system("pause");
			system("cls");
		}
		else if(choice == 3)
		{
			if(cont == 0)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("%s\n", nome);
			}

			system("pause");
			system("cls");
		}
		else if(choice == 0)
		{
			printf("Saindo...\n");
			free(nome);
			system("pause");
			system("cls");
			break;
		}
		else
		{
			printf("Opção inválida!\n");
			system("pause");
			system("cls");
		}

	}

	return 0;
}

char* inserir(char* dest, char* orig)
{
	char* origem = dest;

	while(*dest != '\0')
	{
		dest++;
	}
	*dest = '-';
	dest++;

	while(*orig != '\0')
	{
		*dest = *orig;
		dest++;
		orig++;
	}
	*dest = '\0';

	dest = origem;

	return dest;
}

int existe(char* nome, char* duvidoso)
{
	char copia[50];
	strcpy(copia, nome);

	char s[] = "-";
	char* token;

	token = strtok(copia, s);

	while(token != NULL)
	{
		if(strcmp(duvidoso, token) == 0)
		{
			return 1;
		}

		token = strtok(NULL, s);
	}

	return -1;
}

char* remover(char* nome, char* remocao)
{

	char copia[50];
	strcpy(copia, nome);

	char aux[50];
	aux[0] = '\0';

	char* token;
	char s[] = "-";
	
	//vou separar a string de acordo com traços
	//se tem joao-maria-jose, o primeiro token é joao, o segundo maria etc
	token = strtok(copia, s);

	int posicao_remover = 1; 
	
//primeiro loop pra descobrir em qual posição a string digitada está

	while(token != NULL)
	{
		if(strcmp(remocao, token) == 0)
		{
			break;
		}

		token = strtok(NULL, s);
		posicao_remover++;
	}

	char copia2[50];
	strcpy(copia2, nome);

	token = strtok(copia2, s);

	int i = 1;

//agora eu remonto a string ignorando a posição que eu não quero
	while(token != NULL)
	{
		if(posicao_remover == i)
		{
			token = strtok(NULL, s); //pula pro próximo token
		}
		
		if(token == NULL) //se chegou no final
		{
			break;
		}
		strcat(aux, token);
		strcat(aux, "-");
		//essas duas linhas remontam a string
		
		token = strtok(NULL, s);
		i++;
	}
	
	nome = (char*) realloc(nome, sizeof(char) * strlen(aux));
	
	strcpy(nome, aux); //no final copio a aux pro nome

	return nome; //e mando ela modificada pra main, lá ela se recebe e atualiza

}
