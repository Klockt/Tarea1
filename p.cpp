#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Programa {
private:
    int largo_operaciones;
    char* operaciones;
    int* puntero_salida;
    char* puntero_operaciones;

public:
    Programa(int largo_operaciones = 0)
        : largo_operaciones(largo_operaciones), operaciones(new char[largo_operaciones]), puntero_salida(new int), puntero_operaciones(nullptr) {
    }

    ~Programa() {
        delete[] operaciones;
        delete[] puntero_salida;
    }

    void ejecutar_operador() {
        char operacion = *puntero_operaciones;
        if (operacion == '>') {
            mover('>');
        } else if (operacion == '<') {
            mover('<');
        } else if (operacion == '+') {
            ++(*puntero_salida);
        } else if (operacion == '-') {
            --(*puntero_salida);
        } else if (operacion == '.') {
            cout << *puntero_salida ;
        } else if (operacion == ':') {
            cout << obtener();                             
        } else if (operacion == '[') {
            if ((*puntero_salida) == 0) {
                while (*puntero_operaciones != ']') {
                    puntero_operaciones++;
                }
            }
        } else if (operacion == ']') {
            if ((*puntero_salida) != 0) {
                while (*puntero_operaciones != '[') {
                    puntero_operaciones--;
                }
            }
        } else if (operacion == '!') {
            terminar_programa();
        }
    }

    void mover(char dir) {
        if (dir == '>') {
            ++puntero_salida;
        } else if (dir == '<') {
            --puntero_salida;
        } else {
            cout << "Movimiento fuera de límites" << endl;
        }
    }

    void asignar(int valor, int* puntero_salida) {
        *puntero_salida = valor;
    }

    char obtener() {
        int valor = (*puntero_salida);
        if (valor < 0){
            valor =  valor*-1;
        }
        if (valor >= 72) {
            valor = valor % 72;
        }
        char lista[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
                        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 
                        'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
                        'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                        'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', 
                        '7', '8', '9', '.', ':', '+', '-', '<', '>', '[', ']', '!'};
        return lista[valor];
    }

    void terminar_programa() {
        cout << "\n";
    }

    void ejecutar() {
        puntero_operaciones = operaciones;
        while (*puntero_operaciones != '!'){
            ejecutar_operador();
            ++puntero_operaciones;
        }
        ejecutar_operador();
    }

    void mostrar() {
        for (int i = 0; i < largo_operaciones; ++i) {
            cout << operaciones[i];
        }
        cout << endl;
    }

    void set_operaciones(const string& ops) {
        delete[] operaciones;
        largo_operaciones = ops.size();
        operaciones = new char[largo_operaciones];
        for (int i = 0; i < largo_operaciones; ++i) {
            operaciones[i] = ops[i];
        }
        puntero_operaciones = operaciones;
    }
};




class Interprete {
private:
    int cant_programas; // Cantidad de programas
    int largo_salida; // Longitud del arreglo de salida
    int cargado; // Índice del programa cargado actualmente
    Programa* programas; // Puntero a programas
    int* salida; // Arreglo de salida

public:
    // Constructor que inicializa el intérprete con una cantidad de programas y longitud de salida específicas
    Interprete(int cant_programas, int largo_salida)
        : cant_programas(cant_programas), largo_salida(largo_salida), cargado(-1) { // Inicializa las variables cant_programas y largo_salida con sus respectivos valores, y a la variable cargado en -1
        programas = new Programa[cant_programas]; // Se crea el arreglo programas de tipo Programa con largo igual a la variable cant_programas
        salida = new int [largo_salida]; // Se crea el arreglo salida de tipo int con largo igual a la variable largo_salida
    }

    // Destructor que libera la memoria asignada
    ~Interprete() {
        delete[] programas;
        delete[] salida;
    }

    // Función para cargar un programa específico
    void cargar_programa(int n) {
        if (n >= 0 && n < cant_programas) { // Si la variable n esta entre los valores permitidos entra en el if
            cargado = n;
        } else {
            cout << "Número de programa inválido" << endl;
        }
    }

    // Función para ejecutar el programa cargado
    void ejecutar_programa() {
        if (cargado != -1) { // Revisa que el programa pedido exista
            programas[cargado].ejecutar(); // Se utiliza el metodo ejecutar en el programa cargado
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para mostrar el programa cargado
    void mostrar_programa_cargado() {
        if (cargado != -1) { // Revisa que el programa pedido exista
            programas[cargado].mostrar(); // Se utiliza el metodo mostrar en el programa cargado
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para terminar la ejecución del intérprete
    void terminar_ejecucion() {
        cout << "\n"<< endl; // imprime una linea vacia
    }

    // Función para leer programas desde un archivo, el cual se recibe por referencia
    void lectura_de_archivo(fstream& archivo) { 
        for (int i = 0; i < cant_programas; ++i) { // for para poder moverse por el arreglo programas
            string operaciones;
            getline(archivo, operaciones); // Lee una linea completa del archivo en la cual se encuenta un programa completo y se guarda en un string
            programas[i].set_operaciones(operaciones); // Se utiliza el metodo set_operaciones para el programa i, entregandole el string operaciones
        }
    }

};



int main() {
    fstream archivo;
    archivo.open("Programas.txt", ios::in); // Abre el archivo Programas.txt en modo lectura
    if (!archivo.is_open()) { // Entra en el if si es que no se encontró el archivo 
        cout << "No se encontró el archivo" << endl;
        return 1;
    }

    int largo_maximo, cant_programas;
    archivo >> largo_maximo; // Lee la primera linea del archivo (Largo máximo)
    archivo >> cant_programas; // Lee la segunda linea del archivo (Cantidad de programas)
    archivo.ignore();

    Interprete interprete(cant_programas, largo_maximo); // Inicializa un tda interprete con las variables leidas del archivo
    interprete.lectura_de_archivo(archivo); // Utiliza el metodo lectura_de_archivo en el tda interprete, entrgandole el archivo txt 

    archivo.close(); // Cierra el archivo archivo

    char comando;
    int a;
    while (true) { // While que queda en bucle hasta que se ingrese el input 's'
        cin >> comando; // Pide un input
        if (comando == 'c') { // If de cargar progrma 
            cin >> a;
            interprete.cargar_programa(a); //Utiliza el metodo cargar_programa en interprete con un parametro int
        } else if (comando == 'e') { // If de ejecutar programa
            interprete.ejecutar_programa();//Utiliza el metodo ejecutar_programa en interprete
        } else if (comando == 'm') { // If de mostrar programa 
            interprete.mostrar_programa_cargado();//Utiliza el metodo mostrar_programa_cargado en interprete
        } else if (comando == 's') { // If de terminar ejecucion
            interprete.terminar_ejecucion();//Utiliza el metodo terminar_ejecucion en interprete
            return 0;
        } else { // Si el comando ingresado no es correcto entrara en el else
            cout << "Colocar comando aceptable" << endl;
        }
    }

    return 0;
}
