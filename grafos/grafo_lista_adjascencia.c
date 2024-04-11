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
		if(grafo->vertices[i].dado == dado) {
			vertice = grafo->vertices + i;
			break;
		}
	}

	return vertice;
}

struct Vertice *cria_vertice(struct Grafo *grafo, int dado) {
	struct Vertice *vertice = NULL;
	int pode_criar = 1;
	for(int i = 0; i < grafo->numero_vertices; i++) {
		if(grafo->vertices[i].dado == dado) {
			pode_criar = 0;
			break;
		}
	}
	
	if(pode_criar == 0) return NULL;

	vertice = calloc(1, sizeof(struct Vertice));

	return vertice;
}




int main(void) {
	puts("Olá, mundo!");
	exit(0);
}
