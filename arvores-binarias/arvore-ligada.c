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
		*arvore = (struct arvore *)malloc(sizeof(struct arvore *)); // usando calloc para evitar ter que zerar os ponteiros!
		if(*arvore == NULL) {
			return 1;
		}
        (*arvore)->pai = NULL;
		(*arvore)->filho_esquerda = NULL;
		(*arvore)->filho_direita = NULL;
		(*arvore)->dado = dado;
		return 0;
	} 
    if(*arvore == NULL)

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
	for(int i = 8; i > 0; i--) {
		if(adiciona_ou_cria_arvore(&arvore, i) != 0);
	}
	for(int i = 9; i < 16; i++) {
	    if(adiciona_ou_cria_arvore(&arvore, i) != 0);
	}
	andar_em_ordem_crescente(arvore);
    printf("%d\n", arvore->filho_direita->dado);
	return 0;
}
