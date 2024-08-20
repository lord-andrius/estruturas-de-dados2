#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "grafo_lista_adjascencia.h"
#include "fila.h"



struct Grafo *cria_grafo(void) {
	struct Grafo *grafo = calloc(1, sizeof(struct Grafo));
	return grafo;	
}

void destroi_grafo(struct Grafo **grafo) {
	if(*grafo == NULL) return;

	for(int i = 0; i < (*grafo)->numero_vertices; i++){
		if((*grafo)->vertices[i] != NULL) {
			if((*grafo)->vertices[i]->adjascentes != NULL) {
				free((*grafo)->vertices[i]->adjascentes);
			}	
		}
	}

	free((*grafo)->vertices);
	free(*grafo);
	*grafo = NULL;
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
	vertice->dado = dado;
	vertice->cor = BRANCO;

	return vertice;
}

void buscar_por_conexoes(struct Vertice *vertice) {
	if(vertice->cor != BRANCO) return;

	vertice->cor = CINZA;
	for(int i = 0; i < vertice->qtd_adjascentes; i++) {
		buscar_por_conexoes(vertice->adjascentes[i]);
	}
	vertice->cor = PRETO;
}

void limpar_resultado_da_busca_de_conexoes(struct Grafo *grafo) {
	for(int i = 0; i < grafo->numero_vertices; i++) {
		grafo->vertices[i]->cor = BRANCO;
	}
}


void mostrar_conexoes(struct Grafo *grafo) {
	for(int i = 0; i < grafo->numero_vertices; i++) {
		if(grafo->vertices[i]->cor == PRETO) {
			printf("%d, ", grafo->vertices[i]->dado);
		}
	}
}




int adiciona_conecao(struct Vertice *a, struct Vertice *b) {
	assert(a != NULL);
	assert(b != NULL);
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

int adiciona_ou_modifica_grafo(struct Grafo *grafo, int dado, struct Vertice **conexoes, int qtd_conexoes) {
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
		if(conexoes[i] == NULL) continue;
		if(adiciona_conecao(vertice, conexoes[i])) return 1; // caso dê erro em alguma conexão
	}

	return 0;
	
}

void printa_grafo(struct Grafo *grafo) {
	for(int i = 0; i < grafo->numero_vertices; i++) {
		printf("%d: ", grafo->vertices[i]->dado);
		for(int i2 = 0; i2 < grafo->vertices[i]->qtd_adjascentes; i2++) {
			printf("%d ", grafo->vertices[i]->adjascentes[i2]->dado);
		}
		puts("");
	}
}

int deletar_vertice(struct Grafo *grafo, int dado) {
	assert(grafo != NULL);

	for(int i = 0; i < grafo->numero_vertices; i++){
		for(int i2 = 0; i2 < grafo->vertices[i]->qtd_adjascentes; i2++) {
			if(grafo->vertices[i]->adjascentes[i2]->dado == dado) {
				struct Vertice *tmp = grafo->vertices[i]->adjascentes[i2];


				grafo->vertices[i]->adjascentes[i2] = grafo->vertices[i]->adjascentes[grafo->vertices[i]->qtd_adjascentes - 1];

				grafo->vertices[i]->adjascentes[grafo->vertices[i]->qtd_adjascentes - 1] = tmp;
				grafo->vertices[i]->qtd_adjascentes -= 1;
				struct Vertice **novos_adjascentes = realloc(grafo->vertices[i]->adjascentes, grafo->vertices[i]->qtd_adjascentes * sizeof(struct Vertice **));
				if(!novos_adjascentes) return 1;
				grafo->vertices[i]->adjascentes = novos_adjascentes;
				if(grafo->vertices[i]->qtd_adjascentes == 0) grafo->vertices[i]->adjascentes = NULL;
			}

		}
		if(grafo->vertices[i]->dado == dado) {
			struct Vertice *tmp = grafo->vertices[i];
			grafo->vertices[i] = grafo->vertices[grafo->numero_vertices - 1];
			grafo->vertices[grafo->numero_vertices - 1] = tmp;
			grafo->numero_vertices--;
			struct Vertice **novos_vertices = realloc(grafo->vertices, grafo->numero_vertices * sizeof(struct Vertice **));
			if(!novos_vertices) return 1;
			grafo->vertices = novos_vertices;
			if(grafo->numero_vertices == 0) grafo->vertices = NULL;
		}
	} 

	return 0;

}


void menor_caminho(struct Fila *caminho, struct Vertice *origem, struct Vertice *destino) {
	if(origem->cor == CINZA) return;
	printf("DEBUG: origem: %d\n", origem->dado);
	adicionar_elemento(caminho, &origem->dado);
	origem->cor = CINZA;

	if(origem->dado == destino->dado || origem->qtd_adjascentes == 0) {
		origem->cor = BRANCO;
		return;
	}

	struct Fila **possiveis_caminhos = malloc(sizeof(caminho) * origem->qtd_adjascentes);
	if(possiveis_caminhos == NULL) {
		printf("Erro de alocação de memória!\n");
		exit(1);
	}

	for(int i = 0; i < origem->qtd_adjascentes; i++) {
		possiveis_caminhos[i] = criar_fila(sizeof(origem->dado));
		if(possiveis_caminhos == NULL) {
			printf("Erro de alocação de memória!\n");
			exit(1);
		}
		menor_caminho(possiveis_caminhos[i], origem->adjascentes[i], destino);
	}
	struct Fila *menor_caminho = NULL;
	for(int i = 0; i < origem->qtd_adjascentes; i++) {
		int chegou_ao_destino = 0;

		struct _Elemento *proximo = NULL;
		for (struct _Elemento *atual = possiveis_caminhos[i]->primeiro_elemento; atual != NULL; atual = proximo)
		{
			proximo = atual->proximo;
			int dado_do_vertice_atual = *(int *)atual->elemento;
			if(destino->dado == dado_do_vertice_atual) {
				chegou_ao_destino = 1;
				break;
			}
		}

		if(chegou_ao_destino) {
			if(menor_caminho == NULL) {
				menor_caminho =  possiveis_caminhos[i];
			} else {
				if(menor_caminho->quantidade_elementos > possiveis_caminhos[i]->quantidade_elementos) {
					menor_caminho =  possiveis_caminhos[i];
				}
			}
		}
	}

	struct _Elemento *proximo = NULL;
	for (struct _Elemento *atual = menor_caminho->primeiro_elemento; atual != NULL; atual = proximo)
	{
		proximo = atual->proximo;
		int dado_do_vertice_atual = *(int *)atual->elemento;
		adicionar_elemento(caminho, &dado_do_vertice_atual);
	}


	for(int i = 0; i < origem->qtd_adjascentes; i++) {
		deletar_fila(possiveis_caminhos + i);
	}
	free(possiveis_caminhos); 

	origem->cor = BRANCO;
	return;
}


int main(void) {
	struct Grafo *grafo = cria_grafo();

	assert(grafo != NULL);
	assert(grafo->numero_vertices == 0);
	assert(grafo->vertices == NULL);

	assert(adiciona_ou_modifica_grafo(grafo, 1, NULL, 0) == 0);
	assert(grafo->numero_vertices == 1);
	assert(grafo->vertices != NULL);
	assert(grafo->vertices[0]->dado == 1);


	//Testando se ele está impedindo de adicionar o mesmo número
	assert(adiciona_ou_modifica_grafo(grafo, 1, NULL, 0) == 0);
	assert(grafo->numero_vertices == 1);
	assert(grafo->vertices != NULL);
	assert(grafo->vertices[0]->dado == 1);
	assert(grafo->vertices[0]->qtd_adjascentes == 0);


	assert(adiciona_ou_modifica_grafo(grafo, 2, (struct Vertice *[]){procura_vertice(grafo, 1)}, 1) == 0);
	assert(grafo->numero_vertices == 2);
	assert(grafo->vertices[1]->dado == 2);
	assert(grafo->vertices[1]->qtd_adjascentes == 1);
	assert(grafo->vertices[0]->qtd_adjascentes == 1);
	assert(grafo->vertices[0]->adjascentes[0]->dado == 2);

	assert(adiciona_ou_modifica_grafo(grafo, 3, (struct Vertice *[]){procura_vertice(grafo, 1)}, 1) == 0);
	assert(grafo->numero_vertices == 3);
	assert(grafo->vertices[2]->dado == 3);
	assert(grafo->vertices[2]->qtd_adjascentes == 1);
	assert(grafo->vertices[0]->qtd_adjascentes == 2);
	assert(grafo->vertices[0]->adjascentes[1]->dado == 3);

	assert(adiciona_ou_modifica_grafo(
			grafo, 
			4, 
			(struct Vertice *[]){procura_vertice(grafo, 2), procura_vertice(grafo, 3), procura_vertice(grafo, 1)}, 3) == 0);
	/*
	assert(grafo->numero_vertices == 4);
	assert(grafo->vertices[3]->dado == 4);
	assert(grafo->vertices[3]->qtd_adjascentes == 2);
	assert(grafo->vertices[1]->qtd_adjascentes == 2);
	assert(grafo->vertices[2]->qtd_adjascentes == 2);
	assert(grafo->vertices[2]->adjascentes[1]->dado == 4);
	assert(grafo->vertices[1]->adjascentes[1]->dado == 4);
	assert(grafo->vertices[3]->adjascentes[0]->dado == 2);
	assert(grafo->vertices[3]->adjascentes[1]->dado == 3);
	*/
	printa_grafo(grafo);

	buscar_por_conexoes(grafo->vertices[0]);

	//mostrar_conexoes(grafo);

	struct Fila *fila = criar_fila(sizeof(int));
	menor_caminho(fila, grafo->vertices[0], grafo->vertices[3]);
	struct _Elemento *proximo = NULL;
	for (struct _Elemento *atual = fila->primeiro_elemento; atual != NULL; atual = proximo)
	{
		proximo = atual->proximo;
		int dado_do_vertice_atual = *(int *)atual->elemento;
		printf("%d ", dado_do_vertice_atual);
	}
	puts("");


	
	assert(!deletar_vertice(grafo, 4));
	
	puts("=====================================");
	printa_grafo(grafo);

	destroi_grafo(&grafo);
	exit(0);
}
