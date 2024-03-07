#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct no {
	int dado;
	int indice_pai;
	int esta_preenchido;
};

struct arvore {
	struct no *nos;	
	int tamanho;	
};

// Essa função aloca espaço suficiente para o 'indice' existir na árvore
int alloca_espaco_na_arvore(struct arvore *arvore, int indice) {
	if(indice + 1 < arvore->tamanho) { // serve para previnir que o realloc diminua o vetor
		return 0; 	
	}
	struct no *novos_nos = realloc(arvore->nos, sizeof(struct no) * (indice + 1));
	if(!novos_nos) return 1;
	arvore->nos = novos_nos;
	arvore->tamanho = indice + 1;
	return 0;
}

int inicializa_arvore(struct arvore **arvore, int dado) {
	*arvore = malloc(sizeof(struct arvore));
	if(!*arvore) return 1;
	(*arvore)->nos = calloc(3,sizeof(struct no));
	if(!(*arvore)->nos) return 1;
	(*arvore)->tamanho = 3;
	(*arvore)->nos[0].indice_pai = -1;
	(*arvore)->nos[0].dado = dado;
	(*arvore)->nos[0].esta_preenchido = 1;
	(*arvore)->nos[1].indice_pai = 0;
	(*arvore)->nos[2].indice_pai = 0;
	return 0;
}

int adiciona_elemento(struct arvore *arvore, int dado) {
	if(!arvore) return 1;
	int indice = 0;
	while(arvore->nos[indice].esta_preenchido) {
		if(dado < arvore->nos[indice].dado) {
			indice = 2*indice + 1; // https://pt.wikipedia.org/wiki/%C3%81rvore_bin%C3%A1ria
		} else {
			indice = 2*indice + 2;
		}
	}
		// vamos alocar espaco para este indice e seus filhos
		if(alloca_espaco_na_arvore(arvore,2 * indice + 2)) return 1;
		(arvore->tamanho)++;
		arvore->nos[indice].dado = dado;
		arvore->nos[indice].esta_preenchido = 1;
		arvore->nos[2 * indice + 1].esta_preenchido = 0;
		arvore->nos[2 * indice + 1].indice_pai = indice;
		arvore->nos[2 * indice + 2].esta_preenchido = 0;
		arvore->nos[2 * indice + 2].indice_pai = indice;
		return 0;
}

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

// Arredonda pra baixo
int adiciona_elementos(struct arvore *arvore, int numeros[], size_t length) {
	bubble_sort(numeros, length);
	if(length == 1) {
		return adiciona_elemento(arvore, numeros[0]);
	} else{
		size_t tamanho_metade = (length - 1) / 2; // tambem é o indice do elemento da metade!
		if(adiciona_elemento(arvore, numeros[tamanho_metade]) != 0) return 1;
		if(adiciona_elementos(arvore, numeros, tamanho_metade) != 0) return 1;
		return adiciona_elementos(arvore, numeros + tamanho_metade + 1, tamanho_metade);
	} 
}

int main(int argc, char *argv[]) {
	int teste[] = {1,2,4,5};
	struct arvore *arvore = NULL;
	inicializa_arvore(&arvore, 2); 
	adiciona_elemento(arvore, 1);
	adiciona_elemento(arvore, 3);
	adiciona_elemento(arvore, 0);
	adiciona_elemento(arvore, -1);
	adiciona_elemento(arvore, 4);
	assert(arvore->nos[0].dado == 2);
	assert(arvore->nos[0 * 2 + 1].dado == 1);
	assert(arvore->nos[0 * 2 + 2].dado == 3);
	assert(arvore->nos[1 * 2 + 1].dado == 0);
	assert(arvore->nos[3 * 2 + 1].dado == -1);
	struct arvore *arvore2 = NULL;
	inicializa_arvore(&arvore2, 3);
	adiciona_elementos(arvore2, teste, 4);
	assert(arvore2->nos[0].dado == 3);
	assert(arvore2->nos[0 * 2 + 1].dado == 2);
	assert(arvore2->nos[0 * 2 + 2].dado == 4);
	assert(arvore2->nos[1 * 2 + 1].dado == 1);
	assert(arvore2->nos[2 * 2 + 2].dado == 5);

	puts("Passou em todos os testes!");
	exit(EXIT_SUCCESS);
}
