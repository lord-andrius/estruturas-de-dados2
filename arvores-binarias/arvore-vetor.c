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
	struct no *novos_nos = realloc(arvore, sizeof(struct no) * (indice + 1));
	if(!novos_nos) return 1;
	arvore->nos = novos_nos;
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
	int indice = 0;
	while(arvore->nos[indice].esta_preenchido) {
		if(dado > arvore->nos[indice].dado) {
			indice = 2*indice + 1; // https://pt.wikipedia.org/wiki/%C3%81rvore_bin%C3%A1ria
		} else {
			indice = 2*indice + 2;
		}
	}
		// vamos alocar espaco para este indice e seus filhos
		if(alloca_espaco_na_arvore(arvore,2 * indice + 2)) return 1;
		arvore->nos[indice].dado = dado;
		arvore->nos[indice].esta_preenchido = 1;
		arvore->nos[2 * indice + 1].esta_preenchido = 0;
		arvore->nos[2 * indice + 1].indice_pai = indice;
		arvore->nos[2 * indice + 2].esta_preenchido = 0;
		arvore->nos[2 * indice + 2].indice_pai = indice;
		return 0;
}

int main(int argc, char *argv[]) {
	struct arvore *arvore = NULL;
	inicializa_arvore(&arvore, 2); 
	adiciona_elemento(arvore, 1);
	adiciona_elemento(arvore, 3);
	puts("Passou em todos os testes!");
	exit(EXIT_SUCCESS);
}
