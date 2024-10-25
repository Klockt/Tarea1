#include "Director.h"
#include <iostream>
#include <string>
#include <fstream>

Director::Director(): head(nullptr), curr(nullptr), tail(nullptr), size(0), rating_promedio(0.0){}

void Director::agregar_pelicula( Pelicula * pelicula ){
        lNodo* nuevo_Nodo = new lNodo;
        nuevo_Nodo->val = pelicula;
        nuevo_Nodo->sig = nullptr;
        if (!head) {
            head = tail = nuevo_Nodo;
        }
        else {
            tail->sig = nuevo_Nodo;
            tail = nuevo_Nodo;
        }
        size++;
}

void Director::ordenar(){}

void Director::calcular_rating_promedio(){}

void Director::mostrar_peliculas(){}