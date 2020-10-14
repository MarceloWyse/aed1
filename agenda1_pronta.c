#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char* nome;
	int escolha;
	int i;
	char* tnome;

} Pessoa;

int getChoice(void* pbuffer);
void setChoice(void* pbuffer);
void setNome(void* pbuffer);
void listaNomes(void* pbuffer);
void criaLista(void* pbuffer);
int livre(void* pbuffer);
void busca(void* pbuffer);
void remover(void* pbuffer);

int main()
{
	setlocale(LC_ALL, "portuguese");
	void* pbuffer = malloc(sizeof(Pessoa) * 10);
	
	criaLista(pbuffer);
	
	while(1)
	{
		   	printf("Menu: \n");
		   	printf("\tAdicionar pessoa:(1)\n");
		   	printf("\tRemover pessoa:(2)\n");
		   	printf("\tListar pessoas:(3)\n");
		   	printf("\tBuscar nome:(4)\n");
		   	printf("\tSair:(0)\n");
		   	printf("\nDigite a opção desejada: ");
	 
			setChoice(pbuffer);
	
			if(getChoice(pbuffer) == 1)
			{
				printf("Qual nome deseja inserir?\n");
				setNome(pbuffer);
				system("pause");
				system("cls");
			}
	
			else if(getChoice(pbuffer) == 2)
			{
				remover(pbuffer);
				system("pause");
				system("cls");
			}
			else if(getChoice(pbuffer) == 3)
			{
				listaNomes(pbuffer);
				system("pause");
				system("cls");
			}
			else if(getChoice(pbuffer) == 4)
			{
				   busca(pbuffer);	
				   system("pause");
				   system("cls");
			}
			
			else if(getChoice(pbuffer) == 0)
			{
				printf("Saindo...\n");
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

int getChoice(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	return p->escolha;
}

void setChoice(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	scanf("%d",&p->escolha);
}

void setNome(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	scanf("%s", p[livre(pbuffer)].nome);
}

void criaLista(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	int i;
	for(i = 0; i < 10; i++)
	{
		p[i].nome = malloc(sizeof(char));
		p[i].nome[0] = '\0';	
	}
	
}

int livre(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
		
	for(p->i = 0; p->i < 10; p->i++)
	{
		   if(p[p->i].nome[0] == '\0')
		   {
		   	return p->i;
		   }	
	}
	
	return -1;
}

void busca(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	p->tnome = malloc(sizeof(char));
	
	printf("Qual nome deseja procurar?\n");
	scanf("%s",p->tnome);
	
	for(p->i = 0; p->i < 10; p->i++)
	{

		if(strcmp(p->tnome, p[p->i].nome) == 0)
		{
			printf("%s encontrado na lista!\n",p->tnome);
			free(p->tnome);
			break;
		}
		else if(p->i == 9)
		{
		printf("Nome não encontrado!\n");
		}
	}
	
	free(p->tnome);
}

void listaNomes(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	for(p->i = 0; p->i < 10; p->i++)
	{
		printf("%s\n",p[p->i].nome);
	}
}

void remover(void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	printf("Qual nome deseja remover?\n");
	
	p->tnome = malloc(sizeof(char));
	scanf("%s",p->tnome);
	
	for(p->i = 0; p->i < 10; p->i++)
	{
		if(strcmp(p->tnome, p[p->i].nome) == 0)
		{
			p[p->i].nome[0] = '\0';
			printf("Nome removido com sucesso, espaço liberado\n");
			free(p->tnome);
			break;
		}
		
		else if(p->i == 9)
		{
			printf("Esse nome não consta na lista\n");
			free(p->tnome);
		}
	}
}	
