#include <iostream>
#include "Grafo/Grafo.h"
#include "Leitura/LeituraGrafos.h"

using namespace std;

int main()
{
    Grafo t;

    LeituraGrafos in;
    in.iniciaGrafo(&t);
    t.gulosoCobertura();
    //t.algFloyd();
    t.gulosoRandCobertura(0.05, 100);

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
