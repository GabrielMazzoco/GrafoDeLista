#ifndef LISTAARESTA_H
#define LISTAARESTA_H
#include "Aresta.h"


class ListaAresta
{
    public:
        ListaAresta();
        ~ListaAresta();
        void insereAresta(int a, int peso);
        void removeAresta(int k);
        void imprimir();
        int* getArestas();

    private:
        Aresta *primeiro;
        Aresta *ultimo;
        int n;

        Aresta* busca(int i);
};

#endif // LISTAARESTA_H
