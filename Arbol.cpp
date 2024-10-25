#include "Arbol.h"
#include <iostream>
#include <string>
#include <fstream>

Arboles::Arboles():root_1(nullptr), root_2(nullptr), size_1(0), size_2(0) {}


Arboles::~Arboles(){}

void Arboles::insertar_pelicula( Pelicula * pelicula ){
    Director* dir = buscar_director(pelicula->director);
        if (!dir) {
            dir = new Director();
            dir->set_nombre_director(pelicula->director);
            insertar_en_arbol(root_1, dir);
        }
        dir->agregar_pelicula(pelicula);
        dir->ordenar();
}

void Arboles::copiar_arbol(){}

Director * Arboles::buscar_director(){}

void Arboles::mejores_directores( int n ){}

void Arboles::peores_directores( int n ){}
