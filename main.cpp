#include "class.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream archivo("Menu.txt");
    if (!archivo.open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
    return 0;
}