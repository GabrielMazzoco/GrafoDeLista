//
// Created by Gabriel on 9/22/2018.
//

#ifndef GRAFODELISTA_LEITURAGRAFOS_H
#define GRAFODELISTA_LEITURAGRAFOS_H
#include <fstream>
#include "Grafo/Grafo.h"

using namespace std;

class LeituraGrafos {
private:
    ifstream file;

public:
    void iniciaGrafo(Grafo *p, char *path);
    void iniciaGrafoPonderado(Grafo *p, char *path);
};


#endif //GRAFODELISTA_LEITURAGRAFOS_H
