#include "class.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main() {
    Pedido pedido; 
    ifstream archivo("Menu.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    int numero_platos = 0;
    string linea;

    // Obtener cantidad de los platos
    if (getline(archivo, linea)) {
        numero_platos = stoi(linea);
    }

    Plato menu[numero_platos];
    int i = 0;

    // Obtener platos y sus respectivos precios
    while (getline(archivo, linea) && numero_platos < 25) {
        size_t pos = linea.find('-');
        string nombre = linea.substr(0, pos);
        string precio_str = linea.substr(pos + 1);
        int precio = stoi(precio_str);
        menu[i] =  {nombre, precio};
        i++;
    }
    
    archivo.close();

    // Ingreso de funciones
    int numero_mesas;
    cout << "Ingrese el numero de mesas: ";
    cin >> numero_mesas;

    Registro registro;
    registro.Ingreso_mesas(numero_mesas);
    int id_llevar = 0;
    string funcion, input, variable;

    // Ciclo de comandos
    while (true) { 
        getline(cin, input);

        size_t pos = input.find(" ");
        funcion = input.substr(0, pos);
        variable = input.substr(pos + 1);
        bool tipo;
         if  (funcion == "registrar") {
            // crea un pedido
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            int id;
            if (tipo_pedido == "llevar") {
                tipo = false;
                id = ++id_llevar;
            } else {
                string numero = variable.substr(pos + 1);
                id = stoi(numero);
                tipo = true;
            }
            cout << id << "  " << tipo_pedido << endl;
            registro.Registrar_pedido(id, tipo, menu);

        }
        else if (funcion == "info") {
            // muestra la informacion del pedido
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            string numero = variable.substr(pos + 1);
            int id = stoi(numero);
            registro.get_pedido(id, tipo);
        }
        else if  (funcion == "pagar") {
            // paga el pedido
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            string numero = variable.substr(pos + 1);
            int id = stoi(numero);
            registro.get_pedido(id, tipo);
        }
        else if (funcion  == "cerrar"){
            // cierra el programa
            break;
        }
    }

    return 0;
}
    
