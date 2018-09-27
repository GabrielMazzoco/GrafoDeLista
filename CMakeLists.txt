cmake_minimum_required(VERSION 3.12)
project(GrafoDeLista)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GrafoDeLista
        Grafo/Aresta.h
        Grafo/Grafo.cpp
        Grafo/Grafo.h
        Grafo/ListaAresta.cpp
        Grafo/ListaAresta.h
        main.cpp
        Grafo/No.h
        Leitura/LeituraGrafos.cpp
        Leitura/LeituraGrafos.h)
