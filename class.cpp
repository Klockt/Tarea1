#include "class.h"
#include <iostream>
#include <string>
#include <fstream>

/* Funciones clase Pedido */

//  Constructor Pedido
Pedido::Pedido() : platos(new Plato[25]), servir(true), cant_platos(0) {}

//  Destructor Pedido
Pedido::~Pedido() {
    delete[] platos;
}

//  Agrega un plato al pedido
void Pedido::agregar_plato(Plato* plato){
    if (cant_platos < 25) {
        platos[cant_platos++] = plato;
        } 
    else {
            cerr << "El pedido ya está completo." << endl;
    }
}


//  Retorna la suma del precio de todos los platos del pedido
int Pedido::precio_total(){
    int total = 0;
    for (size_t i = 0; i < cant_platos; i++) {
        total += platos[i].precio;
    }
    return total;
}

/* Funciones clase Registro */

//  Constructor Registro
Registro::Registro() : pedidos(new Pedido[100]), size(0), ganancias(0) {}

//  Destructor Registro
Registro::~Registro(){
    delete[] pedidos;
}

// Constructor por numero de mesas
void Registro::Ingreso_mesas(int numero_mesas){
    delete [] pedidos;
    pedidos = new Pedido[numero_mesas];
    size = 0;
}

//  Agrega un pedido al registro
void  Registro::agregar_pedido(Pedido* pedido){
    if (size < 100) {
        pedidos[size++] = *pedido;
        } else
        cerr << "El registro ya está completo." << endl;
}// EXPERIMENTANDO


//  Retorna el pedido segun id y tipo (servir True , llevar False)
Pedido* Registro::get_pedido(int id, bool tipo){
    for (size_t i = 0; i < size; i++) {
        // identificador del pedido
    }
    return nullptr;

}

//  Eliminia el pedido segun id y tipo
Pedido* Registro::eliminar_pedido(int id, bool tipo){
    for (size_t i = 0; i < size; i++) {
        // identificador del pedido
    }    
    return nullptr;

}