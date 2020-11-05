#ifndef LISTADUPLA_H
#define LISTADUPLA_H

typedef struct
{
	int choice;
	int cont;
	char tnome[30];
	int i;

} Menu;

typedef struct
{
	char nome[30];

} Pessoa;


typedef struct elemento* Lista; //ponteiro do tipo elemento (que é uma struct) de nome Lista

//Funções da lista encadeada dupla:
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
int insere_lista_inicio(Lista* li, void* pbuffer);
int insere_lista_final(Lista* li, void* pbuffer);
int insere_lista_meio(Lista* li, void* pbuffer);
int remove_lista_inicio(Lista * li);
int remove_lista_final(Lista *li);
int remove_lista(Lista * li, char* nome);
int consulta_lista_pos(Lista* li, int pos, void* pbuffer);
int consulta_nome(Lista* li, char* nome, void* pbuffer);
//--------------------------------------------------------------

#endif