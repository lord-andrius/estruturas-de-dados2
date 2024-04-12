#ifndef GRAFO_LISTA_ADJASCENCIA
#define GRAFO_LISTA_ADJASCENCIA

struct Vertice {
	int dado;
	int qtd_adjascentes;
	struct Vertice **adjascentes;
};

struct Grafo {
	int numero_vertices;
	struct Vertice **vertices;
};

struct Grafo *cria_grafo(void);
void destroi_grafo(struct Grafo **);

struct Vertice *procura_vertice(struct Grafo *grafo,int dado);
struct Vertice *cria_vertice(struct Grafo *grafo, int dado);
int adiciona_conecao(struct Vertice *a, struct Vertice *b);
	
int adiciona_ou_modifica_grafo(struct Grafo *grafo, int dado, struct Vertice **conexoes, int qtd_conexoes);
#endif
