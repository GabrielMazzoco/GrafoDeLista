#include "Grafo.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <limits.h>
#include <fstream>

using namespace std;

Grafo::Grafo()
{
    //cout << "------------Criando Grafo------------" << endl;
    primeiro = nullptr;
    ultimo = nullptr;
    n = 0;
}

Grafo::~Grafo()
{
    No *p = primeiro;
    //cout << "------------Apagando Grafo------------" << endl;
    while(p != nullptr)
    {
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

/**
*Adiciona um vertice no grafo
*@param(int i) Id do vertice
*@return: funcao sem retorno
*****************************************************************/
void Grafo::insereNo(int i){
    No* p = new No();
    p->setId(i);
    p->setProx(nullptr);

    if(ultimo != nullptr) ultimo->setProx(p);
    ultimo = p;

    n++;

    if(n == 1) primeiro = p;
}

/**
*Remove o vertice do grafo
*@param(int k) Id do vertice a ser removido
*@return: funcao sem retorno
*****************************************************************/
void Grafo::removeNo(int k){
    No *p = primeiro;
    No *q;
    if(p != nullptr){
        while(p != nullptr){
            if(p->getId() == k){
                cout << "Removendo No : " << p->getId() << endl;
                if(p == primeiro){
                    if(primeiro == ultimo){
                        delete primeiro;
                        primeiro = nullptr;
                        ultimo = nullptr;
                        n--;
                    } else {
                        primeiro = primeiro->getProx();
                        delete p;
                        n--;
                    }
                } else {
                    q->setProx(p->getProx());
                    if(p == ultimo) ultimo = q;
                    delete p;
                    n--;
                }
            }
            q = p;
            p = p->getProx();
        }
        for(p = primeiro ; p != nullptr ; p=p->getProx()){
            p->removAresta(k);
        }
    } else {
        cout << "Grafo Vazio (ERRO) : REMOCAO VERTICE" << endl;
    }
}

/**
*Busca um vertice do grafo
*@param(int i) Id do vertice a ser encontrado
*@return: retorna um ponteiro para o vertice ou NULL se ele nao existir
*****************************************************************/
No* Grafo::busca(int i){
    No *p = primeiro;
    while(p != nullptr){
        if(p->getId() == i)
            return p;
        p = p->getProx();
    }
    return p;
}

/**
*Cria uma aresta nao direcionada entre os nos
*@param(int a, int b, int peso)Id dos nos e o peso da aresta
*@return: funcao sem retorno
*****************************************************************/
void Grafo::addAresta(int a, int b, int peso){
    if(!existe(a))
        insereNo(a);
    if(!existe(b))
        insereNo(b);
    No* p = busca(a);
    No* q = busca(b);
    p->addAresta(b, peso);
    q->addAresta(a, peso);
}

/**
*Remove uma Aresta entre os Vertices
*@param(int a, int b)Ids dos nos que possui aresta a ser removida
*@return; funcao sem retorno
*****************************************************************/
void Grafo::removAresta(int a, int b){
    No* p = busca(a);
    if(p != nullptr){
        p->removAresta(b);
    } else {
        cout << "Vertice Nao encontrado. " << endl;
    }
    p = busca(b);
    if(p != nullptr){
        p->removAresta(a);
    }
}

/**
*Imprime os vertices do Grafo
*@param Nao possui parametro
*@return: funcao sem retorno
*****************************************************************/
void Grafo::imprimir(){
    No* p = primeiro;
    cout << "Nos : ";
    while(p != nullptr){
        cout << p->getId() << "  ";
        p = p->getProx();
    }
    cout << endl;
}

/**
*Imprime todas as arestas dos vertices do grafo
*@param Nao possui parametro
*@return: funcao sem retorno
*****************************************************************/
void Grafo::imprimirArestas(){
    No* p = primeiro;
    while(p != nullptr){
        p->imprimirArestas();
        p = p->getProx();
    }
    cout << endl;
}

/**
*Calculo o grau de um determinado vertice
*@param(int a) Id do vertice desejado
*@return: retorna um inteiro com o grau do Vertice
*****************************************************************/
int Grafo::getGrauNo(int a){
    No* p = busca(a);
    return p->getGrau();
}

bool Grafo::existe(int i) {
    for(No* p = primeiro ; p != nullptr ; p = p->getProx()){
        if(p->getId() == i)
            return true;
    }
    return false;
}

/**
 * Algoritmo guloso para cobertura de Vértice que Inicia um vetor de Nos com
 * os Nos do grafo, e um vetor de int com seus respectivos graus, entao ordena
 * os vetores e enquanto a primeira posiçao for maior que 0, coloca o no da
 * posiçao 0 na soluçao zera seu grau, e diminuiu em 1 o grau dos Nos que
 * havia adjacencia.
 * @return Funçao sem retorno.
 */
void Grafo::gulosoCobertura() {
    No** vetInd = new No*[n];
    int vet[n];
    No* p = primeiro;
    for(int i=0 ; i<n ; i++){
        vetInd[i] = p;
        vet[i] = p->getGrau();
        p = p->getProx();
    }
    ordenaVetores(vetInd, vet);
    ofstream f;
    f.open("../Saidas.txt", ofstream::ios_base::app);
    f << endl << "Solução algoritmo guloso : " << endl;
    int numSolucao = 0;
    while(vet[0] > 0){
        numSolucao++;
        f << vetInd[0]->getId() << "   ";

        diminuiuGrauNosAdjacentes(vetInd[0], vetInd, vet);

        vet[0] = 0;
        ordenaVetores(vetInd, vet);
        if(numSolucao%20 == 0)
            f << endl;
    }
    cout << endl;
    cout << "Numero de nos na solucao Gulosa : " << numSolucao << endl;
    cout << endl;
    f << endl;
    delete [] vetInd;
}

/**
 * Algoritmo guloso Randomizado para cobertura de Vertice que inicia um vetor
 * de Nos com os Vertices do grafo, e um vetor de int com seus respectivos graus,
 * entao ordena os vetores simultaneamente e enquanto a primeira posicao for maior
 * que 0, pega um No aleatorio de acordo com a taxa e o coloca na solucao, zera seu
 * grau e diminuiu em 1 o grau dos Vertices adjacentes a ele.
 * @param taxa Valor Float entre 0 e 1 q determina o limite da aleatoriedade do
 * algoritmo
 * @param vezes Valor Int maior que 0 que determina quantas vezes sera repetido
 * o algoritmo
 */
void Grafo::gulosoRandCobertura(float taxa, int vezes) {
    if(taxa > 0 && taxa <= 1 && vezes > 0){
        int melhorSolucao = 2147483645;
        for(int j=0 ; j<vezes ; j++){
            No** vetInd = new No*[n];
            int vet[n];
            No* p = primeiro;
            for(int i=0 ; i<n ; i++){
                vetInd[i] = p;
                vet[i] = p->getGrau();
                //cout << vetInd[i]->getId() << "  " << vet[i] << endl;
                p = p->getProx();
            }
            ordenaVetores(vetInd, vet);
            //cout << "Solucao Cobertura de Vertice : " << endl;
            int numSolucao = 0;
            int qtdAtt = n;
            while(vet[0] > 0){
                numSolucao++;
                int pos = ceil(taxa * qtdAtt);
                pos = rand() % pos;
                //cout << vetInd[pos]->getId() << "   ";

                diminuiuGrauNosAdjacentes(vetInd[pos], vetInd, vet);

                vet[pos] = 0;
                qtdAtt--;
                ordenaVetores(vetInd, vet);
                //if(numSolucao%20 == 0)
                  //  cout << endl;
            }
            if(melhorSolucao > numSolucao)
                melhorSolucao = numSolucao;
            //cout << endl;
            //cout << "Numero de nos na solucao : " << numSolucao << endl;
            //cout << endl;
            delete [] vetInd;
        }
        cout << "Melhor Solucao do Randomizado : " << melhorSolucao << endl;
    } else {
        cout << "Quantidades Invalidas (ERRO)" << endl;
    }
}


/**
 * Funcao que ordena o vetor de de graus e juntamente ordena o vetor
 * de Nos para deixar o No e seu respectivo grau na mesma posiçao dos
 * vetores.
 * @param vetInd Ponteiro para o vetor de Nos
 * @param vet Ponteiro para o vetor de graus
 * @return Funçao sem retorno
 */
void Grafo::ordenaVetores(No **vetInd, int *vet) {
    int i , j , value;
    No* p;
    int gap = 1;
    while(gap < n) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < n; i++) {
            value = vet[i];
            p = vetInd[i];
            j = i - gap;
            while (j >= 0 && value > vet[j]) {
                vet [j + gap] = vet[j];
                vetInd[j + gap] = vetInd[j];
                j -= gap;
            }
            vet [j + gap] = value;
            vetInd[j + gap] = p;
        }
    }
}

/**
 * Funçao que diminuiu o grau dos nos adjacentes no vetor que armazena
 * o grau dos nos
 * @param p Ponteiro para o primeiro no do Vetor
 * @param vetInd Ponteiro para o vetor de Nos que formam o grafo
 * @param vet Ponteiro para o vetor que guarda o grau dos nos
 * @return Funçao sem retorno
 */
void Grafo::diminuiuGrauNosAdjacentes(No *p, No **vetInd, int *vet) {
    int* v = p->getArestas();
    int t = p->getGrau();
    for(int j=0 ; j<t ; j++){
        for(int i=0 ; i<n ; i++) {
            if (vetInd[i]->getId() == v[j]) {
                vet[i] = vet[i] - 1;
                break;
            }
        }
    }
    delete [] v;
}

/**
 * Faz uma matriz com a distancia minima entre todos os Vertices do
 * Grafo.
 * @return Funcao sem retorno
 */
void Grafo::algFloyd(int a, int b) {
    int mat[n][n];
    No *p;
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            if(i == j){ mat[i][j] = 0; }
            else{
                p = busca(i);
                mat[i][j] = p->getPeso(j);
            }
        }
    }
    for(int k=0 ; k<n ; k++){
        for(int i=0 ; i<n ; i++){
            for(int j=0 ; j<n ; j++){
                if(mat[i][j] > mat[i][k] + mat[k][j] && mat[i][k] + mat[k][j] > 0)
                    mat[i][j] = mat[i][k] + mat[k][j];
            }
        }
    }
    ofstream f;
    f.open("../Saidas.txt", ofstream::ios_base::app);
    if((a >= 0 && a < n) && (b >= 0 && b < n)){
        f << endl << "Menor Caminho entre " << a << " e " << b << " : " << mat[a][b] << endl;
    }
    else
        f << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
}

/**
* Algoritmo de Dijkstra para encontrar menor caminho entre dois vertices
* @param v int com o no inicial
* @param vN int com o no destino
* @return dist[vN] com a distancia entre os dois nos passados por parâmetro
*/
void Grafo::menorCaminhoDijkstra(int v, int vN)
{
    No* p = busca(v);
    No* q = busca(vN);
    ofstream f;
    f.open("../Saidas.txt", ofstream::ios_base::app);
    if(p != nullptr && q != nullptr){
        int menor;

        int dist[n], pre[n];
        bool visit[n];
        for(int i = 0; i < n; i++){
            dist[i] = INT_MAX/2;
            pre[i] = -1;
            visit[i] = false;
        }
        dist[p->getId()] = 0;

        while(!verificaVisit(visit, n)){
            if(!visit[p->getId()]){
                visit[p->getId()] = true;
                Aresta* a = p->getPrimeiraAresta();
                if(a != nullptr){
                    while(a != nullptr){
                        if(a->getPeso() >= 0)
                            if(dist[a->getV1()] > dist[p->getId()] + a->getPeso()){
                                dist[a->getV1()] = dist[p->getId()] + a->getPeso();
                                pre[a->getV1()] = p->getId();
                            }
                        a = a->getProx();
                    }
                }
                int i;
                for(i = 0; i < n; i++){
                    if(!visit[i])
                        break;
                    if(i == n-1){
                        //for(int j = 0; j < n; j++)
                            //cout << dist[j] << "\t";
                        cout << endl;
                        cout << "A distância entre " << v << " e " << vN << " e: " << dist[vN] << endl;
                        f << endl << "Menor Caminho entre " << v << " e " << vN << " : " << dist[vN] << endl;
                        //return dist[vN];
                    }
                }
                menor = i;
                for(i = menor+1; i < n; i++){
                    if(!visit[i] && dist[menor] > dist[i])
                        menor = i;
                }
                p = busca(menor);
            }
        }
        if(dist[vN] == INT_MAX/2) {
            cout << "Nao existe caminho entre os vertices." << endl;
            f << endl << "Nao existe caminho entre os vertices. " << endl;
            //return dist[vN];
        }
    }
    else{
        cout << "Vertice " << v << " ou "<< vN << " nao encontrados no grafo! (ERRO)" << endl;
        f << endl << "Vertice " << v << " ou "<< vN << " nao encontrados no grafo! (ERRO)-Algoritmo Dijkstra" << endl;
        //return -1;
    }
}

/**
* Função que verifica se o vetor é false em todas as posições
* @param vet bool com os indices dos nos do grafo
* @param n int com o tamanho do vetor
* @return false se todas as posicoes sao false ou true se encontrado ao menos um true
*/
bool Grafo::verificaVisit(bool vet[], int n) // funcao que verifica se todos os indicies do vetor foram visitados
{
    for(int i = 0; i < n; i++)
        if(!vet[i])
            return false;
    return true;
}

bool Grafo::ehCompleto() {
    No* p = primeiro;
    while(p != nullptr){
        if(p->getGrau() != n-1)
            return false;
        p = p->getProx();
    }
    return true;
}

void Grafo::sequenciaGraus() {
    No** vetInd = new No*[n];
    int vet[n];
    No* p = primeiro;
    for(int i=0 ; i<n ; i++){
        vetInd[i] = p;
        vet[i] = p->getGrau();
        p = p->getProx();
    }
    ordenaVetores(vetInd, vet);
    ofstream f;
    f.open("../Saidas.txt", ofstream::ios_base::app);
    f << endl << "Sequencia de Graus : " << endl;
    for(int i=0 ; i<n ; i++){
        f << vet[i] << "  ";
        if((i+1) % 20 == 0)
            f << endl;
    }
}
