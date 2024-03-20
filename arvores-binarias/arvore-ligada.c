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

struct arvore *pegar_sucessor(struct arvore *arvore) {
	struct arvore *sucessor = arvore->filho_direita;
	while(sucessor->filho_esquerda != NULL) sucessor = sucessor->filho_esquerda;
	return sucessor;
}

void deletar_elemento(struct arvore *arvore, int dado) {
	struct arvore *no = pegar_elemento(arvore, dado);
	if(no == NULL) return;

	if(no->filho_esquerda == NULL && no->filho_direita == NULL) {
		if(no->pai->dado > dado) { // Quer dizer que o que eu estou tentando exclúir está na esquerda do pai
			no->pai->filho_esquerda = NULL;
			free(no);
		} else {
			no->pai->filho_direita = NULL;
			free(no);
		}
	} else if(no->filho_esquerda && no->filho_direita) {
		struct arvore *sucessor = pegar_sucessor(no);
		no->dado = sucessor->dado;
		//sucessor->pai->filho_esquerda = NULL;
		deletar_elemento(sucessor, sucessor->dado);
	} else if(no->filho_esquerda) {
		no->dado = no->filho_esquerda->dado;
		deletar_elemento(no->filho_esquerda, no->filho_esquerda->dado);
		no->filho_esquerda = NULL;
	} else if(no->filho_direita) {
		no->dado = no->filho_direita->dado;
		deletar_elemento(no->filho_direita, no->filho_direita->dado);
		no->filho_direita = NULL;
	}
}
int main(void) {
	int teste[] = {1,2,3,4,5,6,7,8};
	int teste2[] = {1,2};
	int teste3[] = {1,2,3,4,5};
	struct arvore *arvore4 = NULL;
	struct arvore *arvore5 = NULL;
	struct arvore *arvore6 = NULL;
	adiciona_elementos(&arvore4, teste, 8);
	adiciona_elementos(&arvore5, teste2, 2);
	adiciona_elementos(&arvore6, teste3, 5);
	mostrar(arvore4,0);
	deletar_elemento(arvore4, 2);
	puts("1==============================================================================");
	mostrar(arvore4,0);
	puts("2==============================================================================");
	mostrar(arvore5,0);
	deletar_elemento(arvore5, 1);
	puts("3==============================================================================");
	mostrar(arvore5,0);
	puts("4==============================================================================");
	mostrar(arvore6,0);
	deletar_elemento(arvore6, 3);
	puts("5==============================================================================");
	mostrar(arvore6,0);
	return 0;
}




