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
    t.algFloyd();

    /*t.addAresta(1, 2, 95);
    t.addAresta(1, 3, 85);
    t.addAresta(1, 4, 75);
    t.addAresta(1, 5, 65);
    t.addAresta(1, 0, 55);
    t.addAresta(5, 4, 45);
    t.addAresta(4, 2, 35);
    t.addAresta(3, 2, 25);
    t.addAresta(6, 2, 15);
    t.imprimirArestas();
    t.gulosoCobertura();
    t.algFloyd();*/

    return 0;
}
