#include <iostream>
#include <fstream>
#include <string>
#include "TDAS.cpp"
using namespace std;

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
    for (int i = 0; i < cant_peliculas; i++) {
        getline(archivo, linea);
        int pos1 = linea.find(';'); //busca el caracter ';' y regresa su posicion
        int pos2 = linea.find(';', pos1 + 1); //busca el caracter ';' justo despues del anterior
        Pelicula* pelicula = new Pelicula(); //crea el espacio de Pelicula
        pelicula->nombre = linea.substr(0, pos1); //obtiene el nombre de la pelicula
        pelicula->director = linea.substr(pos1 + 1, pos2 - pos1 - 1); //obtiene el nombre del director
        pelicula->rating = stof(linea.substr(pos2 + 1)); //obtiene el ranking
        arbol.insertar_pelicula(pelicula); //inserta la pelicula en el arbol
    }
    archivo.close();
    arbol.copiar_arbol();
    string comando;
    while (true){
        cin >> comando;
        if (comando.substr(0,2) == "sd") {
            string nombre_director = comando.substr(3);
            Director* director = arbol.buscar_director(nombre_director);
            if (director) {
                director->mostrar_peliculas();
            }
        }
        else if (comando.substr(0,2) == "sm") {
            string nombre_pelicula == comando.substr(3);
            Pelicula* pelicula = arbol.buscar_pelicula(nombre_pelicula);
            if (pelicula) {
                cout << pelicula->nombre << " / " << pelicula->director << " / " << pelicula->rating << endl;
            }
        }
        else if (comando.substr(0,2) == "br") {
            int n = comando.substr(3);
            arbol.mejores_directores(n);
        }
        else if (comando.substr(0,2) == "wr") {
            int n = comando.substr(3);
            arbol.peores_directores(n);
        }
        else if (comando.substr(0,1) == "e") {
            break;
        }
    }
    return 0;
}
