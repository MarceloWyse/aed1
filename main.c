#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h"
#include <string.h>
#include <locale.h>

int main()
{
	//------- Inicializa variáveis, cria a lista duplamente encadeada ----
	setlocale(LC_ALL, "portuguese");
	void* var = malloc(sizeof(Menu));
	Menu* menu;
	Pessoa* pessoa;
	void* pbuffer = malloc(sizeof(var) + sizeof(pessoa));
	menu = pbuffer;
	pessoa = pbuffer;
	menu->cont = 0;
	Lista *li; //crio um ponteiro para ponteiro, pois Lista já é um ponteiro
	li = cria_lista(); //recebe o ponteiro de ponteiro, aponta para o endereço do primeiro nó da lista

	// ------ Menu ---------
	while(1)
	{
		printf("Menu: \n");
		printf("\tAdicionar pessoa:(1)\n");
		printf("\tRemover pessoa:(2)\n");
		printf("\tListar pessoas:(3)\n");
		printf("\tBuscar nome:(4)\n");
		printf("\tSair:(0)\n");
		printf("\nDigite a opção desejada: ");

		scanf("%d", &menu->choice);

		if(menu->choice == 1)
		{
			if(menu->cont == 0)
			{
				printf("Qual nome deseja inserir? ");
				scanf("%s", menu->tnome);
				strcpy(pessoa->nome, menu->tnome);
				insere_lista_inicio(li, pessoa);
				
				printf("%d",consulta_nome(li, menu->tnome, &pessoa));
				system("pause");
				// pessoa++;
			}
			else
			{
				printf("Qual nome deseja inserir?\n");
				scanf("%s", pessoa->nome);

				printf("Em qual parte da lista deseja inserir? Inicio(1), Meio(2), Fim(3)\n");
				scanf("%d", &menu->choice);
				if(menu->choice == 1)
				{
					insere_lista_inicio(li, pessoa);
					pessoa++;
				}
				else if(menu->choice == 2)
				{
					insere_lista_meio(li, pessoa);
					pessoa++;
				}
				else if(menu-> choice == 3)
				{
					insere_lista_final(li, pessoa);
					pessoa++;
				}
				else
				{
					printf("Opção inválida, tente novamente!\n");
				}
			}

			menu->cont++;
		}

		else if(menu->choice == 2)
		{
			if(lista_vazia(li) == 1)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				printf("Qual nome deseja remover? ");
				scanf("%s", menu->tnome);

				printf("%d", remove_lista(li, menu->tnome));

				if(remove_lista(li, menu->tnome) == 1)

				{
					printf("Nome removido com sucesso!");
				}
				else
				{
					printf("Esse nome não consta na lista!\n");
				}
			}

		}
		else if(menu->choice == 3)
		{
			if(lista_vazia(li) == 1)
			{
				printf("A lista está vazia\n");
			}
		}
		else if(menu->choice == 4)
		{
			if(lista_vazia(li) == 1)
			{
				printf("A lista está vazia\n");
			}
			else
			{
				// printf("Qual nome deseja procurar? ");
				// 
				// scanf("%s", menu->tnome);
				
				if(consulta_nome(li, menu->tnome, &pessoa) == 1)
				{
					printf("O nome: %s consta na lista\n", menu->tnome);
				}
				else
				{
					printf("O nome %s não consta na lista\n", menu->tnome);
				}

			}
		}

		else if(menu->choice == 0)
		{
			printf("Saindo...\n");
			free(pbuffer);
			break;
		}
		else
		{
			printf("Opção inválida. Tente novamente....\n");
		}
	}

	return 0;
}


//Isso funciona perfeitamente:

// 	printf("Digite o nome: ");
// 	scanf("%s", menu->tnome);
// 	strcpy(pessoa->nome, menu->tnome);
// 	insere_lista_inicio(li, pessoa);
// 	printf("Qual nome deseja procurar? ");
// 	scanf("%s", menu->tnome);
// 	if(consulta_nome(li, menu->tnome, &pessoa) == 1)
// 	{
// 		printf("O nome: %s consta na lista\n", menu->tnome);
// 	}
// 	else
// 	{
// 		printf("O nome %s não consta na lista\n", menu->tnome);
// 	}
// 
// 	return 0;
// }
