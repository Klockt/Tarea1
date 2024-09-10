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
        cout << "Constructor llamado con largo_operaciones = " << largo_operaciones << endl;
    }

    ~Programa() {
        delete[] operaciones;
        delete puntero_salida;
        cout << "Destructor llamado" << endl;
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

    char* get_operaciones() const { return operaciones; }
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
        : cant_programas(cant_programas), largo_salida(largo_salida), cargado(-1) {
        programas = new Programa[cant_programas];
        salida = new int [largo_salida];

        for (int i = 0; i < largo_salida; ++i) {
            salida[i] = 0; // O cualquier valor inicial adecuado
        }
    }

    // Destructor que libera la memoria asignada
    ~Interprete() {
        delete[] programas;
        delete[] salida;
    }

    // Función para cargar un programa específico
    void cargar_programa(int n) {
        if (n >= 0 && n < cant_programas) {
            cargado = n;
        } else {
            cout << "Número de programa inválido" << endl;
        }
    }

    // Función para ejecutar el programa cargado
    void ejecutar_programa() {
        if (cargado != -1) {
            programas[cargado].ejecutar();
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para mostrar el programa cargado
    void mostrar_programa_cargado() {
        if (cargado != -1) {
            programas[cargado].mostrar();
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para terminar la ejecución del intérprete
    void terminar_ejecucion() {
        cout << "\n"<< endl;
    }

    // Función para leer programas desde un archivo
    void lectura_de_archivo(fstream& archivo) {
        for (int i = 0; i < cant_programas; ++i) {
            string operaciones;
            getline(archivo, operaciones);
            programas[i].set_operaciones(operaciones);
        }
    }

    // Función para obtener los programas
    Programa* get_programas() const { return programas; }
};



int main() {
    fstream archivo;
    archivo.open("Programas.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "No se encontró el archivo" << endl;
        return 1;
    }

    int largo_maximo, cant_programas;
    archivo >> largo_maximo;
    archivo >> cant_programas;
    archivo.ignore();

    Interprete interprete(cant_programas, largo_maximo);
    interprete.lectura_de_archivo(archivo);

    archivo.close();

    char comando;
    int a;
    while (true) {
        cin >> comando;
        if (comando == 'c') {
            cin >> a;
            interprete.cargar_programa(a);
        } else if (comando == 'e') {
            interprete.ejecutar_programa();
        } else if (comando == 'm') {
            interprete.mostrar_programa_cargado();
        } else if (comando == 's') {
            interprete.terminar_ejecucion();
            return 0;
        } else {
            cout << "Colocar comando aceptable" << endl;
        }
    }

    return 0;
}
