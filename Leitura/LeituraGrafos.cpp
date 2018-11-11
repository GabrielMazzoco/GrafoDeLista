//
// Created by Gabriel on 9/22/2018.
//

#include "LeituraGrafos.h"
#include "Grafo/Grafo.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/**
 *Le o arquivo de entrada e inicia o Grafo com seus nos e respectivas
 * arestas.
 * @param(Grafo *p) Ponteiro do Grafo
 * @return: Funcao sem retorno
 *****************************************************************/
void LeituraGrafos::iniciaGrafo(Grafo *p) {
    f.open("../Leitura/grafo_125.txt");
    if(!f.is_open())
        cout << "Erro ao abrir o Arquuivo." << endl;
    else{
        int a, b, peso;
        f >> a;
        cout << "Numeros de Nos : " << a << endl;
        while(!f.eof()){
            f >> a >> b >> peso;
            p->addAresta(a, b, peso);
        }
    }
}
