#include <iostream>
#include "TDA_Programa.cpp"
#include "TDA_interprete.cpp"
#include <fstream>
#include <string>
using namespace std;

int main() {
    fstream archivo;
    archivo.open ("Programas.txt", ios::in);
    if (!archivo.is_open() ) {
        cout << "No se encontró el archivo" << endl;
        return 1;
    } 
    // De esta forma queda más simple, para despues poder leer bien los programas
    int largo_maximo, cant_programas;
    Programa programas;
    archivo >> largo_maximo;
    archivo >> cant_programas;
    archivo.ignore();

    // No tengo ni idea de como guardar los programas usando el tda
    // Si se te ocurre algo avisame :)
    while (archivo >> programas ) {
    } 


    cout << largo_maximo << " y " << programas << endl;

    archivo.close();
    return 0;
}
