#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Programa {
private:
    int largo_operaciones;
    char* puntero_operaciones;
    int* puntero_salida;
    char* operaciones;

public:
    Programa(int largo_operaciones)
        : largo_operaciones(largo_operaciones) {
        operaciones = new char[largo_operaciones];
        puntero_operaciones = operaciones;
        puntero_salida = new int[largo_operaciones];
    }

    ~Programa() {
        delete[] operaciones;
        delete[] puntero_salida;
    }

    void ejecutar_operador() {
        // Implementar la lógica para ejecutar un operador específico
    }

    void mover(char dir) {
        if (dir == '>') {
            ++puntero_operaciones;
        } else if (dir == '<') {
            --puntero_operaciones;
        }
    }

    void asignar(int valor, int* salida) {
        *salida = valor;
    }

    char obtener() {
        return *puntero_operaciones;
    }

    void terminar_programa() {
        std::cout << "Programa terminado." << std::endl;
    }

    void ejecutar() {
        for (int i = 0; i < largo_operaciones; ++i) {
            char operacion = operaciones[i];
            if (operacion == '>' || operacion == '<') {
                mover(operacion);
            } else if (operacion == '+') {
                ++(*puntero_operaciones);
            } else if (operacion == '-') {
                --(*puntero_operaciones);
            } else if (operacion == '.') {
                // Implementar lógica para '.'
            } else if (operacion == ',') {
                // Implementar lógica para ','
            } else if (operacion == '[') {
                // Implementar lógica para '['
            } else if (operacion == ']') {
                // Implementar lógica para ']'
            } else if (operacion == '!') {
                terminar_programa();
                return;
            }
        }
    }

    void mostrar() {
        cout << "Programa: " << operaciones << endl;
    }

    // Hacer operaciones accesible para lectura
    char* get_operaciones() const { return operaciones; }
};

class Interprete {
private:
    int cant_programas;
    int largo_salida;
    int cargado;
    Programa** programas;  // Cambiar a un arreglo de punteros
    int* salida;

public:
    Interprete(int cant_programas, int largo_salida)
        : cant_programas(cant_programas), largo_salida(largo_salida), cargado(-1) {
        programas = new Programa*[cant_programas];  // Inicializar el arreglo de punteros
        for (int i = 0; i < cant_programas; ++i) {
            programas[i] = new Programa(largo_salida);  // Inicializar cada objeto Programa
        }
        salida = new int[largo_salida];
    }

    ~Interprete() {
        for (int i = 0; i < cant_programas; ++i) {
            delete programas[i];  // Liberar cada objeto Programa
        }
        delete[] programas;  // Liberar el arreglo de punteros
        delete[] salida;
    }

    void cargar_programa(int n) {
        if (n >= 0 && n < cant_programas) {
            cargado = n;
            std::cout << "Programa " << n << " cargado.\n";
        } else {
            std::cout << "Número de programa inválido.\n";
        }
    }

    void ejecutar_programa() {
        if (cargado != -1) {
            programas[cargado]->ejecutar();
        } else {
            std::cout << "No hay programa cargado.\n";
        }
    }

    void mostrar_programa_cargado() {
        if (cargado != -1) {
            programas[cargado]->mostrar();
        } else {
            std::cout << "No hay programa cargado.\n";
        }
    }

    void terminar_ejecucion() {
        std::cout << "Ejecución terminada.\n";
    }

    void lectura_de_archivo(fstream& archivo) {
        for (int i = 0; i < cant_programas; ++i) {
            string operaciones;
            getline(archivo, operaciones);
            for (int j = 0; j < largo_salida && j < operaciones.size(); ++j) {
                programas[i]->get_operaciones()[j] = operaciones[j];
            }
        }
    }

    // Hacer programas accesible para lectura
    Programa** get_programas() const { return programas; }
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
            break;
        } else {
            cout << "Colocar comando aceptable" << endl;
        }
    }

    return 0;
}
