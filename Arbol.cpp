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
            dir->nombre_director(pelicula->director);
            if (!root_1) {
                root_1 = new aNodo{ dir, nullptr, nullptr };
                size_1++;
            } 
            else if (director->get_nombre_director() < nodo->val->get_nombre_director()) {
                insertar_en_arbol(nodo->izq, dir);
            }
            else {
                insertar_en_arbol(nodo->der, dir);
            }
    
        }
        dir->agregar_pelicula(pelicula);
        dir->ordenar();
}

void Arboles::copiar_arbol(){}

Director * Arboles::buscar_director( string director ){ //no entendi el arreglo de p
    return buscar_en_arbol(root_1, director);
}

Director* buscar_en_arbol(aNodo* nodo, const string& director) { //busqueda por recursividad
        
    }

void Arboles::mejores_directores( int n ){}

void Arboles::peores_directores( int n ){}
