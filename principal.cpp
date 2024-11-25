#include <iostream>
#include <fstream>
#include <string>
#include "class.h"
using namespace std;

int main() {
    // Declaración de un pedido y apertura del archivo de menú
    Pedido pedido; 
    ifstream archivo("Menu.txt");
    
    // Verificar si el archivo se pudo abrir correctamente
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    int numero_platos = 0;
    string linea;

    // Leer la primera línea del archivo, que indica la cantidad de platos
    if (getline(archivo, linea)) {
        numero_platos = stoi(linea); // Convertir la cantidad de platos a un entero
    }

    // Crear un arreglo de platos basado en la cantidad leída
    Plato menu[numero_platos];
    int i = 0;

    // Leer los datos de cada plato y su precio del archivo
    while (getline(archivo, linea) && numero_platos < 25) {
        size_t pos = linea.find('-'); // Separar el nombre del precio por el delimitador '-'
        string nombre = linea.substr(0, pos);
        string precio_str = linea.substr(pos + 1);
        int precio = stoi(precio_str); // Convertir el precio a un entero
        
        // Guardar el plato en el arreglo
        menu[i] = {nombre, precio};
        i++;
    }
    
    // Cerrar el archivo de menú
    archivo.close();

    // Solicitar el número de mesas al usuario
    int numero_mesas;
    cout << "Ingrese el numero de mesas: ";
    cin >> numero_mesas;

    // Crear un registro de mesas y asignarlas
    Registro registro;
    registro.Ingreso_mesas(numero_mesas);

    // Variables para manejar el flujo del programa
    int id_llevar = 0; // Contador de IDs para pedidos "llevar"
    string funcion, input, variable;

    // Ciclo principal para manejar los comandos del usuario
    while (true) { 
        getline(cin, input); // Leer el comando completo

        // Separar el comando y los parámetros
        size_t pos = input.find(" ");
        funcion = input.substr(0, pos);
        variable = input.substr(pos + 1);
        bool tipo;

        // Comando para registrar un pedido
        if  (funcion == "registrar") {
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            int id;

            // Determinar si el pedido es "llevar" o de mesa
            if (tipo_pedido == "llevar") {
                tipo = false;
                id = ++id_llevar; // Asignar un ID único para pedidos "llevar"
            } else {
                string numero = variable.substr(pos + 1);
                id = stoi(numero); // Convertir el número de mesa a entero
                tipo = true;
            }

            // Registrar el pedido en el registro
            cout << id << "  " << tipo_pedido << endl;
            registro.Registrar_pedido(id, tipo, menu);
        }
        // Comando para mostrar la información de un pedido
        else if (funcion == "info") {
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            string numero = variable.substr(pos + 1);
            int id = stoi(numero);

            // Obtener información del pedido
            Pedido* info_pedido = registro.get_pedido(id, tipo);
            
            // Mostrar el detalle del pedido
            cout << info_pedido->get_nombre(0) << endl;
            for (size_t i = 0; i < info_pedido->get_cant_platos(); ++i) {
                cout << "- " << info_pedido->get_nombre(i) << "\n";
            }
            cout << info_pedido->precio_total() << endl;
        }
        // Comando para pagar un pedido
        else if  (funcion == "pagar") {
            size_t pos = variable.find(" ");
            string tipo_pedido = variable.substr(0 , pos);
            string numero = variable.substr(pos + 1);
            int id = stoi(numero);

            // Obtener información del pedido
            Pedido* info_pedido = registro.get_pedido(id, tipo);
            int total = info_pedido->precio_total(); // Total del pedido
            int propina = total * 0.1;              // Calcular la propina (10%)

            // Mostrar detalles de pago
            cout << "Total:" << total << endl;
            cout << "Propina:" << propina << endl;
            cout << "Total + propina:" << total + propina << endl;
        }
        // Comando para cerrar el programa
        else if (funcion  == "cerrar"){
            registro.cerrar(); // Cerrar el registro
            break; // Terminar el ciclo principal
        }
    }

    return 0;
}
