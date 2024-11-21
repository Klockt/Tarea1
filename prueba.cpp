#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ****
// * Estructura Plato
// ****
// * Representa un plato en el menú con su nombre y precio.
// ****
struct Plato {
    string nombre; // Nombre del plato
    int precio;    // Precio del plato
};

// ****
// * Clase Pedido
// ****
// * Representa un pedido en el restaurante.
// ****
class Pedido {
private:
    Plato* platos;       // Arreglo dinámico de platos (máximo 25)
    size_t cant_platos;  // Número de platos en el pedido
    bool servir;         // true: servir, false: para llevar
    static const int MAX_PLATOS = 25; // Límite de platos por pedido

public:
    // Constructor
    Pedido(bool tipo_servir = true) {
        this->servir = tipo_servir;
        this->cant_platos = 0;
        this->platos = new Plato[MAX_PLATOS]; // Inicializar el arreglo de platos
    }

    // Destructor
    ~Pedido() {
        delete[] platos; // Liberar memoria del arreglo dinámico
    }

    // ****
    // * void agregar_plato
    // ****
    // * Agrega un plato al pedido, verificando que no exceda el límite.
    // ****
    void agregar_plato(Plato* plato) {
        if (cant_platos < MAX_PLATOS) {
            platos[cant_platos++] = *plato; // Copiar el plato al arreglo
        } else {
            cout << "El pedido ha alcanzado el límite de platos.\n";
        }
    }

    // ****
    // * int precio_total
    // ****
    // * Calcula y retorna la suma de los precios de todos los platos del pedido.
    // ****
    int precio_total() const {
        int total = 0;
        for (size_t i = 0; i < cant_platos; ++i) {
            total += platos[i].precio;
        }
        return total;
    }

    // ****
    // * void mostrar_pedido
    // ****
    // * Muestra el contenido del pedido y su precio total.
    // ****
    void mostrar_pedido() const {
        cout << (servir ? "Pedido para servir:\n" : "Pedido para llevar:\n");
        for (size_t i = 0; i < cant_platos; ++i) {
            cout << "- " << platos[i].nombre << ": $" << platos[i].precio << '\n';
        }
        cout << "Total: $" << precio_total() << "\n\n";
    }
};

// ****
// * Clase Registro
// ****
// * Maneja la tabla hash de pedidos.
// ****
class Registro {
private:
    Pedido* pedidos;    // Arreglo dinámico de pedidos
    size_t size;        // Tamaño actual de la tabla
    int ganancias;      // Ganancias totales del día

    // Ajusta el tamaño de la tabla de hashing (no implementado aquí)
    void ajustar_arreglo() {
        // Código para redimensionar la tabla según el factor de carga
    }

public:
    // Constructor
    Registro(size_t n) {
        this->size = n; // Tamaño inicial basado en el número de mesas
        this->ganancias = 0;
        this->pedidos = new Pedido[n]; // Crear arreglo dinámico
    }

    // Destructor
    ~Registro() {
        delete[] pedidos; // Liberar memoria del arreglo
    }

    // ****
    // * void agregar_pedido
    // ****
    // * Agrega un nuevo pedido al registro.
    // ****
    void agregar_pedido(Pedido* pedido, int id) {
        if (id >= 0 && id < size) {
            pedidos[id] = *pedido;
        } else {
            cout << "ID fuera de rango.\n";
        }
    }

    // ****
    // * Pedido* get_pedido
    // ****
    // * Retorna un pedido según el ID y tipo (servir o llevar).
    // ****
    Pedido* get_pedido(int id, bool tipo) {
        if (id >= 0 && id < size) {
            return &pedidos[id];
        }
        return nullptr; // Pedido no encontrado
    }

    // ****
    // * Pedido* eliminar_pedido
    // ****
    // * Elimina un pedido y actualiza las ganancias.
    // ****
    Pedido* eliminar_pedido(int id, bool tipo) {
        if (id >= 0 && id < size) {
            Pedido* pedido = &pedidos[id];
            ganancias += pedido->precio_total();
            // Aquí podría manejarse la eliminación (e.g., marcar como vacío)
            return pedido;
        }
        return nullptr;
    }
};

// ****
// * Main: Pruebas iniciales
// ****
int main() {
    // Crear platos
    Plato plato1 = {"Pad Thai", 10000};
    Plato plato2 = {"Pho", 10500};
    Plato plato3 = {"Gohan", 8000};

    // Crear un pedido
    Pedido pedido1(true);
    pedido1.agregar_plato(&plato1);
    pedido1.agregar_plato(&plato2);
    pedido1.mostrar_pedido();

    // Crear registro con 5 mesas
    Registro registro(5);
    registro.agregar_pedido(&pedido1, 0);

    // Obtener y mostrar el pedido
    Pedido* p = registro.get_pedido(0, true);
    if (p) {
        p->mostrar_pedido();
    }

    return 0;
}
