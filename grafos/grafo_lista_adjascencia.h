#ifndef GRAFO_LISTA_ADJASCENCIA
#define GRAFO_LISTA_ADJASCENCIA

struct Vertice {
	int dado;
	struct Vertice **adjascentes;
};

struct Grafo {
	int numero_vertices;
	struct Vertice *vertices;
};

struct Grafo *cria_grafo(void);

struct Vertice *procura_vertice(struct Grafo *grafo,int dado);
struct Vertice *cria_vertice(struct Grafo *grafo, int dado);
#endif
