#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Programa {
private:
    int largo_operaciones; // Longitud del arreglo de operaciones
    char* operaciones; // Arreglo de operaciones
    int* salida; // Arreglo de salida
    char* puntero_operaciones; // Puntero a la posición actual en el arreglo de operaciones

public:
    // Constructor que inicializa el programa con un tamaño específico
    Programa(int largo_operaciones = 0)
        : largo_operaciones(largo_operaciones), operaciones(nullptr), salida(nullptr), puntero_operaciones(nullptr) {
        if (largo_operaciones > 0) {
            operaciones = new char[largo_operaciones];
            salida = new int[largo_operaciones];
            puntero_operaciones = operaciones;
        }
    }

    // Destructor que libera la memoria asignada
    ~Programa() {
        delete[] operaciones;
        delete[] salida;
    }

    // Función para ejecutar un operador específico
    void ejecutar_operador() {
        char operacion = *puntero_operaciones;
        if (operacion == '>') {
            mover('>');
        } else if (operacion == '<') {
            mover('<');
        } else if (operacion == '+') {
            ++(*salida);
        } else if (operacion == '-') {
            --(*salida);
        } else if (operacion == '.') {
            cout << *salida << " "; // Muestra el valor numérico de lo apuntado
        } else if (operacion == ':') {
            cout << convertir_a_caracter((*salida)); // Muestra el carácter convertido
        } else if (operacion == '[') {
            if ((*salida) == 0) {
                int posicion = (*salida);
                // Saltar hasta el cierre de bucle ']'
                while (*salida != 0) {
                    ejecutar_operador();
                }
            }
        } else if (operacion == ']') {
            if (*puntero_operaciones != 0) {
                // Volver al inicio del bucle '['
                while (*puntero_operaciones != '[') {
                    puntero_operaciones--;
                }
            }
        } else if (operacion == '!') {
            terminar_programa();
        }
    }

    // Función para mover el puntero de operaciones
    void mover(char dir) {
        if (dir == '>' && puntero_operaciones < operaciones + largo_operaciones - 1) {
            ++puntero_operaciones;
        } else if (dir == '<' && puntero_operaciones > operaciones) {
            --puntero_operaciones;
        }
    }

    // Función para asignar un valor a la salida
    void asignar(int valor, int* salida) {
        *salida = valor;
    }

    // Función para obtener el valor en la posición actual del puntero de operaciones
    char obtener() {
        return *puntero_operaciones;
    }

    // Función para terminar el programa
    void terminar_programa() {
        cout << "\n";
    }

    // Función para ejecutar todas las operaciones del programa
    void ejecutar() {
        int* resultado = salida;
        for (int i = 0; i < largo_operaciones; ++i) {
            puntero_operaciones = &operaciones[i];
            ejecutar_operador();
        }
    }

    // Función para convertir un valor numérico a un carácter según una tabla de codificación
    char convertir_a_caracter(int valor) {
        /*cout << valor << endl;*/
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

    // Función para mostrar el programa
    void mostrar() {
        cout << "Programa: ";
        for (int i = 0; i < largo_operaciones; ++i) {
            cout << operaciones[i];
        }
        cout << endl;
    }

    // Función para establecer las operaciones del programa
    void set_operaciones(const string& ops) {
        delete[] operaciones;  // Liberar la memoria anterior
        largo_operaciones = ops.size();
        operaciones = new char[largo_operaciones];
        for (int i = 0; i < largo_operaciones; ++i) {
            operaciones[i] = ops[i];
        }
        puntero_operaciones = operaciones;  // Reiniciar el puntero
    }

    // Función para obtener las operaciones del programa
    char* get_operaciones() const { return operaciones; }
};

class Interprete {
private:
    int cant_programas; // Cantidad de programas
    int largo_salida; // Longitud del arreglo de salida
    int cargado; // Índice del programa cargado actualmente
    Programa** programas; // Arreglo de punteros a programas
    int* salida; // Arreglo de salida

public:
    // Constructor que inicializa el intérprete con una cantidad de programas y longitud de salida específicas
    Interprete(int cant_programas, int largo_salida)
        : cant_programas(cant_programas), largo_salida(largo_salida), cargado(-1) {
        programas = new Programa*[cant_programas];
        for (int i = 0; i < cant_programas; ++i) {
            programas[i] = new Programa();
        }
        salida = new int[largo_salida];
        for (int i=0 ;i<largo_salida;i++){
            salida[i]=0
        }
    }

    // Destructor que libera la memoria asignada
    ~Interprete() {
        for (int i = 0; i < cant_programas; ++i) {
            delete programas[i];
        }
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
            
            programas[cargado]->ejecutar();
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para mostrar el programa cargado
    void mostrar_programa_cargado() {
        if (cargado != -1) {
            programas[cargado]->mostrar();
        } else {
            cout << "No hay programa cargado" << endl;
        }
    }

    // Función para terminar la ejecución del intérprete
    void terminar_ejecucion() {
        cout << "Ejecución terminada." << endl;
    }

    // Función para leer programas desde un archivo
    void lectura_de_archivo(fstream& archivo) {
        for (int i = 0; i < cant_programas; ++i) {
            string operaciones;
            getline(archivo, operaciones);
            programas[i]->set_operaciones(operaciones);
        }
    }

    // Función para obtener los programas
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
