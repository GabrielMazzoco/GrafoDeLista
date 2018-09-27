#include <iostream>
#include "Grafo/Grafo.h"
#include "Leitura/LeituraGrafos.h"

using namespace std;

int main()
{
    Grafo t;
    /*t.insereNo(1);
    t.insereNo(2);
    t.insereNo(3);
    t.insereNo(4);
    t.imprimir();
    t.addAresta(1, 2, 20);
    t.addAresta(1, 3, 15);
    t.addAresta(1, 4, 40);
    t.addAresta(2, 3, 80);
    //t.addAresta(3, 1, 50);
    t.imprimirArestas();
    cout << "Grau do no 1 : " << t.getGrauNo(1) << endl;
    t.removAresta(1, 4);
    t.removeNo(3);
    t.imprimirArestas();
    cout << "Grau do no 1 : " << t.getGrauNo(1) << endl;*/

    LeituraGrafos in;
    in.iniciaGrafo(&t);
    t.gulosoCobertura();

    /*t.addAresta(1, 2, 5);
    t.addAresta(1, 3, 5);
    t.addAresta(1, 4, 5);
    t.addAresta(1, 5, 5);
    t.addAresta(1, 7, 5);
    t.addAresta(5, 4, 5);
    t.addAresta(4, 2, 5);
    t.addAresta(3, 2, 5);
    t.addAresta(6, 2, 5);
    t.imprimirArestas();
    t.gulosoCobertura();*/

    return 0;
}
