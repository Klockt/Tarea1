#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct cuenta {
// El rol es el identificador de la persona.
// El nombre y la descripcion son valores asociados al rol
    string rol, nombre, descripcion;
};
class registro_cuentas {
    private:
    float factor_de_carga = 0.0;
    cuenta* tabla; // Aca se almacenaran los elementos de la tabla
    int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
    int elementos = 0; //revisar ---------------------------
    int hash(string rol) {
        int hash_val = 0;
        for (char c : rol) {
            hash_val = (hash_val * 31 + c) % ranuras;
        }
        return hash_val;
    } // Se obtiene el hash dado el rol
    int p(string rol, int i) {
        return (hash(rol) + i) % ranuras;
    } // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
    public:
    registro_cuentas() {
        tabla = new cuenta[ranuras];
    } // (Recuerde que puede crear con distintos parametros)
    ~registro_cuentas() {
        delete[] tabla;
    }
    cuenta obtener(string rol); // Dado el rol, devuelve la cuenta con ese rol
    void agregar(cuenta c); // Se agrega una cuenta a la tabla
    void eliminar(string rol); // Se elimina la cuenta
    void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
    void redimensionar(int n); // Se redimensiona la tabla a n espacios
    void estadisticas(); // Debe mostrar las estadisticas
};

