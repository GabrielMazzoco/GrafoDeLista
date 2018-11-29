#include <iostream>
#include <time.h>
#include <chrono>
#include "Grafo.h"
#include "LeituraGrafos.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[ ])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    if(argc == 1) {
        cout << "Faltam Argumentos" << endl;
        exit(1);
    }


    Grafo t;

    int x;
    cout << "Qual o tipo de Grafo : " << endl;
    cout << " 1 - Ponderado" << endl;
    cout << " 2 - Nao Ponderado" << endl;
    cin >> x;
    if(x == 1){
        LeituraGrafos in;
        in.iniciaGrafoPonderado(&t, argv[1]);
    }else if(x == 2){
        LeituraGrafos in;
        in.iniciaGrafo(&t, argv[1]);
    }

    int flag = 1000;
    while(flag != 0) {
        if(flag == 1) {
            t.gulosoCobertura();

        }
        else if(flag == 2){
            float alfa;
            int vezes;
            cout << "Digite o Alfa (Entre 0 e 1) : ";
            cin >> alfa;
            cout << "Digite quantidade de vezes : ";
            cin >> vezes;
            grafoAux aux = t.gulosoRandCobertura(alfa, vezes);
            cout << "Melhor Solução : " << aux.tam << endl;
            ofstream f;
            f.open("../Saidas.txt", ofstream::ios_base::app);
            f << endl << "Melhor soluçao Randomizado : " << endl;
            for(int i=0 ; i<aux.tam ; i++){
                f << aux.vet[i] << "   ";
                if((i+1) % 20 == 0)
                    f << endl;
            }
            f << endl;
            f.close();
        }
        else if(flag == 3){
            int l;
            l = 10; ///Espaçamento 0.05
            grafoAux aux = t.gulosoReativo(2000, l);
            cout << "Soluçao Reativo :" << aux.tam << endl;
            ofstream f;
            f.open("../Saidas.txt", ofstream::ios_base::app);
            f << endl << "Melhor soluçao Reativo : " << endl;
            for(int i=0 ; i<aux.tam ; i++){
                f << aux.vet[i] << "   ";
                if((i+1) % 20 == 0)
                    f << endl;
            }
            f << endl;
            f.close();

        }
        else if(flag == 4){
            int a, b;
            cout << "Digite o primeiro Vertice : ";
            cin >> a;
            cout << "Digite o segundo Vertice : ";
            cin >> b;
            t.algFloyd(a, b);
        }
        else if(flag == 5){
            int a, b;
            cout << "Digite o primeiro Vertice : ";
            cin >> a;
            cout << "Digite o segundo Vertice : ";
            cin >> b;
            t.menorCaminhoDijkstra(a, b);
        }
        else if(flag == 6){
            t.sequenciaGraus();
        }
        else if(flag == 7){
            int x;
            cout << "Id do Vertice : ";
            cin >> x;
            cout << "Grau : " << t.getGrauNo(x) << endl;
        }
        else if(flag == 8){
            if(t.ehCompleto())
                cout << "O grafo eh completo." << endl;
            else
                cout << "O grafo nao eh completo." << endl;
        }
        else if (flag == 9){
            t.bipartido();
        }
        else if(flag == 10){
            int x;
            cout << "Digite o vertice inicial: ";
            cin >> x;
            t.buscaProfundidade(x);
        }
        else if(flag == 11){
            t.kruskal();
        }
        //more options

        cout << endl;
        cout << "------------------ Selecione uma opcao ------------------" << endl;
        cout << " 1 - Algoritmo Guloso de Cobertura de Vertice" << endl;
        cout << " 2 - Algoritmo Guloso Randomizado " << endl;
        cout << " 3 - Algoritmo Guloso Reativo " << endl;
        cout << " 4 - Algoritmo de Floyd (Apenas para Grafos Ponderados)" << endl;
        cout << " 5 - Algoritmo de Dijkstra (Apenas para Grafos Ponderados)" << endl;
        cout << " 6 - Sequencia de Graus " << endl;
        cout << " 7 - Grau do Vertice " << endl;
        cout << " 8 - Eh Completo " << endl;
        cout << " 9 - Eh Bipartido " << endl;
        cout << " 10 - Busca em Profundidade " << endl;
        cout << " 11 - Algoritmo de Kruskal " << endl;
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


// FUNCAO UTILIZADA PARA CONTAGEM DE TEMPO
/*auto inicio = std::chrono::high_resolution_clock::now();

ALGORITMO A SER TESTADO

auto resultado = std::chrono::high_resolution_clock::now() - inicio;
long long seconds = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();
cout << seconds << endl;*/
