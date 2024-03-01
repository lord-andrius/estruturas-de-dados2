#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void bubble_sort(int numeros[], size_t length) {
	int troca;
	do {
		troca = 0;
		for(size_t i = 1; i < length; i++) {
			if(numeros[i - 1] > numeros[i]) {
				int tmp = numeros[i - 1];
				numeros[i - 1] = numeros[i];
				numeros[i] = tmp;
				troca = 1;
			}
		}
	} while(troca);
}

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

int adiciona_elementos(struct arvore **arvore, int numeros[], size_t length) {
	bubble_sort(numeros, length);
	if(length == 1) {
		return adiciona_ou_cria_arvore(arvore, numeros[0]);
	} else if(length == 2){
		if(adiciona_ou_cria_arvore(arvore, numeros[0] != 0)) return 1;
		return adiciona_ou_cria_arvore(arvore, numeros[1] != 0);

	} else if(length % 2 != 0) {
		size_t tamanho_metade = (length - 1) / 2; // tambem é o indice do elemento da metade!
		if(adiciona_ou_cria_arvore(arvore, numeros[tamanho_metade]) != 0) return 1;
		if(adiciona_elementos(arvore, numeros, tamanho_metade) != 0) return 1;
		return adiciona_elementos(arvore, numeros + tamanho_metade + 1, tamanho_metade);
	} else {
		size_t tamanho_metade = (length - 2) / 2; // nos números pares temos dois números no meio
		if(adiciona_ou_cria_arvore(arvore, numeros[tamanho_metade]) != 0) return 1;
		if(adiciona_ou_cria_arvore(arvore, numeros[tamanho_metade + 1]) != 0) return 1;
		if(adiciona_elementos(arvore, numeros, tamanho_metade) != 0) return 1;
		return adiciona_elementos(arvore, numeros + tamanho_metade + 2, tamanho_metade);
	}
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
	int par[] = {1,2,3,4};
	int impar[] = {1,2,3};
	struct arvore *arvore = NULL;
	if(adiciona_ou_cria_arvore(&arvore, 8) != 0);
	if(adiciona_ou_cria_arvore(&arvore, 7) != 0);
	if(adiciona_ou_cria_arvore(&arvore, 9) != 0);
	assert(arvore->filho_esquerda->dado == 7);
	assert(arvore->filho_direita->dado == 9);
	struct arvore *arvore2 = NULL;
	adiciona_elementos(&arvore2, par, 4);
	assert(arvore2->dado == 2);
	assert(arvore2->filho_esquerda->dado == 1);
	assert(arvore2->filho_direita->dado == 3);
	assert(arvore2->filho_direita->filho_direita->dado == 4);
	struct arvore *arvore3 = NULL;
	adiciona_elementos(&arvore3, impar, 3);
	assert(arvore3->dado == 2);
	assert(arvore3->filho_esquerda->dado == 1);
	assert(arvore3->filho_direita->dado == 3);
	puts("Passou nos testes!!");
	return 0;
}
