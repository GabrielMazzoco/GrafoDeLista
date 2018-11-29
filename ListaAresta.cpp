#include "ListaAresta.h"
#include <iostream>
#include <cstdlib>

using namespace std;

ListaAresta::ListaAresta()
{
    primeiro = nullptr;
    ultimo = nullptr;
    n = 0;
}

ListaAresta::~ListaAresta()
{
    Aresta *p = primeiro;
    while(p != nullptr)
    {
        Aresta *t = p->getProx();
        delete p;
        p = t;
    }
}

/**
*Insere aresta deste no para o no indicado no parametro
*@param(int a, int peso)Id do no adjacente e seu respectivo peso
*@return: funcao sem retorno
*****************************************************************/
void ListaAresta::insereAresta(int a, int peso){
    Aresta *p = new Aresta();
    p->setV1(a);
    p->setPeso(peso);
    p->setProx(nullptr);
    n++;
    if(primeiro == nullptr){
        primeiro = p;
        ultimo = p;
    } else {
        ultimo->setProx(p);
        ultimo = p;
    }
}
/**
* Remove a aresta deste no para o no indicado no parâmetro
* @param(int k) Id do no k sobre o qual a aresta incide
* @return: funcao sem retorno
*
*****************************************************************/
void ListaAresta::removeAresta(int k){
    Aresta *p = primeiro;
    Aresta *q;
    if(p != nullptr){
        while(p != nullptr){
            if(p->getV1() == k){
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
    }/* else {
        cout << "Lista Vazia (ERRO) : REMOCAO ARESTA" << endl;
    }*/
}

/**
*Funcao que imprime a lista de aresta do No
*@param Nao possuiu parametros
*@return: funcao sem retorno
*****************************************************************/
void ListaAresta::imprimir(){
    Aresta* p = primeiro;
    while(p != nullptr){
        cout << p->getV1() << "   ";
        p = p->getProx();
    }
    cout << endl;
}

/**
*Funcao privada para buscar uma determinada aresta na lista
*@param(int i) Aresta que deseja ser encontrada
*@return: retorna um ponteiro para para Aresta se ela for encontrada
 * ou NULL caso contrario
*****************************************************************/
Aresta* ListaAresta::busca(int i){
    Aresta *p = primeiro;
    while(p != nullptr){
        if(p->getV1() == i)
            return p;
        p = p->getProx();
    }
    cout << "No nao encontrado. " << endl;
    return p;
}

/**
 * Funçao que varre a lista de arestas de um determinado No e guarda
 * os vertices que estao na lista
 * @return Retorna um vetor de inteiros com o ID dos vertices da lista
 * de arestas
 */
int *ListaAresta::getArestas() {
    int* vet = new int[n];
    Aresta* p = primeiro;
    for(int i=0 ; i<n ; i++){
        vet[i] = p->getV1();
        p = p->getProx();
    }
    return vet;
}

int ListaAresta::getPeso(int i) {
    Aresta *p = primeiro;
    while(p != nullptr){
        if(p->getV1() == i)
            return p->getPeso();
        p = p->getProx();
    }
    return 	2147483645;
}

Aresta *ListaAresta::getPrimeira() {
    return primeiro;
}

void ListaAresta::insereOrdenado(Aresta* a, int v)
{
    Aresta* p = new Aresta();
    p->setPeso(a->getPeso());
    p->setProx(a->getProx());
    p->setV1(a->getV1());
    p->setPai(v);
    if(n == 0){
        primeiro = p;
        ultimo = p;
        p->setProx(NULL);
        n++;
    }
    else{
        if(p->getPeso() <= primeiro->getPeso()){
            Aresta* q = primeiro;
            p->setProx(q);
            primeiro = p;
            n++;
        }
        else if(p->getPeso() > ultimo->getPeso()){
            ultimo->setProx(p);
            p->setProx(NULL);
            ultimo = p;
            n++;
        }
        else{
            Aresta* q = primeiro;
            while(q->getProx()->getPeso() < p->getPeso())
                    q = q->getProx();
            Aresta* c = q->getProx();
            q->setProx(p);
            p->setProx(c);
            n++;
        }
    }
}

void ListaAresta::removeK(Aresta* a)
{
    if(n == 0)
        cout << "Lista Vazia!!!" << endl;
    else{
        Aresta* p = primeiro;
        if(n == 1 && p == a){
            delete p;
            primeiro = NULL;
            ultimo = NULL;
            n--;
        }
        else if(p == a){
            primeiro = p->getProx();
            delete p;
            n--;
        }
        else{
            while(p != NULL){
                if(p->getProx() != NULL && p->getProx() == a){
                    if(p->getProx() == ultimo){
                        Aresta* q = p->getProx();
                        delete q;
                        p->setProx(NULL);
                        ultimo = p;
                        n--;
                    }
                    else{
                        Aresta* q = p->getProx();
                        p->setProx(q->getProx());
                        delete q;
                        n--;
                    }
                }
                p = p->getProx();
            }
        }
    }
}

bool ListaAresta::vazia()
{
    if(n == 0)
        return true;
    else return false;
}

