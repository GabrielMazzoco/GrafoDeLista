#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"

class Grafo
{
    public:
        Grafo();
        ~Grafo();

        int getN() { return n; }
        void insereNo(int i);
        void removeNo(int k);
        void addAresta(int a, int b, int peso);
        void removAresta(int a, int b);
        void imprimir();
        void imprimirArestas();
        int getGrauNo(int a);
        void gulosoCobertura();
        void diminuiuGrauNosAdjacentes(No* p, No **vetInd, int *vet);
        void algFloyd();
        void gulosoRandCobertura(float taxa, int vezes);
        int menorCaminhoDijkstra(int v, int vN);
        bool verificaVisit(bool vet[], int n);


    private:
        No *primeiro;
        No *ultimo;
        int n;

        No* busca(int i);
        bool existe(int i);
        void ordenaVetores(No** vetInd, int* vet);
};

#endif // GRAFO_H
