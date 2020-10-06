#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int MAX = 2;

typedef struct
{
	char nome[100];

} Pessoa;

void criar_lista(Pessoa* p);
void inserir(Pessoa* p);
void remover(Pessoa* p);
int comparar(Pessoa* p, char* novo_nome);
void ler_string(char* nome);
void listar(Pessoa* p);
int livre(Pessoa* p);

int main()
{
	setlocale(LC_ALL, "portuguese");
	Pessoa* p;
	p = (Pessoa*) malloc(MAX * sizeof(Pessoa));
	
	char escolha;
	criar_lista(p);
	
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
			
			if(p[MAX - 1].nome[0] == '\0')
			{
				inserir(p);
				system("pause");
				break;
			}
			else
			{
				printf("Limite de memória excedida, expandindo\n");
				MAX = MAX + 2;
				p = (Pessoa*) realloc(p, MAX * sizeof(Pessoa));
				printf("Favor tentar novamente.\n");
				system("pause");
				break;   	
			}

		case '2':
			remover(p);
			system("pause");
			break;

		case '3':
			listar(p);
			system("pause");
			break;
		case '0':
			exit(1);
			break;
		}
	} while(escolha != 0);

	return 0;

}

//---------------------------------------
void listar(Pessoa* p)
{
	int i;
	
	for(i = 0; i < MAX; i++)
	{
		if(p[i].nome[0] != '\0')
		{
			printf("Registro: %d, Nome: %s\n", i + 1, p[i].nome);
		}
	}
}

void remover(Pessoa* p)
{
	printf("Remover qual nome? ");
	char nome[100];
	getchar();
	ler_string(nome);
	
	
	int posicao = comparar(p, nome);
	
	if(posicao != -1)
	{
		p[posicao].nome[0] = '\0';
		printf("Nome removido com sucesso.\n");
		p = (Pessoa*)realloc(p, ((MAX - 1) * sizeof(Pessoa)));
	}
	else
	{
		printf("%s não consta na lista.\n", nome);
		return;
	}
	
}

void ler_string(char* nome)
{

	char c;
	c = getchar();
	int i = 0;
	
	while(c != '\n')
	{
		nome[i] = c;
		c = getchar();
		i++;
	}
	nome[i] = '\0';
		
}

int comparar(Pessoa* p, char* novo_nome)
{
	
	int i;
	
	for(i = 0; i < MAX; i++)
	{
		if(p[i].nome[0] != '\0')
		{
			
		if(strcmp(p[i].nome, novo_nome) == 0)
		
		{
	
		return i;
		}
		
		}
	}
	
	return -1;
	
}

void inserir(Pessoa* p)
{
	int posicao;
	char novo_nome[100];
	getchar();
	
	printf("Qual nome deseja inserir?\n");
	ler_string(novo_nome);
	
	
	posicao = livre(p);
	if(posicao == -1)
	{
		printf("Lista cheia\n");
		return;
	}
	
	
	int comp;
	comp = comparar(p, novo_nome);
	
	if(comp != -1)
	{
		printf("Esse nome já existe na lista.\n");
		return;
	}
	else
	{
		strcpy(p[posicao].nome, novo_nome);
		printf("Nome inserido com sucesso.\n");
	}
	
	
}

void criar_lista(Pessoa* p)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		p[i].nome[0] = '\0';
	}
}

int livre(Pessoa* p)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		if(p[i].nome[0] == '\0')
			return i;
	}
	
	return -1;
	
}