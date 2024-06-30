#include "TDAtarea3.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

// Función para redimensionar la tabla
void registro_cuentas::redimensionar(int n) {
    cuenta* nueva_tabla = new cuenta[n]; // Crea una nueva tabla de tamaño n
    int viejas_ranuras = ranuras; // Guarda el número de ranuras antiguas
    ranuras = n; // Actualiza el número de ranuras a n
    for (int i = 0; i < viejas_ranuras; ++i) { // Recorre las ranuras antiguas
        if (!tabla[i].rol.empty()) { // Si la ranura no está vacía
            int j = 0;
            int nueva_pos = p(tabla[i].rol, j); // Define la nueva posición
            while (!nueva_tabla[nueva_pos].rol.empty()) { // Mientras la nueva posición no esté vacía
                j++;
                nueva_pos = p(tabla[i].rol, j); // Actualiza la nueva posición
            }
            nueva_tabla[nueva_pos] = tabla[i]; // Asigna el valor a la nueva posición
        }
        delete[] tabla; // Elimina la tabla antigua
        tabla = nueva_tabla; // Actualiza la tabla
    }
}

// Función para obtener informacion designada en el rol
cuenta registro_cuentas::obtener(string rol) {
    int i = 0;
    int pos = p(rol, i); // Define la posición inicial
    while (!tabla[pos].rol.empty()) { // Mientras la tebla en la posición no esté vacía
        if (tabla[pos].rol == rol) { // Si el rol coincide
            cout << tabla[pos].nombre + " " << tabla[pos].descripcion << endl; // Imprime el nombre y descripción asignados al rol
            return {"","",""}; // Retorna strings vacios
        }
        i++;
        pos = p(rol, i); // si no encuentra pasa a la siguiente posicion
    }
    return {"","",""}; // Retorna strings vacios si no se encontró el rol
}

// Función para agregar una cuenta
void registro_cuentas::agregar(cuenta c) {
    if (factor_de_carga >= 0.9) { // Si el factor de carga es mayor o igual a 0.9
        redimensionar(ranuras * 2); // Redimensiona la tabla, aumentando en 15
    }
    int i = 0;
    int pos = p(c.rol, i); // Define la posición inicial
    while (!tabla[pos].rol.empty()) { // Mientras la tabla en la posición no esté vacía
        if (tabla[pos].rol == c.rol) { // Si el rol coincide
            cout << "Rol ya existente" << endl; // Imprime advertencia de existencia
            return; // Retorna vacio
        }
        i++;
        pos = p(c.rol, i); // Si no coincide, pasa a la siguiente posición
    }
    tabla[pos] = c; // Asigna la cuenta a la posición
    elementos++; // Incrementa el número de elementos
    factor_de_carga = (float)elementos / ranuras; // Actualiza el factor de carga
}

// Función para eliminar una cuenta por su rol
void registro_cuentas::eliminar(string rol) {
    int i = 0;
    int pos = p(rol, i); // Define la posición inicial
    while (!tabla[pos].rol.empty() && tabla[pos].rol != rol) { // Busca la cuenta, itera hasta encontrarla por el rol
        i++;
        pos = p(rol, i); // Pasa a la siguiente posición
    }
    if (tabla[pos].rol == rol) { // Si el rol coincide
        tabla[pos] = {"", "", ""}; // Vacía la posición
        elementos--; // Disminuye el número de elementos
        factor_de_carga = (float)elementos / ranuras; // Actualiza el factor de carga
    } else {
        cout << "Rol no existente" << endl; // Imprime advertencia de no existencia
    }
}

// Función para modificar la descripción de una cuenta por su rol
void registro_cuentas::modificar(string rol, string descripcion) {
    int i = 0;
    int pos = p(rol, i); // Define la posición inicial
    while (!tabla[pos].rol.empty() && tabla[pos].rol != rol) { // Itera hasta encontrar el rol por su posicion
        i++;
        pos = p(rol, i); // Pasa a la siguiente posición
    }
    if (tabla[pos].rol == rol) { // Si el rol coincide
        tabla[pos].descripcion = descripcion; // Modifica la descripción
    } else {
        cout << "Rol no existente" << endl; // Imprime advertencia de no existencia
    }
}

// Función para imprimir las estadísticas
void registro_cuentas::estadisticas(){
    cout << "RANURAS OCUPADAS: " << elementos << endl; // Imprime el número de ranuras ocupadas
    cout << "RANURAS TOTALES: " << ranuras << endl; // Imprime el número total de ranuras
    cout << "FACTOR DE CARGA: " << factor_de_carga << endl; // Imprime el factor de carga
}

// Función principal
int main() {
    registro_cuentas registro; // Crea un registro de cuentas
    fstream archivo; 
    archivo.open("pruebas.txt", ios::in); // Abre el archivo de pruebas
    if (!archivo) { // Si no se pudo abrir el archivo
        cout << "No se logró abrir el archivo" << endl; // Imprime un mensaje de error
        return 0; // Retorna 0
    }
    string funcion, rol, nombre, descripcion; // Crea strings para almacenar la información sacada del texto
    while (archivo >> funcion){ 
        if (funcion == "AGREGAR"){ // Si la función es AGREGAR
            archivo >> rol >> nombre >> descripcion; // Lee el rol, nombre y descripción
            registro.agregar({rol,nombre,descripcion}); // Agrega la cuenta al registro (llama a la funcion agregar)
        }
        else if (funcion == "QUITAR") { // Si la función es QUITAR
            archivo >> rol; // Lee el rol
            registro.eliminar(rol); // Elimina la cuenta del registro por el rol (llama a la funcion eliminar)
        }
        else if (funcion == "ESTADISTICAS") { // Si la función es ESTADISTICAS
            registro.estadisticas(); // Imprime las estadísticas del registro (llama a la funcion estadisticas)
        }
        else if (funcion == "OBTENER"){ // Si la función es OBTENER
            archivo >> rol; // Lee el rol
            registro.obtener(rol); // Obtiene la cuenta del registro (llama a la funcion obtener)
        }
    }
    archivo.close(); // Cierra el archivo
    return 0; // Retorna 0
}
