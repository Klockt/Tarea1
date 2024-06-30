#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

struct cuenta {
    string rol, nombre, descripcion;
};

class registro_cuentas {
private:
    float factor_de_carga = 0.0;
    cuenta* tabla;
    int ranuras = 15;
    int elementos = 0;

    int hash(string rol) {
        int hash_val = 0;
        for (char c : rol) {
            hash_val = (hash_val * 31 + c) % ranuras;
        }
        return hash_val;
    }

    int p(string rol, int i) {
        return (hash(rol) + i) % ranuras;
    }

    void redimensionar(int n) {
        cuenta* nueva_tabla = new cuenta[n];
        int viejas_ranuras = ranuras;
        ranuras = n;
        for (int i = 0; i < viejas_ranuras; ++i) {
            if (!tabla[i].rol.empty()) {
                int j = 0;
                int nueva_pos = p(tabla[i].rol, j);
                while (!nueva_tabla[nueva_pos].rol.empty()) {
                    j++;
                    nueva_pos = p(tabla[i].rol, j);
                }
                nueva_tabla[nueva_pos] = tabla[i];
            }
        }
        delete[] tabla;
        tabla = nueva_tabla;
    }

public:
    registro_cuentas() {
        tabla = new cuenta[ranuras];
    }

    ~registro_cuentas() {
        delete[] tabla;
    }

    cuenta obtener(string rol) {
        int i = 0;
        int pos = p(rol, i);
        while (!tabla[pos].rol.empty() && tabla[pos].rol != rol) {
            i++;
            pos = p(rol, i);
        }
        if (tabla[pos].rol == rol) {
            return tabla[pos];
        } else {
            return {"", "", ""};
        }
    }

    void agregar(cuenta c) {
        if (factor_de_carga >= 0.7) {
            redimensionar(ranuras * 2);
        }
        int i = 0;
        int pos = p(c.rol, i);
        while (!tabla[pos].rol.empty()) {
            if (tabla[pos].rol == c.rol) {
                cout << "Rol ya existente" << endl;
                return;
            }
            i++;
            pos = p(c.rol, i);
        }
        tabla[pos] = c;
        elementos++;
        factor_de_carga = (float)elementos / ranuras;
    }

    void eliminar(string rol) {
        int i = 0;
        int pos = p(rol, i);
        while (!tabla[pos].rol.empty() && tabla[pos].rol != rol) {
            i++;
            pos = p(rol, i);
        }
        if (tabla[pos].rol == rol) {
            tabla[pos] = {"", "", ""};
            elementos--;
            factor_de_carga = (float)elementos / ranuras;
        } else {
            cout << "Rol no existente" << endl;
        }
    }

    void modificar(string rol, string descripcion) {
        int i = 0;
        int pos = p(rol, i);
        while (!tabla[pos].rol.empty() && tabla[pos].rol != rol) {
            i++;
            pos = p(rol, i);
        }
        if (tabla[pos].rol == rol) {
            tabla[pos].descripcion = descripcion;
        } else {
            cout << "Rol no existente" << endl;
        }
    }

    void estadisticas() {
        cout << "RANURAS OCUPADAS: " << elementos << endl;
        cout << "RANURAS TOTALES: " << ranuras << endl;
        cout << "FACTOR DE CARGA: " << factor_de_carga << endl;
    }
};

int main() {
    registro_cuentas rc;
    ifstream archivo("pruebas.txt");
    if (!archivo) {
        cout << "No se logró abrir el archivo" << endl;
        return 0;
    }
    string funcion, rut, nombre, descripcion;
    while (archivo >> funcion){
        if (funcion == "AGREGAR"){
            archivo >> rut >> nombre >> descripcion;
            rc.agregar({rut,nombre,descripcion});
        }
        else if (funcion == "QUITAR") {
            archivo >> rut;
            rc.eliminar(rut);
        }
        else if (funcion == "ESTADISTICAS") {
            rc.estadisticas();
        }
    }
    return 0;
}
