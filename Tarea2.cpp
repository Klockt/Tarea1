#include "TDAtarea2.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;




//FUNCION TIPO VOID INORDENREC: RECORRE EL ARBOL MIENTRAS CREA UN STRING CON LOS CARACTERES DE CADA NODO/*
void super_string::InOrdenRec( nodo* nodo, string& text){  
    if (nodo == nullptr) return;
    InOrdenRec ( nodo -> left, text ); 
    text +=  nodo->c ;
    InOrdenRec ( nodo -> right, text );
}//OUTPUT: STRING/*




//FUNCION TIPO VOID LIMPIARREC: ELIMINA EL ARBOL EMPEZANDO POR LA HOJA IZQUIERDA/*
void super_string::limpiarRec( nodo* raiz){     
    if ( raiz == nullptr ){
        return;
    }
    limpiarRec(raiz->left);
    limpiarRec(raiz->right);
    delete raiz;
}//OUTPUT: ARBOL SIN NODOS/*





//FUNCION TIPO VOID AGREGAR: AGREGA NODOS A LA ULTIMA POSICION DEL ARBOL, ANTES DE AGREGAR UN NODO, ESTE CREA UN ESPACIO PARA EL AGREGADO CON SU POSICION Y SU CARACTER. ADEMAS DE AUMENTAR LA ALTURA 
//POR CADA ITERACIÓN/*
void super_string::agregar(char c) {  
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
}//OUTPUT: CHAR C DENTRO DE EL SUPER STRING/*




//FUNCION TIPO VOID JUNTAR: UNE DOS SUPER STRINGS (EL QUE LLAMA A LA FUNCION Y EL DADO A LA FUNCION), PARA FORMAR UN NUEVO SUPER STRING/*
void super_string::juntar(super_string &s){
    string texto = s.stringizar();
    for ( int i = 0; i < texto.size(); i++){  
        char caracter = texto[i];
        agregar( caracter );
    }
}//OUTPUT: SUPER STRING UNIDO/*




//FUNCION TIPO VOID SEPARAR: TOMA UN INT I (SE REFIERE A UNA POSICIÓN DEL STRING); UN SUPER_STRING "a" (EL CUAL SE SEPARARA) Y UN SUPER_STRING VACIO. "a" SE CONVIERTE EN UN STRING LLAMADO  ORIGINAL, LUEGO CON DOS STRING
//AUXILIARES SE SEPARA EL STRING ORIGINAL Y SE LE DAN ESOS STRING A "part_a" Y "part_b", LUEGO SE BORRAN AMBOS SUPER_STRINGS PARA PODER CREAR UNO NUEVO A BASE EN LA SEPARACIÓN/*
void super_string::separar(int i, super_string &a, super_string &b) {  
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
}//OUTPUT: SUPER_STRING "a" SEPARADO Y "b" SUBTRING/*




//FUNCION TIPO DOUBLE LOG2: CALCULO DE LOG2 DE UNA VARIABLE USANDO LA FORMULA LOG2(X) = LOG X / LOG 2/*
double log2(double x) { 
    return log(x) / log(2.0);
}//OUTPUT: EL RESULTADO DEL CALCULO*/




//FUNCION TIPO INT CALCULO: MEDIADOR DEL CALCULO, COVERTIDOR DE TIPO INT A TIPO DOUBLE/* 
int calculo( int a ) {
    double x = a; 
    double resultado = log2(x);
    return resultado + 1;
}//OUTPUT: EL RESULTADO EQUIVALENTE A LA ALTURA DEL ARBOL/*




//FUNCION TIPO INT RECORTAR: SOLO PUDIMOS ENCONTRAR LA MANERA EN LA CUAL SE PUDIERA CALCULAR LA ALTURA DE UN ARBOL ABB A PARTIR DE UN ARBOL DE ENLACES SIMPLES/*
int super_string::recortar() {
    if (root == nullptr){
        return 0;
    }
    else {
        string texto = stringizar();
        int len = texto.length();
        return calculo( len );
    }
}//OUTPUT: ALTURA DEL ARBOL ABB/*




//FUNCION TIPO STRING STRINGIZAR: CREA UN STRING A PARTIR DE LOS NODOS DEL SUPER_STRING, RECORRIENDOLO EN INORDEN/*
string super_string::stringizar(){  // Debe ser O(n)
    string text = "";
    InOrdenRec(root, text);
    return text;
}//OUTPUT: STRING FORMADO DEL ARBOL/*




//FUNCION TIPO VOID LIMPIAR: LOGRA RESETEAR UN SUPER_STRING/*
void super_string::limpiar(){ 
    limpiarRec(root);
    root = nullptr;         
    length = 0;
    height = 0;
}//OUTPUT: ARBOL RESETEADO/*





//FUNCION TIPO VOID REVERSO: LOGRA VOLTEAR LAS POSICIONES DE UN STRING/*
void super_string::reverso(){   
    string texto = stringizar();
    int len = texto.length();  
    limpiar();
    for (int i = len - 1; i >= 0; i--){  
        char caracter = texto[i];
        agregar(caracter);
    }
}//OUTPUT: STRING VOLTEADO/*




//FUNCION TIPO VOID ANALISIS: ANALIZA LA LINEA DE TEXTO Y DEPENDIENDO DE LOS PRIMEROS CARACTERES LLAMA A LA FUNCION CORRESPONDIENTE/*
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


    //SI LA ENTRADA ES INSERTAR: AGRUPA EL STRING SALTANDOSE LOS ESPACIOS Y LLAMA A LA FUNCION AGREGAR/*
    if (funcion == "INSERTAR"){ 
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
        } 
    }
    //SI LA ENTRADA ES MOSTRAR: REVELA UN STRING LLAMANDO A LA FUNCION STRINGIZAR/*
    if (funcion == "MOSTRAR"){                         
        cout<< b.stringizar() << endl;
    }


    //SI LA ENTRADA ES REVERSO: AGRUPA LOS PARAMETROS DENTRO DE UN STRING, PARA DESPUES INSERTARLOS EN LAS VARIABLES INICIO Y FIN, LUEGO LLAMA A LAS FUNCIONES SEPARAR(), REVERSO(), JUNTAR() Y LIMPIAR()
    //USA SUPER_STRING AUXILIARES PARA LOGRAR INICIALIZAR LAS FUNCIONES, ESTOS SE COMPORTAN COMO SUBSTRING, LUEGO ESTAS SE BORRAN./*
    if (funcion == "REVERSO"){                                                   
        int inicio, fin;
        string numeros = "";
        super_string aux1,aux2;
        for( int i = 8; i < a.size(); i++){
            char caracter = a[i];
            numeros += caracter;

        }
        istringstream iss(numeros);
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


//SI LA ENTRADA ES ELIMINAR: ELIMINA LOS CARACTERES DENTRO DE UN RANGO/*
    if ( funcion == "ELIMINAR"){ 
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


    //SI LA ENTRADA ES RECORTAR: LOGRA REVELAR LA ALTURA DEL ARBOL SI ESTUVIERA BALANCEADO/*
    if (funcion == "RECORTAR") { 
        cout << b.recortar() << endl;
    }
}

//COMO ES VOID NO RETORNA NADA




//FUNCION MAIN: ABRE EL ARCHIVO PRUEBA.TXT Y LO LEE, SI ENCUENTRA UNA LINEA QUE DIGA FIN DETIENE LA EJECUCION, SI NO LLAMA A ANALISIS/*
int main() {
    super_string arbol;
    ifstream archivo( "prueba.txt");      
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
//NO RETORNA UN 0 YA QUE NO ES NECESARIO QUE RETORNE ALGO EN CONCRETO/*