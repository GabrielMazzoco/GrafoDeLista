#ifndef NO_H
#define NO_H
#include "ListaAresta.h"
#include <iostream>

using namespace std;

class No
{
    public:
        No() {lista = new ListaAresta; grau = 0; }
        ~No() {delete lista;}

        int getId() { return id; }
        int getGrau() { return grau; }
        No* getProx() { return prox; }
        void* setProx(No *p) { prox = p; }
        void addAresta(int a, int peso) { lista->insereAresta(a, peso); grau++; }
        void removAresta(int k) { lista->removeAresta(k); grau--; }
        void setId(int i) { id = i; }
        void imprimirArestas() { cout << "No " << id << " possui aresta com : ";  lista->imprimir(); }
        void zerarGrau() { grau = 0; }
        void diminuiu1Grau() { grau--; }
        int* getArestas() { return lista->getArestas(); }
        int getPeso(int i) { return lista->getPeso(i); }


    private:
        int id;
        int grau;
        No *prox;
        ListaAresta *lista;
};

#endif // NO_H
