#include "listadupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct elemento
{
	struct elemento *ant;
	Pessoa* dados;
	struct elemento *prox;
}; //a lista duplamente encadeada

typedef struct elemento Elem; //facilitar manipulações nas implementações
//é um auxiliar, porque eu crio um Elem *no nas implementações
//e esse nó por ser um ponteiro de Elem, que é um elemento,
// pode receber as mesmas coisas que a lista, uma vez que a
//lista também é um ponteiro de elemento, que é minha struct com os dados e o nó anterior e posterior.

// (*no).ant ou no->ant , no->prox

Lista* cria_lista()
{
	Lista* li = (Lista*) malloc(sizeof(Lista)); //aloco espaço pro ponteiro de ponteiro
	if(li != NULL) //se conseguir dar o malloc
	{
		*li = NULL; //conteúdo recebe nulo
	}
	return li; //retorna o ponteiro de ponteiro, com conteúdo nulo
}

void libera_lista(Lista* li) //passo a lista
{
	if(li != NULL) //só posso liberar algo se existir uma lista
	{
		Elem* no; //crio um no auxiliar pra liberar o que ficar pra tras

		while(*li != NULL)
		{
			no = *li;
			*li = (*li)->prox; //*li vai pro proximo
			free(no); //libero o conteúdo que estava em no
		} //repito isso até *li = NULL

		free(li); //isso feito, libero o espaço de li

	}

}

int tamanho_lista(Lista* li)
{
	if(li == NULL) return 0;

	int cont = 0;
	Elem* no = *li; //utilizo o auxiliar

	while(no != NULL) //percorre toda lista até achar o ponteiro nulo
	{
		cont++; //adiciono 1 ao contador
		no = no->prox; //pula pro próximo nó
	}

	return cont; //retorno a contagem de nós não nulos, que é o tamanho da lista

}

int lista_cheia(Lista* li)
{
	return 0; //por se tratar de uma lista dinâmica eu presumo que ela nunca esteja cheia, deve sempre retornar 0
}

int lista_vazia(Lista* li)
{
	if(li == NULL) return 1; //se for nula retorna verdadeiro, 1

	if(*li == NULL)
	{
		return 1; //se o conteúdo de li for nulo retorna verdadeiro
	}

	return 0; //se não for nulo ela retorna 0
}

int insere_lista_inicio(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL) return 0; //não posso inserir se a lista não foi criada/alocada anteriormente

	Elem* no = (Elem*) malloc(sizeof(Elem)); //se passou do if eu tenho a lista, então aloco um no auxiliar
	if(no == NULL) return 0; //deu erro ao alocar espaço
	no->dados = p;
	no-> prox = *li; //esse no vai ter como seguinte o primeiro nó da lista, pq estou no começo da lista
	no->ant = NULL; //o anterior é nulo porque não tem ninguém antes dele

	if(*li != NULL) //se a lista não estava vazia
	{
		(*li)->ant = no; //o primeiro no da lista vai apontar para o nó que eu inseri
	}
	*li = no; //no final faço a substituição, o no passa a ser o primeiro elemento da lista
	
	return 1;
}

int insere_lista_final(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL) return 0; //não posso inserir numa lista que não foi alocada

	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0; //erro na alocação do no
	no->dados = p; //copio os dados da minha struct
	no->prox = NULL; //porque não terá nada depois dele

	if(*li == NULL) //se por acaso for o começo da listaq
	{
		no->ant = NULL; //pq não tem nada antes dele
		*li = no; //primeiro elemento da lista passa a ser o elemento nó
	}
	else //se chegou aqui a lista não estava vazia, então eu tenho que percorrer toda ela
	{
		Elem *aux = *li; //crio um auxiliar que vai receber o começo da lista
		while(aux->prox != NULL) //enquanto não chegar no final da lista
		{
			aux = aux->prox; //não quero chegar no NULL, quero chegar no último elemento, que tem NULL como próximo
		}
		//uma vez percorrida a lista
		aux->prox = no; //no lugar de NULL vou colocar o no, agora o nó é o último elemento.
		//Mas ainda tenho conectar o nó anterior no penúltimo elemento, então:
		no->ant = aux; //o ponteiro do último nó para o penúltimo elemento que é o aux
	}
	return 1;

}

int insere_lista_meio(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	if(li == NULL) return 0; //lista nem existe, não posso alocar nada
	//if falhou, então ela existe, posso colocar meu no.
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0; //deu erro ao alocar o nó

	no->dados = p; //se o no alocou memoria ele copia para si os dados de al

	if(*li == NULL) //caso a lista passada esteja vazia
	{

		no->prox = NULL;
		no->ant = NULL;
		*li = no;
		return 1;
	}
	else //não é uma lista vazia, vou ter que procurar onde inserir
	{
		Elem *anterior, *atual = *li; //crio dois nós auxiliares, sendo que o atual recebe o começo da lista
		while(atual != NULL && strcmp(atual->dados->nome, p->nome) < 0)
		{
			//percorro a lista enquanto o nome atual for menor que o nome passado, ou chegar no final da lista
			anterior = atual;
			atual = atual->prox;
		}
		if(atual == *li) //isso significa que nunca andei na lista, pois meu atual já éra o maior
		{
			//então eu insiro no início
			no->ant = NULL;
			(*li)->ant = no;
			no->prox = (*li);
			*li = no;
		}
		else
		{
			no->prox = anterior->prox;
			no->ant = anterior;
			anterior->prox = no;
			if(atual != NULL)
			{
				atual -> ant = no;
			}
		}

		return 1;
	}
}

int remove_lista_inicio(Lista * li)
{
	if(li == NULL) return 0; //se não tem lista, não posso remover
	if(*li == NULL) return 0; //se existe lista, mas ela está vazia, não tem o que remover

	//senão:
	Elem* no = *li; //crio um no auxiliar que recebe o valor do primeiro nó
	*li = no->prox;
	if(no->prox != NULL) //significa que tinha mais de um elemento na lista
	{
		no->prox->ant = NULL;
	}
	free(no);
	return 1;
}

int remove_lista_final(Lista * li)
{
	if(li == NULL) return 0; //não tem lista
	if(*li == NULL) return 0; //a lista está vazia

	Elem* no = *li; //crio um nó auxiliar pra remover o no que me foi passado

	while(no->prox != NULL) //vou conseguir chegar no último elemento e saio do loop
	{
		no = no-> prox;
	}
	//agora meu nó está no último elemento
	if(no->ant == NULL) //se for isso, só tem um elemento e a lista ficará vazia
	{
		*li = no->prox; //*li receberá NULL, porque no está no último elemento
	}
	else //se o nó não é o único elemento, tem mais um elemento na lista
	{
		no->ant->prox = NULL;
//o penúltimo elemento vai valer nulo, excluindo o no atual
	}
	free(no); //porque o nó foi excluido mas ainda está alocado na memória
	return 1;
}

int remove_lista(Lista * li, char* nome)
{
	if(li == NULL) return 0;
	Elem* no = *li;
	while(no != NULL && strcmp(no->dados->nome, nome) != 0)
	{
		no = no->prox; //percorre a lista

	}
	if(no == NULL) return 0; //não encontrou o nome
	if(no->ant == NULL) //então estou removendo no início
	{
		*li = no->prox; 
	}
	else
	{
		no->ant->prox = no->prox; //então estou removendo no meio
	}
	if(no->prox != NULL) //testando se não é o último elemento
	{
		no->prox->ant = no->ant;
	}
	free(no);
	return 1;

}

int consulta_lista_pos(Lista * li, int pos, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL || pos <= 0) return 0;
	Elem* no = *li;
	int i = 1;
	while(no != NULL && i < pos)
	{
		no = no->prox;
		i++;
	}
	if(no == NULL) return 0;
	else
	{
		p = no->dados;

		return 1;
	}
}

int consulta_nome(Lista* li, char* nome, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL) return 0;
	if(*li == NULL) return 0;
	Elem* no = *li;
	while(no != NULL && strcmp(nome, no->dados->nome) != 0)
	{
		no = no->prox;
	}
	if(no == NULL)
	{
		return 0;
	}
	else
	{
		p = no->dados;
		return 1;
	}
}
