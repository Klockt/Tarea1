#include <iostream>
#include <fstream>
#include <string>
using namespace std;

 class super_string {
 private:
 struct nodo {
      nodo *left = nullptr, *right = nullptr;
 int index;
 char c;
 nodo(int index, char c) {}
 nodo(){}
 };
 int height = 0; // Altura del árbol
 int length = 0; // Largo del super-string
    nodo* root = nullptr; // Raíz del super-string
 public:
 super_string() {}
 void juntar(super_string &s);
 void agregar(char c) {
 }; // Insertar un caracter en la última posición
 // En la izquierda esta el super_string a y en la derecha el super_string b
 void separar(int i, super_string &a, super_string &b);
 void reverso(); // No debe cambiar la altura del árbol
 int recortar(); // Retorna this->height después de recortar
    string stringizar(); // Debe ser O(n)
 void limpiar(); // Se deben borrar todos los nodos del super-string
 };

int INSERTAR(string x, string y, super_string &s) {
    for (int i = 10; i < x.size(); i++) {
        s.agregar(x[i]);
    }
    return 0;
}

void mostrar(super_string &s) {
    cout << s.stringizar() << endl;
}

int analisis(string a) {
    string funcion = "";
    super_string s1;
    for (int i = 0; i < a.size(); i++) {
        char k = a[i];
        if (k == ' ') {
            break;
        }
        else {
            funcion += k;
        }
    }
    if (funcion == "INSERTAR") {
        INSERTAR(a, funcion, s1);
    }
    // Implementa las otras operaciones aquí
    if (funcion == "MOSTRAR") {
        mostrar(s1);
    }
    return 0;
}

int main() {
    string input = "x";
    while (input != "FIN") {
        getline(cin, input);
        analisis(input);
    }
    return 0;
}