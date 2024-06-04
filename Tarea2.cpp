#include "TDAtarea2.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void super_string::InOrdenRec( nodo* nodo, string& text){  // Recorre el arbol mientras crea un string con los caracteres de cada nodo
    if (nodo == nullptr) return;
    InOrdenRec ( nodo -> left, text ); 
    text +=  nodo->c ;
    InOrdenRec ( nodo -> right, text );
}

void super_string::limpiarRec( nodo* raiz){     // Elimina el arbol empezando por la hoja izquierda 
    if ( raiz == nullptr ){
        return;
    }
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
    }
    length++;
    height++;
}

void super_string::juntar(super_string &s){
    string texto = s.stringizar();
    for ( int i = 0; i < texto.size(); i++){  
        char caracter = texto[i];
        agregar( caracter );
    }
}

void super_string::separar(int i, super_string &a, super_string &b) {  // En la izquierda esta el super_string a y en la derecha el super_string b
    string original = a.stringizar();
    string part_a = original.substr(0, i);
    string part_b = original.substr(i);
    a.limpiar();
    b.limpiar();
    for (char c : part_a) {
        a.agregar(c);
    }
    for (char c : part_b) {
        b.agregar(c);
    }
}

int super_string::recortar() {
    return 0;
}

string super_string::stringizar(){  // Debe ser O(n)
    string text = "";
    InOrdenRec(root, text);
    return text;
}

void super_string::limpiar(){  // Se deben borrar todos los nodos del super-string
    limpiarRec(root);
    root = nullptr;            // LA HICE DE IMPROVISO, PARECE FUNCIONAR BIEN
    length = 0;
    height = 0;
}


void super_string::reverso(){   // cambia las posiciones dentro de un super string
    string texto = stringizar();
    int len = texto.length();  
    limpiar();
    for (int i = len - 1; i >= 0; i--){  
        char caracter = texto[i];
        agregar(caracter);
    }
}

void analisis(string a, super_string &b){ //analisa que funcion procede
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
    if (funcion == "INSERTAR"){ // INSERTAR 
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
        istringstream iss(aux);          // CAMBIE LA FORMA EN QUE LEE LOS NUMERO PARA QUE PUEDA LEER MASS DE UNO TIPO "17" Y NO LEA SOLO "1"
        int donde_insertar;
        if (iss >> donde_insertar) {
            for (f; f < a.size(); f++){
                char caracter = a[f];
                b.agregar(caracter);
            }
        } 
    }
    if (funcion == "MOSTRAR"){                          // MOSTRAR
        cout<< b.stringizar() << endl;
    }
    if (funcion == "REVERSO"){                         // REVERSO                               
        int inicio, fin;
        string numeros = "";
        super_string aux1,aux2;
        for( int i = 8; i < a.size(); i++){
            char caracter = a[i];
            numeros += caracter;
        }
        istringstream iss(numeros); //ahora funciona para substrings
        if (iss >> inicio >> fin) {
                b.separar(inicio, b,aux1);
                b.separar(fin-inicio+1,aux1,aux2);
                aux1.reverso();
                b.juntar(aux1);
                aux1.limpiar();
                b.juntar(aux2);
                aux2.limpiar();
                
            
        } 
    }

    if ( funcion == "ELIMINAR"){ //elimina dentro de un rango
        int inicio, fin;
        string numeros = "";
        super_string aux1,aux2;
        for ( int i = 9; i < a.size(); i++){
            char caracter = a[i];
            numeros += caracter;
        }
        istringstream iss(numeros);
        if (iss >> inicio >> fin) {
            b.separar(inicio, b, aux1);
            b.separar(fin-inicio+1, aux1, aux2);
            aux1.limpiar();
            b.juntar(aux2);
            aux2.limpiar();
        } 
    }
}

int main() {
    super_string arbol;
    ifstream archivo( "prueba.txt");      // PARA QUE LEA ARCHIVOS 
    string linea;
    if ( archivo.fail() ){
        cout << "No se pudo abrir el archivo";
    }
    else {
        while (getline(archivo,linea)) {
            if (linea == "FIN") {
                break;
            }
            else {
                analisis(linea, arbol);
            }
        };
    archivo.close();
    }
    return 0;
}
