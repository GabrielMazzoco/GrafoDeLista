#ifndef ARESTA_H
#define ARESTA_H


class Aresta
{
    public:
        Aresta() {}
        ~Aresta() {}

        Aresta* getProx() { return prox; }
        void setProx(Aresta *p) { prox = p; }
        void setV1(int v) { v1 = v; }
        void setPeso(int v) { peso = v; }
        int getV1()       { return v1; }
        int getPeso()       { return peso; }
        void setPai(int v) { pai = v; };
        int getPai() { return pai; };

    private:
        int pai;
        int v1;
        int peso;
        Aresta *prox;
};

#endif // ARESTA_H
