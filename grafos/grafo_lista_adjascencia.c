#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_adjascencia.h"


struct Grafo *cria_grafo(void) {
	struct Grafo *grafo = calloc(1, sizeof(struct Grafo));
	return grafo;	
}

struct Vertice *procura_vertice(struct Grafo *grafo,int dado) {
	struct Vertice *vertice = NULL;	
	for(int i = 0; i < grafo->numero_vertices; i++) {
		if(grafo->vertices[i]->dado == dado) {
			vertice = grafo->vertices[i];
			break;
		}
	}

	return vertice;
}

struct Vertice *cria_vertice(struct Grafo *grafo, int dado) {
	struct Vertice *vertice = NULL;
	int pode_criar = 1;
	for(int i = 0; i < grafo->numero_vertices; i++) {
		if(grafo->vertices[i]->dado == dado) {
			pode_criar = 0;
			break;
		}
	}
	
	if(pode_criar == 0) return NULL;

	vertice = calloc(1, sizeof(struct Vertice));

	return vertice;
}



int adiciona_conecao(struct Vertice *a, struct Vertice *b) {
	int pode_adicionar = 1;
	for(int i = 0; i < a->qtd_adjascentes; i++) {
		if(a->adjascentes[i]->dado == b->dado) {
			pode_adicionar = 0;
			break;
		}
	}

	// Se der algum bug por favor verifique se o a está em b :)
	
	if(pode_adicionar) {
		// melhor lidar com o realloc. No momento se houver uma falha na alocação vamos ter um vazamento de memória(Melhor o seu pc ter RAM!).
		a->adjascentes = realloc(a->adjascentes,sizeof(struct Vertice **) * (a->qtd_adjascentes + 1));
		if(a->adjascentes == NULL) return 1;
		b->adjascentes = realloc(b->adjascentes,sizeof(struct Vertice **) * (b->qtd_adjascentes + 1));
		if(b->adjascentes == NULL) return 1;
		a->adjascentes[a->qtd_adjascentes++] = b;
		b->adjascentes[b->qtd_adjascentes++] = a;
		return 0;
	} else {
		return 1;
	}
}

int adicona_ou_modifica_grafo(struct Grafo *grafo, int dado, struct Vertice *conexoes, int qtd_conexoes) {
	if(!grafo) return 1;

	struct Vertice *vertice = procura_vertice(grafo, dado);

	int deve_add = vertice == NULL;

	if(deve_add) {
		if((vertice = cria_vertice(grafo,dado)) == NULL) return 1;
		// melhor lidar com o realloc. No momento se houver uma falha na alocação vamos ter um vazamento de memória(Melhor o seu pc ter RAM!).
		grafo->vertices = realloc(grafo->vertices,sizeof(struct Vertice **) * (grafo->numero_vertices + 1));
		if(!grafo->vertices) return 1;
		grafo->vertices[grafo->numero_vertices++] = vertice;
	}


	for(int i = 0; i < qtd_conexoes; i++) {
		if(adiciona_conecao(vertice, conexoes + i)) return 1; // caso dê erro em alguma conexão
	}

	
}


int main(void) {
	puts("Olá, mundo!");
	exit(0);
}
