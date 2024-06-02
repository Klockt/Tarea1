#include "TDAtarea2.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void super_string::InOrdenRec( nodo* nodo, string& text){
    if (nodo == nullptr) return;
    InOrdenRec ( nodo -> left, text ); 
    text +=  nodo->c ;
    InOrdenRec ( nodo -> right, text );
}

void super_string::limpiarRec( nodo* raiz){
    limpiarRec(raiz->left);
    limpiarRec(raiz->right);
    delete raiz;
}

void super_string::agregar(char c) {  // Insertar un caracter en la última posición
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
        //nuevo_nodo ->left = current_nodo; // Nose que hace, pero cuando llamaba el InOrdenMod se quedaba en bucle
    }
    length++;
}

void super_string::juntar(string frase1, string frase2, super_string &s) { // NO ESTOY SEGURO DE QUE TENGA QUE SER DE ESTA FORMA PERO XDD
    string a = frase1 + frase2;
    for ( int i = 0; i < a.size(); i++){
            char caracter = a[i];
            agregar( caracter );
    }
}

void super_string::separar(int i, super_string &a, super_string &b) {  // En la izquierda esta el super_string a y en la derecha el super_string b
    
}


int super_string::recortar(){  // Retorna this->height después de recortar
    return 0;
}

string super_string::stringizar(){  // Debe ser O(n)
    string text = "";
    InOrdenRec(root, text);
    return text;
}

void super_string::limpiar(){  // Se deben borrar todos los nodos del super-string
    limpiarRec(root);
    root = nullptr;
    length = 0;
    height = 0;
}

void super_string::reverso(int inicio , int fin, super_string &b){  // No debe cambiar la altura del árbol
    string texto = stringizar();
    super_string nuevo;
    if (inicio == 0 && fin == texto.size() - 1){
        for (fin; fin != -1; fin--){
            char caracter = texto[fin];
            cout << caracter << endl;
                nuevo.agregar(caracter);
        }
        b = nuevo;
    }
}

void analisis(string a, super_string &b){
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
    if (funcion == "INSERTAR"){                      // INSERTAR 
        string aux;
        int f;
        for ( int i = 9; i < a.size(); i++){
            char caracter = a[i];
            if (caracter != ' '){
                aux += caracter;
            }
            if (caracter == ' '){
                f = ++i;
                break;
            }
        }
        istringstream iss(aux);
        int donde_insertar;
        if (iss >> donde_insertar) {
            for (f; f < a.size(); f++){
                char caracter = a[f];
                b.agregar(caracter);
            }
        } else {
            cerr << "Error al convertir la cadena en enteros." << endl;
        }
    }
    if (funcion == "JUNTAR"){                           // JUNTAR
        int donde_insertar = a[7];
        super_string nuevo;
        string super1 = "", super2 = "";
        for ( int i = 9; i < a.size(); i++){
            bool flag = true;
            char caracter = a[i];
            if (caracter == ' '){
                flag = false;
            } else if (caracter != ' ' && flag){
                super1 += caracter;
            } else if ( !flag ){
                super2 += caracter;
            }
        }
        nuevo.juntar(super1, super2, nuevo);
    } 
    if (funcion == "MOSTRAR"){                          // MOSTRAR
        cout<< b.stringizar() << endl;
    }
    if (funcion == "REVERSO"){                         // REVERSO                               
        int inicio, fin;
        string numeros = "";
        for( int i = 8; i < a.size(); i++){
            char caracter = a[i];
            numeros += caracter;
        }
        istringstream iss(numeros);
        if (iss >> inicio >> fin) {
            b.reverso(inicio, fin, b);
        } else {
            cerr << "Error al convertir la cadena en enteros." << endl;
        }
    }
}

int main() {
    fstream archivo;
    string input;
    super_string arbol;
    archivo.open( "Algo.txt", ios::in );
    if ( archivo.fail() ){
        cout << "No se pudo abrir el archivo";
    }
    
    while (input != "FIN") {
        getline(archivo, input);
        analisis(input, arbol);
    };
    return 0;
}