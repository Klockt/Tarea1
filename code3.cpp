#include <fstream> //permite abrir el archivo*/
#include <iostream>
using namespace std;

struct Pieza {
    char simbolo; //definición de pieza*/
    int x, y;// posicion dentro del tablero [0, 7] x [0, 7]*/
};

//estructura del tablero
struct Tablero {
    Pieza piezas_tablero[8][8]; // Define una matriz de 8 x 8 la cual representa el tablero, este siendo [fila] x [columna], ademas cada elemento de la matriz puede contener una Pieza*/
};


Tablero revisión_tablero() {
    ifstream archivo; 
    archivo.open("tablero.txt", ios::in); //abrir el archivo en modo lectura*/
    Tablero tablero;
    char letra;
    if ( !archivo.is_open() ) {
        cout << "No se ha podido abrir el archivo" << endl;
    }
    else {
        for ( int i = 0; i < 9; ++i ) {
            if ( i == 0 ) {
                archivo >> tablero.piezas_tablero[0][0].simbolo; // aquí se salta la primera linea, ya que necesitamos saber que piezas hay*/
            }
            else {
                for ( int j = 0; j < 8; ++j) {
                    archivo >> letra;
                    Pieza pieza_nueva = {letra, i-1, j};
                    tablero.piezas_tablero[i - 1][j] = pieza_nueva; // colocar las piezas dentro de la matriz*/
                    }
                }
            }
        }
    archivo.close();
    return tablero;
    }


int main() {

}


 