#include <iostream>
#include <fstream>
#include <string>
#include "Director.cpp"
#include "Arbol.cpp"
using namespace std;


int main() {
    ifstream archivo("Peliculas.txt");
    if (!archivo){
        cout << "No se logró encontrar el archivo" << endl;
        return 1;
    }
    string linea;
    while ( getline(archivo,linea)){
        cout << linea << endl;
    }
    return 0;
}