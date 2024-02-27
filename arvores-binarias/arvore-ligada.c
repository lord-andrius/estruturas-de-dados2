#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct arvore {
	int dado;
	struct arvore *pai;
	struct arvore *filho_esquerda;
	struct arvore *filho_direita;
};

// cria ou adiciona elementos na árvore
// retorna 0 no sucesso
int adiciona_ou_cria_arvore(struct arvore **arvore, int dado) {
	if(*arvore == NULL) { // se o ponteiro é nulo temos que criar
		*arvore = (struct arvore *)malloc(sizeof(struct arvore)); // usando calloc para evitar ter que zerar os ponteiros!
		if(*arvore == NULL) {
			return 1;
		}
		(*arvore)->pai = NULL;
		(*arvore)->filho_esquerda = NULL;
		(*arvore)->filho_direita = NULL;
		(*arvore)->dado = dado;
		return 0;
	} else {
		struct arvore *pai = *arvore;
		struct arvore *a = *arvore;
		while(a) {
			pai = a;
			if(dado > a->dado) {
				a = a->filho_direita;
			} else {
				a = a->filho_esquerda;
			}
		}
			
		a = (struct arvore *)malloc(sizeof(struct arvore)); // usando calloc para evitar ter que zerar os ponteiros!
		if(a == NULL) {
			return 1;
		}
		a->pai = pai;
		a->filho_esquerda = NULL;
		a->filho_direita = NULL;
		a->dado = dado;
		if(dado > pai->dado) {
			pai->filho_direita = a;
		} else {
			pai->filho_esquerda = a;
		}
	}

	return 0;
}

void andar_em_ordem_crescente(struct arvore *arvore) {
	if(arvore != NULL) {
		andar_em_ordem_crescente(arvore->filho_esquerda);
		printf("%d\n", arvore->dado);
		andar_em_ordem_crescente(arvore->filho_direita);
	}
}

void panico(const char *msg) {
	puts(msg);
	exit(EXIT_FAILURE);
}
int main(void) {
	struct arvore *arvore = NULL;
	if(adiciona_ou_cria_arvore(&arvore, 8) != 0);
	if(adiciona_ou_cria_arvore(&arvore, 7) != 0);
	if(adiciona_ou_cria_arvore(&arvore, 9) != 0);
	assert(arvore->filho_esquerda->dado == 7);
	assert(arvore->filho_direita->dado == 9);
	andar_em_ordem_crescente(arvore);
	
	return 0;
}
