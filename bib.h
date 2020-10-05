#ifndef _BIB_H_
#define _BIB_H_
#define MAX 10

struct Pessoa
{
	char nome[100];

} p[MAX];

void criar_lista();
int comparar(char* novo_nome);
void inserir();
void remover();
void ler_string(char* nome);
void listar();
int livre();


void listar()
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

void remover()
{
	printf("Remover qual nome? ");
	char nome[100];
	getchar();
	ler_string(nome);
	
	
	int posicao = comparar(nome);
	
	if(posicao != -1)
	{
		p[posicao].nome[0] = '\0';
		printf("Nome removido com sucesso.\n");
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

int comparar(char* novo_nome)
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

void inserir()
{
	int posicao;
	char novo_nome[100];
	getchar();
	
	printf("Qual nome deseja inserir?\n");
	ler_string(novo_nome);
	
	
	posicao = livre();
	if(posicao == -1)
	{
		printf("Lista cheia\n");
		return;
	}
	
	
	int comp;
	comp = comparar(novo_nome);
	
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

void criar_lista()
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		p[i].nome[0] = '\0';
	}
}

int livre()
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		if(p[i].nome[0] == '\0')
			return i;
	}
	
	return -1;
	
}

#endif