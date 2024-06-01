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
 nodo(int index, char c) : index(index), c(c) {} // REVISAR, YA QUE TUVE QUE PEDIR AYUDA A COPILOT, Y DICE QUE SIN ESTO NO SE INICIALIZA LOS VALORES
 nodo(){}
 };
 int height = 0; // Altura del árbol
 int length = 0; // Largo del super-string
    nodo* root = nullptr; // Raíz del super-string
 public:
 super_string() {}
 void juntar(super_string &s);
 void agregar(char c) {
    nodo *nuevo_nodo = new nodo(length, c);
    if ( root == nullptr ) {
        root = nuevo_nodo;
    }
    else {
        nodo *current_nodo = root;
        while ( current_nodo -> right != NULL) {
            current_nodo = current_nodo->right;
        }
        current_nodo -> right = nuevo_nodo;
        nuevo_nodo ->left = current_nodo;
    }

 }; // Insertar un caracter en la última posición
 // En la izquierda esta el super_string a y en la derecha el super_string b
 void separar(int i, super_string &a, super_string &b);
 void reverso(); // No debe cambiar la altura del árbol
 int recortar(); // Retorna this->height después de recortar
    string stringizar() ; // Debe ser O(n)
 void limpiar(); // Se deben borrar todos los nodos del super-string
 };


void analisis(string a, super_string &b) {
    string funcion = "";
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
        int count = 0;
        for ( int i = 9; i < a.size(); i++)
        {
            char caracter = a[i];
            if ( caracter != ' ') {
                if ( count == 0 ) {
                    int largo_insertado = caracter;
                    count += 1;
                }
                else {
                    b.agregar( caracter );
                }
            }
        }
        
    }
}

int main() {
    string input = "x";
    super_string arbol;
    while (input != "FIN") {
        getline(cin, input);
        analisis(input, arbol);
    }
    return 0;
}