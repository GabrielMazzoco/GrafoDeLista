cmake_minimum_required(VERSION 3.12)
project(GrafoDeLista)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GrafoDeLista
        Aresta.h
        Grafo.cpp
        Grafo.h
        ListaAresta.cpp
        ListaAresta.h
        main.cpp
        No.h
        LeituraGrafos.cpp
        LeituraGrafos.h
        No.h
        NoPilha.h
        Pilha.cpp)
