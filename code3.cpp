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
    Pieza* piezas_tablero; 
};



// Función para hacer un arreglo de structs sobre el tablero /* 
Tablero revisión_tablero() { 
    ifstream archivo; 
    archivo.open("tablero.txt", ios::in); //abrir el archivo en modo lectura */
    int a;
    Tablero tablero;
    if ( !archivo.is_open() ) {
        cout << "No se ha podido abrir el archivo" << endl;
    }
    else {
        for ( int i = 0; i < 9; ++i ) { //revisión tablero por filas */
            if ( i == 0 ) {
                archivo >> tablero.cantidad_piezas; // guarda el número total de piezas */
                tablero.piezas_tablero = new Pieza[tablero.cantidad_piezas]; // crea el espacio necesario para las piezas */
            }
            else {
                char a = 0;
                for ( int j = 0; j < 8; ++j) { // revisión del tablero por columnas */
                    char c;
                    archivo >> c;
                    if (c == 'X') {
                        tablero.piezas_tablero[0].simbolo = c;
                        tablero.piezas_tablero[0].x = j;
                        tablero.piezas_tablero[0].y = i;
                    }
                    if (c != '.') { // discriminar a los puntos */ 
                        tablero.piezas_tablero[a+1].simbolo = c;
                        tablero.piezas_tablero[a+1].x = j;
                        tablero.piezas_tablero[a+1].y = i;
                        ++a;
                    }  
                }
            }
        }
    }
    archivo.close();
    return tablero;
}



bool Jaque ( Tablero tablero ) { // Función la cual revisa si el X (rey) esta en jaque */
    char P;
    char A;
    char C;
    char K;
    char R;
    char X;
    for ( int i = 1; i < tablero.cantidad_piezas; ++i) { // Defino los valores x,y,,m,n los cuales equivalen a las coordenas x,y de las piezas y el rey respectivamente */
        int x = tablero.piezas_tablero[i].x;
        int y = tablero.piezas_tablero[i].y;
        int m = tablero.piezas_tablero[0].x;
        int n = tablero.piezas_tablero[0].y;
        if ( tablero.piezas_tablero[i].simbolo == P ){ 
            Peón (x,y,m,n);
        }
        if ( tablero.piezas_tablero[i].simbolo == A) {
            Alfil(x,y,m,n);
        }
        if ( tablero.piezas_tablero[i].simbolo == C ) {
            Caballo(x,y,m,n);
        }
        if ( tablero.piezas_tablero[i].simbolo == K ) {
            Rey(x,y,m,n);
        }
        if ( tablero.piezas_tablero[i].simbolo == R ) {
            Reina(x,y,m,n); 
        }
    }
}



bool Peón ( int a, int b, int c, int d ) { // Movimiento del Peón */
    a+=1;
    if ( a == c ) {
        if ( b - 1 == d || b + 1 ==d) {
            return true;
        }
    }
    
}



bool Reina ( int a, int b, int c, int d ) { // Movimiento de la Reina */
    if ( a == c || b == d) {
        return true;
    }
    if ( abs( a - b ) == abs( c - d ) ) {
        return true;
    }
}



bool Alfil ( int a, int b, int c, int d ) { // Movimiento del Alfil */
    if ( abs( a - b ) == abs( c - d ) ) {
        return true;
    }
}



bool Caballo ( int a, int b, int c, int d ) { // Movimiento del Caballo */
    if ( a + 2 == c && ( b + 1 == d || b - 1 == d ) ) {
        return true;
    }
    if ( a - 2 == c && ( b + 1 == d || b - 1 == d ) ) {
        return true;
    }
    if ( a + 1 == c && ( b + 2 == d || b - 2 == d ) ) {
        return true; 
    }
    if ( a - 1 == c && ( b - 2 == d || b + 2 == d ) ) {
        return true;
    }
    return false;
}



bool Torre (int a, int b, int c, int d) { // Movimiento de la Torre */
    if ( a == c || b == d) {
        return true;
    }
}



bool Rey (int a, int b, int c, int d) {  // Movimiento del Rey de Sebastián */
    if ( ( a + 1 == c ) || ( a - 1 == c ) || ( b + 1 == d ) || ( b - 1 == d) || ( a + 1 && ( b - 1 == d || b + 1)) || ( a - 1 && ( b - 1 == d || b + 1 == d))) {
        return true;
    }
 
}



int main() {
    revisión_tablero();
    return 0;
}



 