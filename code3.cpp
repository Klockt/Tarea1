#include <fstream> // permite abrir el archivo */
#include <iostream>
using namespace std;


struct Pieza {
    char simbolo; // Guarda la pieza*/
    int x, y; // posicion dentro del tablero [0, 7] x [0, 7] */
};

//estructura del tablero
struct Tablero {
    int cantidad_piezas; // número de piezas en el tablero */
    Pieza* piezas_tablero; // 
};


Tablero revisión_tablero() {
    ifstream archivo; 
    archivo.open("tablero.txt", ios::in); //abrir el archivo en modo lectura*/
    int a;
    Tablero tablero;
    if ( !archivo.is_open() ) {
        cout << "No se ha podido abrir el archivo" << endl;
    }
    else {
        for ( int i = 0; i < 9; ++i ) { //revisión tablero por filas */
            if ( i == 0 ) {
                archivo >> tablero.cantidad_piezas; // guarda el número total de piezas */
                tablero.piezas_tablero = new Pieza[tablero.cantidad_piezas];
            }

            else {
                char a = 0;
                for ( int j = 0; j < 8; ++j) { // revisión del tablero por columnas */
                    char c;
                    archivo >> c;
                     if (c != '.') {
                        tablero.piezas_tablero[a].simbolo = c;
                        tablero.piezas_tablero[a].x = j;
                        tablero.piezas_tablero[a].y = i;
                        ++a;
                    }  
                }
            }
        }
    }
    archivo.close();
    return tablero;
    }






int main() {
    revisión_tablero();
    return 0;
}



 