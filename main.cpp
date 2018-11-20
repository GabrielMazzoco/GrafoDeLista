#include <iostream>
#include <time.h>
#include <chrono>
#include "Grafo/Grafo.h"
#include "Leitura/LeituraGrafos.h"

using namespace std;

int main(int argc, char *argv[ ])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    if(argc == 1) {
        cout << "Faltam Argumentos" << endl;
        exit(1);
    }


    Grafo t;

    LeituraGrafos in;
    in.iniciaGrafo(&t, argv[1]);

    int flag = 1000;
    while(flag != 0) {
        if(flag == 1) {
            auto inicio = std::chrono::high_resolution_clock::now();
            t.gulosoCobertura();
            auto resultado = std::chrono::high_resolution_clock::now() - inicio;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
            cout << microseconds << endl;

        }
        else if(flag == 2){
            float alfa;
            int vezes;
            cout << "Digite o Alfa (Entre 0 e 1) : ";
            cin >> alfa;
            cout << "Digite quantidade de vezes : ";
            cin >> vezes;
            t.gulosoRandCobertura(alfa, vezes);
        }
        else if(flag == 3){
            int a, b;
            cout << "Digite o primeiro Vertice : ";
            cin >> a;
            cout << "Digite o segundo Vertice : ";
            cin >> b;
            t.algFloyd(a, b);
        }
        else if(flag == 4){
            int a, b;
            cout << "Digite o primeiro Vertice : ";
            cin >> a;
            cout << "Digite o segundo Vertice : ";
            cin >> b;
            t.menorCaminhoDijkstra(a, b);
        }
        else if(flag == 5){
            t.sequenciaGraus();
        }
        //more options

        cout << "------------- Selecione uma opcao -------------" << endl;
        cout << " 1 - Algoritmo Guloso de Cobertura de Vertice" << endl;
        cout << " 2 - Algoritmo Guloso Randomizado " << endl;
        cout << " 3 - Algoritmo de Floyd " << endl;
        cout << " 4 - Algoritmo de Dijkstra " << endl;
        cout << " 5 - Sequencia de Graus " << endl;
        cout << " 0 - Sair" << endl;
        cin >> flag;
    }

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
