#include <fstream> // permite abrir el archivo */
#include <iostream>
using namespace std;



struct Pieza {
    char simbolo; // Guarda la pieza */
    int x, y; // posicion dentro del tablero [0, 7] x [0, 7] */
};



//estructura del tablero
struct Tablero {
    int cantidad_piezas; // número de piezas en el tablero */
    Pieza* piezas_tablero; 
};


// estructura que guarda los posibles movimientos del rey Ton */
struct MovRey {
    int x, y;
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
        for ( int i = -1; i < 8; ++i ) { //revisión tablero por filas */
            if ( i == -1 ) {
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






bool Peón ( int a, int b, int c, int d ) { // Movimiento del Peón */
    a+=1;
    if ( a == c ) {
        if ( b - 1 == d || b + 1 ==d) {
            return true;
        }
    }
    return false;
}



bool Reina ( int a, int b, int c, int d ) { // Movimiento de la Reina */
    if ( a == c || b == d) {
        return true;
    }
    if ( abs( a - b ) == abs( c - d ) ) {
        return true;
    }
    return false;
}



bool Alfil ( int a, int b, int c, int d ) { // Movimiento del Alfil */
    if ( abs( a - b ) == abs( c - d ) ) {
        return true;
    }
    return false;
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
    return false;
}



bool Rey (int a, int b, int c, int d) {  // Movimiento del Rey de Sebastián */
    if ( ( a + 1 == c ) || ( a - 1 == c ) || ( b + 1 == d ) || ( b - 1 == d) || ( a + 1 && ( b - 1 == d || b + 1)) || ( a - 1 && ( b - 1 == d || b + 1 == d))) {
        return true;
    }
    return false;
}


bool Jaque ( Tablero tablero ) { // Función la cual revisa si el X (rey) esta en jaque */
    char P, A, C, K, R, T, X;
    for ( int i = 1; i < tablero.cantidad_piezas; ++i) { // Defino los valores x,y,,m,n los cuales equivalen a las coordenas x,y de las piezas y el rey respectivamente */
        int x = tablero.piezas_tablero[i].x;
        int y = tablero.piezas_tablero[i].y;
        int m = tablero.piezas_tablero[0].x;
        int n = tablero.piezas_tablero[0].y;
        cout << x << endl;
        if ( tablero.piezas_tablero[i].simbolo == P ) { 
            if ( Peón (x,y,m,n) ){
                return true;
            }
        }
        if ( tablero.piezas_tablero[i].simbolo == A ) {
            if ( Alfil(x,y,m,n) ){
                cout << x << endl;
                return true;
            }
        }
        if ( tablero.piezas_tablero[i].simbolo == C ) {
            if ( Caballo(x,y,m,n) ){
                return true;
            }    
        }
        if ( tablero.piezas_tablero[i].simbolo == K ) {
            if ( Rey(x,y,m,n) ){
                return true;
            }
        }
        if ( tablero.piezas_tablero[i].simbolo == R ) {
            if ( Reina(x,y,m,n) ){
                return true; 
            }
        }
        if ( tablero.piezas_tablero[i].simbolo == T ) {
            if ( Torre(x,y,m,n) ){
                return true; 
            }
        }
    }
    return false;
}


bool tableroEnJaqueMate (Tablero &tablero) {  // Función que revisa si el tablero esta en jaque mate */
    Tablero p = &tablero;
    int veces_jaque[8] = { 0, 0, 0, 0, 0, 0, 0, 0, };
    if (  !Jaque ( p ) ){                 // EL ERROR ESTA AQUÍ
        cout << Jaque ( p ) << endl;     // Por alguna razon la funcion jaque pasa como falsa, lo que hace que automaticamente se apague la funcion
        cout << true << endl;
        return false;
    }
    else{
        char P, A, C, K, R, T, X;
        int Mov_x[8] = { 1, 1, 1, 0, -1, -1, -1, 0  };    
        int Mov_y[8] = { -1, 0, 1, 1, 1, 0, -1, -1  };
        int X_rey = tablero.piezas_tablero[0].x;
        int Y_rey = tablero.piezas_tablero[0].y;
        for ( int j = 0; j < 8; ++j ) {
            int m = 0;
            int n = 0;
            m = X_rey + Mov_x[j];
            n = Y_rey + Mov_y[j];

            cout << m << endl;

            if ( m < 0 || m > 8 || n < 0 || n > 8 ) {
                m = X_rey;
                n = Y_rey;
            }
            for ( int i = 1; i < tablero.cantidad_piezas; ++i) {    // Utilizé el mismo algoritmo de la funcion jaque, porque tecnicamente era lo mismo solo que mueves al rey
                int x = tablero.piezas_tablero[i].x;
                int y = tablero.piezas_tablero[i].y;
                if ( tablero.piezas_tablero[i].simbolo == P ) { 
                    if ( Peón (x,y,m,n) )
                        veces_jaque[j]++;
                }
                if ( tablero.piezas_tablero[i].simbolo == A ) {
                    if ( Alfil(x,y,m,n) )
                        veces_jaque[j]++;
                }
                if ( tablero.piezas_tablero[i].simbolo == C ) {
                    if ( Caballo(x,y,m,n) )
                        veces_jaque[j]++;
                }
                if ( tablero.piezas_tablero[i].simbolo == K ) {
                    if ( Rey(x,y,m,n) )
                        veces_jaque[j]++;
                }
                if ( tablero.piezas_tablero[i].simbolo == R ) {
                    if ( Reina(x,y,m,n) )
                        veces_jaque[j]++;
                }
                if ( tablero.piezas_tablero[i].simbolo == T ) {
                    if ( Torre(x,y,m,n) )
                        veces_jaque[j]++;
                }
            }
        }
    }
    for ( int i = 0; i < 8 ; ++i ) {
        cout << veces_jaque[i] << endl;
        if ( veces_jaque[i] == 0 ) {
            return false;
        }    
    }
    return true;
}




int main() {
    Tablero p;
    p = revisión_tablero();
    if ( tableroEnJaqueMate( p ) ) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}
