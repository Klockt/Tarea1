#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream archivo;
    archivo.open ("Programas.txt", ios::in);
    if (!archivo.open() ) {
        cout << "No se encontró el archivo" << endl;
    }
    archivo.close();
    return 0;
}