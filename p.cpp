#include <iostream>
#include <fstream>
#include <string>
#include "Director.h"
#include "Arbol.h"
using namespace std;


struct Pelicula {
    string nombre ;
    string director ;
    float rating ;
};


int main() {
    Arboles arbol;
    ifstream archivo("Peliculas.txt");
    if (!archivo){
        cout << "No se logró encontrar el archivo" << endl;
        return 1;
    }
    string linea;
    int cant_peliculas;
    archivo >> cant_peliculas;
    archivo.ignore();
    for (int i = 0; i < num_peliculas; i++) {
        getline(archivo, linea);
        size_t pos1 = linea.find(';'); //busca el caracter ';' y regresa su posicion
        size_t pos2 = linea.find(';', pos1 + 1); //busca el caracter ';' justo despues del anterior
        Pelicula* pelicula = new Pelicula(); //crea el espacio de Pelicula
        pelicula->nombre = linea.substr(0, pos1); //obtiene el nombre de la pelicula
        pelicula->director = linea.substr(pos1 + 1, pos2 - pos1 - 1); //obtiene el nombre del director
        pelicula->rating = stof(linea.substr(pos2 + 1)); //obtiene el ranking
        arbol.insertar_pelicula(pelicula); //inserta la pelicula en el arbol

    }
    archivo.close();
    return 0;
}