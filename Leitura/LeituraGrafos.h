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
    ifstream f;

public:
    void iniciaGrafo(Grafo *p);
};


#endif //GRAFODELISTA_LEITURAGRAFOS_H
