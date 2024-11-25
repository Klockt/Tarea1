#include "class.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* Funciones clase Pedido */

string Pedido::get_nombre(int i) {
    if (platos[i].nombre=="") {
        cout << "aweonao" << endl;
        return "";

    } else {
        cerr << "Índice fuera de rango: " << i << endl;
        return "";
    }
}

int Pedido::get_cant_platos() {
    return cant_platos;
}

void Pedido::set_id(int valor){
    id_pedido = valor;
}

void Pedido::set_servir(bool tipo){
    servir = tipo;
}

int Pedido::get_id(){ return id_pedido;}

bool Pedido::get_servir(){ return servir;}


//  Constructor Pedido
Pedido::Pedido() : platos(new Plato[25]), servir(true), cant_platos(0) {} // 25 platos maximos

//  Destructor Pedido
Pedido::~Pedido() {
    delete[] platos;
}

void Pedido::set_cant_platos(){
    cant_platos++;
}

//  Agrega un plato al pedido
void Pedido::agregar_plato(Plato* plato){
    if (cant_platos < 25) {
        platos[cant_platos] = *plato;
        cant_platos++;
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

void Registro::ajustar_arreglo(){ // ajusta el arreglo de pedidos en el hash
    size_t nuevo_size = size * 1.5; // Duplicar tamaño
    Pedido* nuevos_pedidos = new Pedido[nuevo_size];

        // Copiar pedidos existentes al nuevo arreglo
    for (size_t i = 0; i < size; ++i) {
        if (pedidos[i].precio_total() > 0) { // Solo copiar pedidos válidos
            int nuevo_index = f_hash(pedidos[i].get_id()); // Suponiendo que tienes un método get_id()
            while (nuevos_pedidos[nuevo_index].precio_total() > 0) {
                nuevo_index = (nuevo_index + 1) % nuevo_size; // Sondeo lineal
            }
            nuevos_pedidos[nuevo_index] = pedidos[i];
            }
        }

    delete[] pedidos; // Liberar el antiguo arreglo
    pedidos = nuevos_pedidos; // Asignar el nuevo arreglo
    size = nuevo_size; // Actualizar el tamaño
}



//  Constructor Registro
Registro::Registro() : pedidos(new Pedido[1]), size(0), ganancias(0) {}

//  Destructor Registro
Registro::~Registro(){
    delete[] pedidos;
}


// Constructor por numero de mesas
void Registro::Ingreso_mesas(int numero_mesas){
    delete [] pedidos;
    pedidos = new Pedido[numero_mesas];
    size = numero_mesas;
}

//  Agrega un pedido al registro
void Registro::agregar_pedido(Pedido* pedido){
    int index = f_hash(pedido->get_id());
    while (pedidos[index].precio_total() > 0){
        index = (index + 1 ) % size;
    }
    pedidos[index] = *pedido;
     if ((index + 1) / static_cast<double>(size) > 0.8) { // Factor de carga (Revisar)
            ajustar_arreglo();
        }

    
}// EXPERIMENTANDO


//  Retorna el pedido segun id y tipo (servir True , llevar False)
Pedido* Registro::get_pedido(int id, bool tipo){
    for (size_t i = 0; i < size; i++) {
        if ( pedidos[i].get_id() == id && pedidos[i].get_servir() == tipo ){
            cout << "pedido encontrado" << endl;
            return &pedidos[i]; 
        }
    }
    return nullptr;
}


//  Eliminia el pedido segun id y tipo
Pedido* Registro::eliminar_pedido(int id, bool tipo){
    return nullptr;
}

void Registro::Registrar_pedido(int id, bool tipo, Plato* menu){
    ajustar_arreglo();
    Pedido nuevo_pedido;
    nuevo_pedido.set_id(id);
    nuevo_pedido.set_servir(tipo);
    string entrada;
    while (true) {
        getline(cin, entrada);
        size_t pos = entrada.find(" ");
        string funcion = entrada.substr(0, pos);
        if (funcion == "pedir"){
            if (tipo){
                cout << "Servir " << id << " Registrado" << endl;
            }else {
                cout << "Llevar " << id << " Registrado" << endl;
            }
            break;
        }
        else {
            string nuevo_plato = entrada.substr(pos + 1);
            int i = 0;
            bool flag = true;
            while (flag) {
                if (menu[i].nombre == nuevo_plato){
                    Plato* plato_seleccionado = &menu[i];
                    nuevo_pedido.agregar_plato(plato_seleccionado);
                    nuevo_pedido.set_cant_platos();
                    flag = false;
                }
                i++;
            }
        }
    Pedido* nuevo_pedido_ptr = new Pedido(nuevo_pedido);
    cout << nuevo_pedido_ptr->get_nombre(1) << endl;
    agregar_pedido(nuevo_pedido_ptr); 
    }
}

int Registro::f_hash(int id){
    return id % size;
}

void Registro::cerrar() {
    int ganancias = 0;
    cout << "Pedidos pendientes:\n";
    for (size_t i = 0; i < size; i++) {
        if (pedidos[i].precio_total() > 0) { // Si el pedido tiene platos
        ganancias += pedidos[i].precio_total();
            cout << (pedidos[i].get_servir() ? "Mesa " : "Llevar ") << pedidos[i].get_id() << "\n";
        }
    }
    cout << "Ganancias del día: " << ganancias << endl;
    // Liberar memoria dinámica
    delete[] pedidos;
}