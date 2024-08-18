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
    else {
        int numero, largo_maximo, programas, linea;
        linea = 0;
        while (archivo >> numero ) {
            if (linea == 0) {
                largo_maximo = numero;
                linea++;

            }
            else if (linea == 1) {
                programas = numero;
                linea++;
            }
        } 
    } 
    archivo.close();
    return 0;
}