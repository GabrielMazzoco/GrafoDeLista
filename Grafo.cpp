#include "Grafo.h"
#include "Pilha.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <limits.h>
#include <fstream>
#include <unistd.h>

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
    f.close();
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
grafoAux Grafo::gulosoRandCobertura(float taxa, int vezes) {
    grafoAux aux;
    if(taxa > 0 && taxa <= 1 && vezes > 0){
        int melhorSolucao = 2147483645;
        for(int j=0 ; j<vezes ; j++){
            No** vetInd = new No*[n];
            int *vet = new int [n];
            int *vetNos = new int [n];
            No* p = primeiro;
            for(int i=0 ; i<n ; i++){
                vetInd[i] = p;
                vet[i] = p->getGrau();
                p = p->getProx();
            }
            ordenaVetores(vetInd, vet);
            int numSolucao = 0;
            int qtdAtt = n;
            int cont = 0;
            while(vet[0] > 0){
                numSolucao++;
                int pos = ceil(taxa * qtdAtt);
                pos = rand() % pos;
                vetNos[cont] = vetInd[pos]->getId();
                cont++;

                diminuiuGrauNosAdjacentes(vetInd[pos], vetInd, vet);

                vet[pos] = 0;
                qtdAtt--;
                ordenaVetores(vetInd, vet);
            }
            if(melhorSolucao > numSolucao){
                melhorSolucao = numSolucao;
                aux.tam = numSolucao;
                aux.vet = vetNos;
            }
            delete [] vetInd;
        }
    } else {
        cout << "Quantidades Invalidas (ERRO)" << endl;
    }
    return aux;
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
        f << endl << "Menor Caminho(Floyd) entre " << a << " e " << b << " : " << mat[a][b] << endl;
        cout << endl << "Menor Caminho(Floyd) entre " << a << " e " << b << " : " << mat[a][b] << endl;
    }
    else {
        f << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
        cout << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
    }
    f.close();
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
                        f << endl << "Menor Caminho(Dijkstra) entre " << v << " e " << vN << " : " << dist[vN] << endl;
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
            cout << endl << "Nao existe caminho entre os vertices." << endl;
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

/**
 * Verifica se o Grafo eh completo
 * @return Retorna o valor logico encontrado
 */
bool Grafo::ehCompleto() {
    No* p = primeiro;
    while(p != nullptr){
        if(p->getGrau() != n-1)
            return false;
        p = p->getProx();
    }
    return true;
}

/**
 * Escreve no arquivo de saida a sequencia de graus do Grafo
 */
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
    f.close();
}

/**
 * Algoritmo guloso reativo que faz um vetor com alfas de 0.05 ate 0.5 e chama o randomizado
 * e faz outro vetor de probabilidades, atualizando as probabilidades de acordo com as melhores
 * solucoes geradas por cada alfa, fazendo com que os melhores alfas tenham maiores probabilidades
 * gerando solucoes melhores.
 * @param k Int de quantas iteracoes serao feitas
 * @param tamAlf Tamanho do vetor de alfas
 * @return Melhor Solucao Gerada
 */
grafoAux Grafo::gulosoReativo(int k, int tamAlf) {
    float *alfas = new float[tamAlf];
    float b = 0.05;
    int mat[2][tamAlf];//MATRIZ DE MEDIAS
    alfas[0] = 0.05;
    for (int a = 1; a < tamAlf; a++) alfas[a] = alfas[a - 1] + b;//VARIAÇÕES DE ALPFAS 0.1 ATÉ 0.5
    grafoAux *menor = new grafoAux[tamAlf];

    ////PRIMEIRA ITERAÇÃO = RANDOMIZADO
    menor[0] = gulosoRandCobertura(alfas[0], 1);
    mat[0][0] = menor[0].tam;
    mat[1][0] = 1;
    int melhor = menor[0].tam;
    for (int c = 1; c < tamAlf; c++) {
        menor[c] = gulosoRandCobertura(alfas[c], 1);//
        mat[0][c] = menor[c].tam;
        mat[1][c] = 1;
        if (menor[c].tam < melhor) melhor = menor[c].tam; //MELHOR SOLUCAO DA 1º ITERAÇÃO
    }
    float *Q = new float[tamAlf];
    for (int d = 0; d < tamAlf; d++)
        Q[d] = Qi(melhor, mat[0][d],
                  mat[1][d]);//cria o vetor de normalização e atualiza com os resultados da primeira iteração

    //VETOR PROBABILIDADE
    float sum = SomatorioQ(Q, tamAlf);
    float *P = new float[tamAlf];
    P[0] = (1000 * (Q[0] / (float) sum));//cria o vetor de probabilidade e o adequa ao padrão escolhido
    for (int i = 1; i < tamAlf; i++) {
        P[i] = P[i - 1] + (1000 * (Q[i] / (float) sum));
    }

    int i = 1;
    grafoAux s;
    grafoAux better = menor[0];
    int in;
    //srand((unsigned) time(NULL));
    while (i < k) {
        //cout << "i " << i << endl;
        in = RandomPseudoAleatorio(P, tamAlf);//  ESCOLHE UM ALFA ALEATORIO
        s = gulosoReativo(alfas[in], 1);
        if (menor[in].tam > s.tam) menor[in] = s;//atualiza menor solucao no vetor
        mat[0][in] = mat[0][in] + s.tam;//incrementa o somatorio das solucoes
        mat[1][in]++;//incremente o numero de vezes que um alfa foi radado
        if (s.tam < melhor) {
            melhor = s.tam;    //atualiza a melhor solucao
            better = s;
        }
        if (i % 10 == 0) //atualiza vetor de normalização e o vetor de probabilidade
        {
            for (int f = 0; f < tamAlf; f++) {
                Q[f] = Qi(melhor, mat[0][f], mat[1][f]);
            }
            sum = SomatorioQ(Q, tamAlf);
            P[0] = (1000 * (Q[0] / (float) sum));
            for (int g = 1; g < tamAlf; g++) {
                P[g] = (P[g - 1] + 1000 * (Q[g] / (float) sum));
            }
        }
        i++;
    }
    return better;
}
/**
    Calcula Qi na forma escolhida pelo grupo
*/
float Grafo::Qi(float tamMelhorS, float somatorio, float qtd)
{
    return ( ( (float)tamMelhorS)/ ( ((float)somatorio)/( (float)qtd )  ) );
}

/**
    função auxiliar para qualquer o somatorio de
    todos os elementos do vetor Q
*/
float Grafo::SomatorioQ(float *q, int tam)
{
    float somatorio =0;
    for(int i =0 ; i < tam ; i++) somatorio = somatorio + q[i] ;
    return somatorio;
}

/**
     o vetor de probabilidade foi montado de forma
     crescente de 0 a 1000 diminuindo a perda de precisão
*/
int Grafo::RandomPseudoAleatorio(float * prob, int tamAlf)
{
    //sleep(1);
    int x = rand() % 1000;
    for (int i=0; i< tamAlf; i++)
    {
        if( x < prob[i])
        {
            return i;
        }
    }
    return tamAlf-1;
}

/**
 * Faz uma arvore geradora minima ou se o grafo for conexo ou
 * faz florestas se o grafo for desconexo
 */
void Grafo::kruskal()
{
    if(n != 0){
        No* p = primeiro;
        int vetArv[n];
        bool visit[n];
        bool condicao[n];
        Aresta* a = p->getPrimeiraAresta();
        ListaAresta* lista = new ListaAresta();

        for(int i = 0; i < n; i++){
            vetArv[i] = p->getId();
            visit[i] = false;
            condicao[i] = false;
            p = p->getProx();
        }
        p = primeiro;

        while(p != NULL){
            while(a != NULL){
                if(!visit[a->getV1()])
                    lista->insereOrdenado(a, p->getId());
                a = a->getProx();
            }
            visit[p->getId()] = true;
            p = p->getProx();
            if(p != NULL)
                a = p->getPrimeiraAresta();
        }



//        lista->imprimeAresta();
        p = primeiro;
        a = lista->getPrimeira();
        int cont = 0;
        cout << "Arvore geradora: " << endl;
        while(!lista->vazia() && cont != n-1){
            if(condicao[lista->getPrimeira()->getPai()] && condicao[lista->getPrimeira()->getV1()])
                lista->removeK(lista->getPrimeira());
            else{
                if(lista->getPrimeira()->getPai() > lista->getPrimeira()->getV1()){
                    cout << "Aresta de " << lista->getPrimeira()->getPai() << " para " << lista->getPrimeira()->getV1() << " peso: " << lista->getPrimeira()->getPeso() << endl;
                    condicao[lista->getPrimeira()->getPai()] = true;
                    lista->removeK(lista->getPrimeira());
                    cont++;
                }
                else{
                    cout << "Aresta de " << lista->getPrimeira()->getPai() << " para " << lista->getPrimeira()->getV1() << " peso: " << lista->getPrimeira()->getPeso() << endl;
                    condicao[lista->getPrimeira()->getV1()] = true;
                    lista->removeK(lista->getPrimeira());
                    cont++;
                }
            }

        }
        if(lista->vazia() && cont != n-1)
                    cout << "Grafo desconexo" << endl;
        cout << "Numero de aresta na solucao: " << cont << endl;
        cout << "Numero de vertices: " << cont+1 << endl;


        delete lista;
    }
}

/**
 * Verifica se o grafo eh bipartido
 */
void Grafo::bipartido()
{
    if(n != 0){
        No* p = primeiro;
        bool visit[n];
        int color[n]; // particao a = 0 / particao b = 1
        for(int i = 0; i < n; i++){
            visit[i] = false;
            color[i] = -1;
        }
        Pilha pilha;
        int cont = 0;
        int status = 0;
        pilha.empilha(p->getId());
        cont++;
        visit[p->getId()] = true;
        color[p->getId()] = 0;

        Aresta* a;
        while(!pilha.vazia()){
            a = p->getPrimeiraAresta();
            while(a != NULL){
                if(!visit[a->getV1()]){
                    visit[a->getV1()] = true;
                    cont++;
                    if(color[a->getV1()] == -1){
                        if(color[p->getId()] == 0){
                            color[a->getV1()] = 1;
                            pilha.empilha(a->getV1());
                            p = busca(pilha.getTopo());
                            a = p->getPrimeiraAresta();
                        }
                        else{
                            color[a->getV1()] = 0;
                            pilha.empilha(a->getV1());
                            p = busca(pilha.getTopo());
                            a = p->getPrimeiraAresta();
                        }
                    }
                    else{
                        if(color[p->getId()] == 0){
                            if(color[a->getV1()] == 0){
                                status = -1;
                                break;
                            }
                            else{
                                pilha.empilha(a->getV1());
                                p = busca(pilha.getTopo());
                                a = p->getPrimeiraAresta();
                            }
                        }
                        else{
                            if(color[a->getV1()] == 1){
                                status = -1;
                                break;
                            }
                            else{
                                pilha.empilha(a->getV1());
                                p = busca(pilha.getTopo());
                                a = p->getPrimeiraAresta();
                            }
                        }
                    }
                }else{
                    if(color[p->getId()] != color[a->getV1()])
                        a = a->getProx();
                    else {
                        status = -1;
                        break;
                    }
                }
            }
            pilha.desempilha();
            p = busca(pilha.getTopo());
        }
        if(status == 0)
            cout << "Grafo admite biparticao" << endl;
        else cout << "Grafo nao admite biparticao!!" << endl;
    }
}

/**
 * Faz uma busca em profundidade para ver se o grafo eh conexo
 * @param v Vertice inicial
 */
void Grafo::buscaProfundidade(int v)
{
    No* p = busca(v);
    if(p != NULL){
        bool visit[n];
        int cont = 0;
        for(int i = 0; i < n; i++)
            visit[i] = false;

        Pilha pilha;
        pilha.empilha(p->getId());

        visit[p->getId()] = true;
        cont++;

        Aresta* a;
        while(!pilha.vazia()){
            a = p->getPrimeiraAresta();
            while(a != NULL){
                if(!visit[a->getV1()]){
                    visit[a->getV1()] = true;
                    cont++;
                    //cout << "\t " << a->getV1();
                    pilha.empilha(a->getV1());
                    p = busca(pilha.getTopo());
                    a = p->getPrimeiraAresta();
                }else{
                    a = a->getProx();
                }
            }
            pilha.desempilha();
            p = busca(pilha.getTopo());
        }
    if(cont == n){
        cout << endl <<  "Grafo conexo!!!" << endl;
    }
    else cout << "Grafo desconexo!!!" << endl;
    }
}
