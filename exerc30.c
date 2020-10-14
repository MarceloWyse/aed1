#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int** criaMatriz(int m, int n);
void leiaMatriz(int **mat, int m, int n);
void imprimeMatriz(int **mat, int m, int n);
int somaMatriz(int **mat, int m, int n);
int* colunaMatriz(int ** mat, int m, int n, int ncoluna);
void imprimeVetor(int *vet, int n);

int main()
{
	setlocale(LC_ALL, "portuguese");
	char choice;
	int cont = 0; //controle pra saber se eu criei uma matriz
	int** minhaMatriz;
	int lin;
	int col;
	int ncoluna;
	
	while(1)
	{
		printf("Menu: \n");
		printf("\tCriar/redimensionar a matriz: (1)\n");
		printf("\tLer um elemento da matriz: (2)\n");
		printf("\tSomar elementos da matriz: (3)\n");
		printf("\tRetornar elementos de uma coluna: (4)\n");
		printf("\tImprimir a matriz: (5)\n");
		printf("\tSair do programa: (0)\n");
		printf("\nDigite a opção desejada: ");

		fflush(stdin);
		scanf("%c", &choice);
		system("cls");

		if(choice == '1')
		{
			cont = cont + 1;

			printf("Quantas linhas? ");
			scanf("%d", &lin);

			printf("Quantas colunas? ");
			scanf("%d", &col);

			if(cont == 1) //só crio uma matriz se for a minha primeira vez
			{
				minhaMatriz = criaMatriz(lin, col);
			}

			else //senão eu realoco o espaço da matriz com os dados anteriores
			{
				minhaMatriz = (int**)realloc(minhaMatriz, sizeof(lin) * sizeof(col));

			}
			system("pause");
			system("cls");
		}
		else if(choice == '2')
		{
			if(cont != 0)
			{
				leiaMatriz(minhaMatriz, lin, col);
			}
			else
			{
				printf("Você deve primeiramente criar uma matriz.\n");
			}
			system("pause");
			system("cls");
		}
		else if(choice == '3')
		{
			if(cont != 0)
			{
				printf("Soma da matriz = %d\n", somaMatriz(minhaMatriz, lin, col));
			}
			else
			{
				printf("Você deve primeiramente criar uma matriz.\n");
			}

			system("pause");
			system("cls");
		}
		else if(choice == '4')
		{	
			if(cont != 0)
			{
			printf("Qual coluna deseja imprimir? ");
			scanf("%d",&ncoluna);
			
			printf("Imprimindo os elementos da coluna %d:\n", ncoluna);
			imprimeVetor(colunaMatriz(minhaMatriz,lin,col,ncoluna),lin);
			}
			else
			{
				printf("Você deve primeiramente criar uma matriz.\n");
			}
			system("pause");
			system("cls");
		}
		else if(choice == '5')
		{
			if(cont != 0)
			{
				printf("Sua matriz: \n");
				imprimeMatriz(minhaMatriz, lin, col);
			}
			else
			{
				printf("Você deve primeiramente criar uma matriz.\n");
			}
			system("pause");
			system("cls");
		}
		else if(choice == '0')
		{
			printf("Saindo do programa.\n");
			if(cont > 0) //evita que eu libere a matriz se eu não tiver criado uma anteriormente
			{
				free(minhaMatriz);
			}
			system("pause");
			system("cls");
			break;
		}

	}

	return 0;
}

int** criaMatriz(int m, int n)
{

	int** matriz;
	matriz = (int**) malloc(sizeof(int*) * m);

	int i;

	for(i = 0; i < m; i++)
	{
		matriz[i] = (int*) malloc(sizeof(int) * n);
	}

	return matriz;
}

void leiaMatriz(int **mat, int m, int n)
{
	int i, j;

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("Digite o elemento da linha %d, coluna %d: ", i + 1, j + 1);
			scanf("%d", &mat[i][j]);
		}
	}
}

void imprimeMatriz(int **mat, int m, int n)
{
	int i, j;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("[%d]", mat[i][j]);
		}
		printf("\n");
	}

}

int somaMatriz(int **mat, int m, int n)
{
	int i, j, soma = 0;

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			soma = soma + mat[i][j];
		}
	}

	return soma;
}

int* colunaMatriz(int ** mat, int m, int n, int ncoluna)
{
	int i, j;
	int* nvetor = (int*) malloc(sizeof(int) * m); //se ele tem 5 linhas, preciso de um vetor com 5 espaços
	int* origem;
	origem = nvetor; //pra não perder a origem de onde começa o nvetor
	
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if((j == (ncoluna - 1)))
			{
				   *nvetor = mat[i][j]; 
				   nvetor++;
			}
		}
	}
	
	nvetor = origem;
	
	return nvetor;	
	
}

void imprimeVetor(int *vet, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
	printf("[%d]\n",vet[i]);
	}
}