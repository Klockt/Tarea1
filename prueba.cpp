#include "class.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_PLATOS = 25; // Definir un máximo de platos

int main() {
    Pedido pedido; 
    ifstream archivo("Menu.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    int numero_platos = 0; // Inicializar el número de platos
    string linea;

    // Leer el número de platos
    if (getline(archivo, linea)) {
        numero_platos = stoi(linea);
    }

    // Asegurarse de que no exceda el máximo permitido
    if (numero_platos > MAX_PLATOS) {
        cerr << "El número de platos excede el máximo permitido de " << MAX_PLATOS << endl;
        return 1;
    }

    Plato menu[MAX_PLATOS]; // Arreglo estático de platos
    int i = 0;

    // Leer los platos del archivo
    while (getline(archivo, linea) && i < numero_platos) {
        size_t pos = linea.find('-');
        if (pos != string::npos) { // Verificar que se encontró el separador
            string nombre = linea.substr(0, pos);
            string precio_str = linea.substr(pos + 1);
            int precio = stoi(precio_str);
            menu[i] = {nombre, precio};
            i++;
        }
    }

    archivo.close();

    int numero_mesas;
    cout << "Ingrese el numero de mesas: ";
    cin >> numero_mesas;

    Registro registro;
    registro.Ingreso_mesas(numero_mesas);
    string funcion, input, variable;

    // Bucle de comandos
    while (true) {
        cout << "Ingrese un comando: ";
        cin >> input;

        size_t pos = input.find(' ');
        funcion = input.substr(0, pos);
        variable = input.substr(pos + 1);

        if (funcion == "registrar") {
            // Lógica para registrar un pedido
        }
        else if (funcion == "info") {
            // Lógica para mostrar la información del pedido
        }
        else if (funcion == "pagar") {
            // Lógica para pagar el pedido
        }
        else if (funcion == "cerrar") {
            // Lógica para cerrar el pedido
        }
        else if (funcion == "0") {
            break; // Salir del bucle
        }
        else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0; // No es necesario liberar memoria para arreglos estáticos
}