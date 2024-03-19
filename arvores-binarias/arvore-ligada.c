#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define COUNT 10

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
		
		if(adiciona_ou_cria_arvore(arvore, numeros[0]) != 0) return 1;
		return adiciona_ou_cria_arvore(arvore, numeros[1]);
	}else {
		size_t tamanho_metade = length / 2; // tambem é o indice do elemento da metade!
		if(adiciona_ou_cria_arvore(arvore, numeros[tamanho_metade]) != 0) return 1;
		if(adiciona_elementos(arvore, numeros, tamanho_metade) != 0) return 1;
		return adiciona_elementos(arvore, numeros + (tamanho_metade + 1), length - (tamanho_metade + 1));
	}
}

struct arvore *pegar_elemento(struct arvore *arvore, int dado) {
	if(arvore == NULL) {
		return NULL;
	} else if(arvore->dado == dado) {
		return arvore;
	} else if(arvore->dado < dado) {
		return pegar_elemento(arvore->filho_direita, dado);
	} else {
		return pegar_elemento(arvore->filho_esquerda, dado);
	}
}

void andar_em_ordem_crescente(struct arvore *arvore) {
	
	if(arvore != NULL) {
		andar_em_ordem_crescente(arvore->filho_esquerda);
		printf("%d\n", arvore->dado);
		andar_em_ordem_crescente(arvore->filho_direita);
	}
}

void mostrar(struct arvore *arvore, int space) {
		
	if(arvore == NULL) {
		return;
	}
	
	space += COUNT;
	
	mostrar(arvore->filho_direita, space);

	puts("");
 
	for(int i = COUNT; i < space; i++) printf(" ");

	printf("%d\n", arvore->dado);

	mostrar(arvore->filho_esquerda, space);
}

void panico(const char *msg) {
	puts(msg);
	exit(EXIT_FAILURE);
}

int main(void) {
	int impar[] = {1,2,3};
	int teste[] = {1,2,3,4,5,6,7,8};
	struct arvore *arvore4 = NULL;
	adiciona_elementos(&arvore4, teste, 8);
	//for(int i = 0; i < 8; i++) printf("%d\n", teste[i]);
	//printf("%d\n", arvore4->dado);
	//assert(arvore4->filho_esquerda->filho_direita->dado == 8);
	mostrar(arvore4,0);
	return 0;
}




