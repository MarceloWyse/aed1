#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char* nome;
	int choice;
	int cont;
	char* tnome;
	char copia[50];
	char copia2[50];
	int tentativa;
	char aux[50];
	int posicao_remover;
	int i;

} Pessoa;

char* nometmp(void *pbuffer);
char* inserir(char* dest, char* orig);
void liberar(void* pbuffer);
int existe(void* pbuffer, char* nome, char* duvidoso);
char* remover(void* pbuffer, char* nome, char* remocao);

int main()
{
	setlocale(LC_ALL, "portuguese");
	void* pbuffer = malloc(sizeof(Pessoa));
	Pessoa* p;
	p = pbuffer;

	p->nome = (char*)malloc(sizeof(char) * 15);
	p->nome[0] = '\0';

	p->tnome = (char*)malloc(sizeof(char) * 15);
	p->tnome[0] = '\0';

	p->cont = 0;
	p->copia[0] = '\0';

	while(1)
	{
		printf("Menu: \n");
		printf("\tAdicionar pessoa:(1)\n");
		printf("\tRemover pessoa:(2)\n");
		printf("\tListar pessoas:(3)\n");
		printf("\tBuscar nome:(4)\n");
		printf("\tSair:(0)\n");
		printf("\nDigite a opção desejada: ");

		scanf("%d", &p->choice);

		if(p->choice == 1)
		{
			if(p->cont == 0)
			{
				printf("Qual nome deseja inserir? ");
				scanf("%s", p->nome);
			}
			else
			{
				printf("Qual nome deseja inserir?\n");
				scanf("%s", p->tnome);

				p->nome = (char*) realloc(p->nome, sizeof(char) * (strlen(p->nome) + strlen(p->tnome) + 2));
				p->nome = inserir(p->nome, p->tnome);
			}
			p->cont++;
			system("pause");
			system("cls");
		}

		else if(p->choice == 2)
		{
			if(p->cont == 0)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("Qual nome deseja remover? ");
				scanf("%s", p->tnome);

				p->tentativa = existe(pbuffer, p->nome, p->tnome);

				if(p->tentativa == 1)
				{
					p->nome = remover(pbuffer, p->nome, p->tnome);
					printf("Nome removido com sucesso\n");

				}
				else
				{
					printf("O nome %s não consta na lista!\n", p->tnome);
				}
			}

			system("pause");
			system("cls");
		}
		else if(p->choice == 3)
		{
			if(p->cont == 0)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("%s\n", p->nome);
			}

			system("pause");
			system("cls");
		}
		else if(p->choice == 4)
		{
			if(p->cont == 0)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("Qual nome deseja procurar? ");
				scanf("%s", p->tnome);

				p->tentativa = existe(pbuffer, p->nome, p->tnome);

				if(p->tentativa == 1)
				{
					printf("%s encontrado na lista!\n", p->tnome);

				}
				else
				{
					printf("O nome %s não consta na lista!\n", p->tnome);
				}
			}
			system("pause");
			system("cls");
		}

		else if(p->choice == 0)
		{
			printf("Saindo...\n");
			free(p->nome);
			free(p->tnome);
			free(pbuffer);
			system("pause");
			system("cls");
			break;
		}
		else
		{
			printf("Opção inválida. Tente novamente....\n");
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

int existe(void* pbuffer, char* nome, char* duvidoso)
{
	Pessoa* p;
	p = pbuffer;

	strcpy(p->copia, p->nome);

	char* s = (char*) malloc(sizeof(char));
	
	s = "-";
	
	char* token;

	token = strtok(p->copia, s);

	while(token != NULL)
	{
		if(strcmp(duvidoso, token) == 0)
		{
			return 1;
		}

		token = strtok(NULL, s);
	}

	free(s);
	return -1;
}


char* remover(void* pbuffer, char* nome, char* remocao)
{
	Pessoa* p;
	p = pbuffer;

	p->copia[0] = '\0';

	strcpy(p->copia, p->nome);

	p->aux[0] = '\0';

	char* token;

	char* s = (char*) malloc(sizeof(char));
	s = "-";

	//vou separar a string de acordo com traços
	//se tem joao-maria-jose, o primeiro token é joao, o segundo maria etc
	token = strtok(p->copia, s);

	p->posicao_remover = 1;

//primeiro loop pra descobrir em qual posição a string digitada está

	while(token != NULL)
	{
		if(strcmp(remocao, token) == 0)
		{
			break;
		}

		token = strtok(NULL, s);
		p->posicao_remover++;
	}

	p->copia2[0] = '\0';
	strcpy(p->copia2, p->nome);

	token = strtok(p->copia2, s);

	p->i = 1;

//agora eu remonto a string ignorando a posição que eu não quero
	while(token != NULL)
	{
		if(p->posicao_remover == p->i)
		{
			token = strtok(NULL, s); //pula pro próximo token
		}

		if(token == NULL) //se chegou no final
		{
			break;
		}
		strcat(p->aux, token);
		strcat(p->aux, "-");
		//essas duas linhas remontam a string

		token = strtok(NULL, s);
		p->i++;
	}

	p->nome = (char*) realloc(p->nome, sizeof(char) * (strlen(p->aux) + 2));

	strcpy(p->nome, p->aux); //no final copio a aux pro nome

	free(s);
	
	return p->nome; //e mando ela modificada pra main, lá ela se recebe e atualiza

}
