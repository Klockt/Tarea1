#include <iostream>
#include "TDA_Programa.cpp"
#include "TDA_interprete.cpp"
#include <fstream>
#include <string>
using namespace std;

/*Programa*/
Programa::Programa(int largo_operaciones)
    : largo_operaciones(largo_operaciones) {
    operaciones = new char[largo_operaciones];
    puntero_operaciones = operaciones;
    puntero_salida = new int[largo_operaciones];
}

Programa::~Programa() {
    delete[] operaciones;
    delete[] puntero_salida;
}

void Programa::ejecutar_operador() {
        char list = new char[' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                             'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                             'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                             'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'V', 'W',
                             'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8',
                             '9', '.', ':', '+', '-', '<', '>', '[', ']', '!'];
        
}

void Programa::mover(char dir) {
    if (dir == '>') {
        ++puntero_operaciones;
    } else if (dir == '<') {
        --puntero_operaciones;
    }
}

void Programa::asignar(int valor, int* salida) {
    *salida = valor;
}

char Programa::obtener() {
    return *puntero_operaciones;
}

void Programa::terminar_programa() {
    std::cout << "Programa terminado." << std::endl;
}

void Programa::ejecutar() {
    for (int i = 0; i < largo_operaciones; ++i) {
        char operacion = operaciones[i];
        if (operacion == '>' || operacion == '<'){
            mover(operacion);
        }
        else if (operacion == '+'){
            ++(*puntero_operaciones);
        }
        else if (operacion == '-'){
            --(*puntero_operaciones);
        }
        else if (operacion == '.'){

        }
        else if (operacion == ','){

        }
        else if (operacion == '['){

        }
        else if (operacion == ']'){

        }
        else if (operacion == '!'){
            terminar_programa();
            return;
        }
    }
}

void Programa::mostrar() {
    cout << "Programa: " << operaciones << endl;
}

/*Interprete*/

Interprete::Interprete(int cant_programas, int largo_salida)
    : cant_programas(cant_programas), largo_salida(largo_salida), cargado(-1) {
    programas = new Programa[cant_programas];
    salida = new int[largo_salida];
}

Interprete::~Interprete(){
    delete[] programas;
    delete[] salida;
}


void Interprete::cargar_programa(int n) {
        if (n >= 0 && n < cant_programas) {
            cargado = n;
            std::cout << "Programa " << n << " cargado.\n";
        } else {
            std::cout << "Número de programa inválido.\n";
            programas[cargado].mostrar();
        }
    }

void Interprete::ejecutar_programa() {
        if (cargado != -1) {
            programas[cargado].ejecutar();
        } else {
            std::cout << "No hay programa cargado.\n";
        }
    }

    void Interprete::mostrar_programa_cargado() {
        if (cargado != -1) {
            programas[cargado].mostrar();
        } else {
            std::cout << "No hay programa cargado.\n";
        }
    }

    void Interprete::terminar_ejecucion() {
        std::cout << "Ejecución terminada.\n";
    }

int main() {
    fstream archivo;
    archivo.open ("Programas.txt", ios::in);
    if (!archivo.is_open() ) {
        cout << "No se encontró el archivo" << endl;
        return 1;
    } 
    // De esta forma queda más simple, para despues poder leer bien los programas
    int largo_maximo, cant_programas;
    Interprete interprete;
    archivo >> largo_maximo;
    archivo >> cant_programas;
    archivo.ignore();
    Interprete.Interprete(cant_programas, largo_maximo);
    char comando;
    int a;
    while (true) {
        cin >> comando;
        if (comando == 'c') {
            cin >> a;
            cargar_programa(a);
        }
        if (comando == 'e') {
            ejecutar_programa();
        }
        if (comando == 'm') {
            mostrar_programa_();
        }
        if (comando == 's') {
            terminar_ejecucion();
            break;
        }
        else {
            cout << "Colocar comando aceptable" << endl;
        }
    }
// No tengo ni idea de como guardar los programas usando el tda
// Si se te ocurre algo avisame :)
    archivo.close();
    return 0;
}
