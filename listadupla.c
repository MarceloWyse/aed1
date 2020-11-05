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

typedef struct elemento Elem; //facilitar manipula��es nas implementa��es
//� um auxiliar, porque eu crio um Elem *no nas implementa��es
//e esse n� por ser um ponteiro de Elem, que � um elemento,
// pode receber as mesmas coisas que a lista, uma vez que a
//lista tamb�m � um ponteiro de elemento, que � minha struct com os dados e o n� anterior e posterior.

// (*no).ant ou no->ant , no->prox

Lista* cria_lista()
{
	Lista* li = (Lista*) malloc(sizeof(Lista)); //aloco espa�o pro ponteiro de ponteiro
	if(li != NULL) //se conseguir dar o malloc
	{
		*li = NULL; //conte�do recebe nulo
	}
	return li; //retorna o ponteiro de ponteiro, com conte�do nulo
}

void libera_lista(Lista* li) //passo a lista
{
	if(li != NULL) //s� posso liberar algo se existir uma lista
	{
		Elem* no; //crio um no auxiliar pra liberar o que ficar pra tras

		while(*li != NULL)
		{
			no = *li;
			*li = (*li)->prox; //*li vai pro proximo
			free(no); //libero o conte�do que estava em no
		} //repito isso at� *li = NULL

		free(li); //isso feito, libero o espa�o de li

	}

}

int tamanho_lista(Lista* li)
{
	if(li == NULL) return 0;

	int cont = 0;
	Elem* no = *li; //utilizo o auxiliar

	while(no != NULL) //percorre toda lista at� achar o ponteiro nulo
	{
		cont++; //adiciono 1 ao contador
		no = no->prox; //pula pro pr�ximo n�
	}

	return cont; //retorno a contagem de n�s n�o nulos, que � o tamanho da lista

}

int lista_cheia(Lista* li)
{
	return 0; //por se tratar de uma lista din�mica eu presumo que ela nunca esteja cheia, deve sempre retornar 0
}

int lista_vazia(Lista* li)
{
	if(li == NULL) return 1; //se for nula retorna verdadeiro, 1

	if(*li == NULL)
	{
		return 1; //se o conte�do de li for nulo retorna verdadeiro
	}

	return 0; //se n�o for nulo ela retorna 0
}

int insere_lista_inicio(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL) return 0; //n�o posso inserir se a lista n�o foi criada/alocada anteriormente

	Elem* no = (Elem*) malloc(sizeof(Elem)); //se passou do if eu tenho a lista, ent�o aloco um no auxiliar
	if(no == NULL) return 0; //deu erro ao alocar espa�o
	no->dados = p;
	no-> prox = *li; //esse no vai ter como seguinte o primeiro n� da lista, pq estou no come�o da lista
	no->ant = NULL; //o anterior � nulo porque n�o tem ningu�m antes dele

	if(*li != NULL) //se a lista n�o estava vazia
	{
		(*li)->ant = no; //o primeiro no da lista vai apontar para o n� que eu inseri
	}
	*li = no; //no final fa�o a substitui��o, o no passa a ser o primeiro elemento da lista
	
	return 1;
}

int insere_lista_final(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	
	if(li == NULL) return 0; //n�o posso inserir numa lista que n�o foi alocada

	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0; //erro na aloca��o do no
	no->dados = p; //copio os dados da minha struct
	no->prox = NULL; //porque n�o ter� nada depois dele

	if(*li == NULL) //se por acaso for o come�o da listaq
	{
		no->ant = NULL; //pq n�o tem nada antes dele
		*li = no; //primeiro elemento da lista passa a ser o elemento n�
	}
	else //se chegou aqui a lista n�o estava vazia, ent�o eu tenho que percorrer toda ela
	{
		Elem *aux = *li; //crio um auxiliar que vai receber o come�o da lista
		while(aux->prox != NULL) //enquanto n�o chegar no final da lista
		{
			aux = aux->prox; //n�o quero chegar no NULL, quero chegar no �ltimo elemento, que tem NULL como pr�ximo
		}
		//uma vez percorrida a lista
		aux->prox = no; //no lugar de NULL vou colocar o no, agora o n� � o �ltimo elemento.
		//Mas ainda tenho conectar o n� anterior no pen�ltimo elemento, ent�o:
		no->ant = aux; //o ponteiro do �ltimo n� para o pen�ltimo elemento que � o aux
	}
	return 1;

}

int insere_lista_meio(Lista* li, void* pbuffer)
{
	Pessoa* p;
	p = pbuffer;
	if(li == NULL) return 0; //lista nem existe, n�o posso alocar nada
	//if falhou, ent�o ela existe, posso colocar meu no.
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0; //deu erro ao alocar o n�

	no->dados = p; //se o no alocou memoria ele copia para si os dados de al

	if(*li == NULL) //caso a lista passada esteja vazia
	{

		no->prox = NULL;
		no->ant = NULL;
		*li = no;
		return 1;
	}
	else //n�o � uma lista vazia, vou ter que procurar onde inserir
	{
		Elem *anterior, *atual = *li; //crio dois n�s auxiliares, sendo que o atual recebe o come�o da lista
		while(atual != NULL && strcmp(atual->dados->nome, p->nome) < 0)
		{
			//percorro a lista enquanto o nome atual for menor que o nome passado, ou chegar no final da lista
			anterior = atual;
			atual = atual->prox;
		}
		if(atual == *li) //isso significa que nunca andei na lista, pois meu atual j� �ra o maior
		{
			//ent�o eu insiro no in�cio
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
	if(li == NULL) return 0; //se n�o tem lista, n�o posso remover
	if(*li == NULL) return 0; //se existe lista, mas ela est� vazia, n�o tem o que remover

	//sen�o:
	Elem* no = *li; //crio um no auxiliar que recebe o valor do primeiro n�
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
	if(li == NULL) return 0; //n�o tem lista
	if(*li == NULL) return 0; //a lista est� vazia

	Elem* no = *li; //crio um n� auxiliar pra remover o no que me foi passado

	while(no->prox != NULL) //vou conseguir chegar no �ltimo elemento e saio do loop
	{
		no = no-> prox;
	}
	//agora meu n� est� no �ltimo elemento
	if(no->ant == NULL) //se for isso, s� tem um elemento e a lista ficar� vazia
	{
		*li = no->prox; //*li receber� NULL, porque no est� no �ltimo elemento
	}
	else //se o n� n�o � o �nico elemento, tem mais um elemento na lista
	{
		no->ant->prox = NULL;
//o pen�ltimo elemento vai valer nulo, excluindo o no atual
	}
	free(no); //porque o n� foi excluido mas ainda est� alocado na mem�ria
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
	if(no == NULL) return 0; //n�o encontrou o nome
	if(no->ant == NULL) //ent�o estou removendo no in�cio
	{
		*li = no->prox; 
	}
	else
	{
		no->ant->prox = no->prox; //ent�o estou removendo no meio
	}
	if(no->prox != NULL) //testando se n�o � o �ltimo elemento
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
