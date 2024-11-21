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
    int numero_mesas;
    cout << "Ingrese el numero de mesas: ";
    cin >> numero_mesas;
    Registro registro;
    registro.Ingreso_mesas(numero_mesas);
    int numero_platos;
    string linea;
    if (getline(archivo, linea)) {
        numero_platos = stoi(linea);
    }
    while (getline(archivo, linea)) {
        size_t pos = linea.find('-');
        string nombre = linea.substr(0, pos);
        string precio_s = linea.substr(pos + 1);
        int precio = stoi(precio_s);
        Plato plato = {nombre, precio};
    }
    archivo.close();
    return 0;
}
    
