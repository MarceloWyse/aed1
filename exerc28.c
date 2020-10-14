#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
	char nome[30];
	int idade;
	int altura;
} Pessoa;

int main()
{
	setlocale(LC_ALL, "portuguese");
	Pessoa *p;
	
	int i = 0;
	int j = 1;
	char escolha;
	
	p = (Pessoa*) malloc(sizeof(Pessoa));
	
	while(1)
	{	
			
	printf("Digite o nome da pessoa: ");
	scanf("%s", p[i].nome);
	
	printf("\nDigite a idade: ");
	scanf("%d",&p[i].idade);
	
	printf("\nDigite a altura: ");
	scanf("%d", &p[i].altura);
	
	printf("\nDeseja adicionar mais nomes à lista (s/n)? ");
	getchar();
	scanf("%c",&escolha);
	
	if(escolha == 'n')
	{
		break;
	}
	else
	{
		printf("\nExpandindo a memória...\n");
		j = j + 1;
		i++;
		p = realloc(p, sizeof(Pessoa) * j);
	}
	
	
	}
	
	printf("\nListando pessoas:\n\n");
	int x; 
	for(x = 0; x <= i; x++)
	{
		printf("Nome: %s\n", p[x].nome);
		printf("Idade: %d\n",p[x].idade);
		printf("Altura: %d\n",p[x].altura);
		printf("-----------------\n");
	}
	
	free(p);
	
	return 0;
}
