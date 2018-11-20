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
void LeituraGrafos::iniciaGrafo(Grafo *p, char *path) {
    file.open(path);
    if(!file.is_open())
        cout << "Erro ao abrir o Arquuivo." << endl;
    else{
        int a, b, peso;
        file >> a;
        cout << "Numeros de Nos : " << a << endl;
        while(!file.eof()){
            file >> a >> b;
            p->addAresta(a, b, 0);
        }
    }
    file.close();
}

void LeituraGrafos::iniciaGrafoPonderado(Grafo *p, char *path) {
    file.open(path);
    if(!file.is_open())
        cout << "Erro ao abrir o Arquuivo." << endl;
    else{
        int a, b, peso;
        file >> a;
        cout << "Numeros de Nos : " << a << endl;
        while(!file.eof()){
            file >> a >> b >> peso;
            p->addAresta(a, b, peso);
        }
    }
    file.close();
}
