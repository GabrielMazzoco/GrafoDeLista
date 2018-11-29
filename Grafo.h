#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"

typedef struct grafoAux {
    int tam;
    int *vet;
} grafoAux;

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
        void algFloyd(int a, int b);
        grafoAux gulosoRandCobertura(float taxa, int vezes);
        void menorCaminhoDijkstra(int v, int vN);
        bool verificaVisit(bool vet[], int n);
        bool ehCompleto();
        void sequenciaGraus();
        grafoAux gulosoReativo(int k, int tamAlf);
        float Qi(float tamMelhorS, float somatorio, float qtd);
        float SomatorioQ(float *q, int tam);
        int RandomPseudoAleatorio(float * prob, int tamAlf);
        void kruskal();
        void bipartido();
        void buscaProfundidade(int v);



    private:
        No *primeiro;
        No *ultimo;
        int n;

        No* busca(int i);
        bool existe(int i);
        void ordenaVetores(No** vetInd, int* vet);
};

#endif // GRAFO_H
