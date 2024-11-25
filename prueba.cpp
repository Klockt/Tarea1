#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Plato {
    std::string nombre;
    int precio;
};


class Pedido {
private:
    Plato* platos; // arreglo de platos en el pedido, tamaño inicial 25
    bool servir;   // true para servir, false para llevar
    size_t cant_platos;

public:
    Pedido() : servir(false), cant_platos(0) {
        platos = new Plato[25]; // tamaño inicial 25
    }

    ~Pedido() {
        delete[] platos;
    }

    void agregar_plato(Plato* plato) {
        if (cant_platos < 25) {
            platos[cant_platos++] = *plato; // copia el contenido del plato
        } else {
            std::cout << "El pedido ha alcanzado el máximo de 25 platos.\n";
        }
    }

    int precio_total() {
        int total = 0;
        for (size_t i = 0; i < cant_platos; ++i) {
            total += platos[i].precio;
        }
        return total;
    }

    void mostrar_detalle() const {
        for (size_t i = 0; i < cant_platos; ++i) {
            std::cout << platos[i].nombre << " - " << platos[i].precio << " CLP\n";
        }
    }
};


class Registro {
private:
    Pedido* pedidos; // arreglo de pedidos, tamaño inicial n (cantidad de mesas)
    size_t size;
    int ganancias;

    void ajustar_arreglo() {
        size_t nuevo_size = size * 1.5; // Redimensionar tabla
        Pedido* nuevos_pedidos = new Pedido[nuevo_size];

        for (size_t i = 0; i < size; ++i) {
            nuevos_pedidos[i] = pedidos[i];
        }

        delete[] pedidos;
        pedidos = nuevos_pedidos;
        size = nuevo_size;
    }

public:
    Registro(size_t n = 10) : size(n), ganancias(0) {
        pedidos = new Pedido[n];
    }

    ~Registro() {
        delete[] pedidos;
    }

    void agregar_pedido(Pedido* pedido) {
        // Hashing cerrado (implementación simplificada)
        static size_t contador_llevar = 0;

        for (size_t i = 0; i < size; ++i) {
            if (pedidos[i].precio_total() == 0) { // Espacio vacío encontrado
                pedidos[i] = *pedido;
                if (!pedido->precio_total()) { // Si es "llevar"
                    contador_llevar++;
                }
                if ((i + 1) / static_cast<double>(size) > 0.8) { // Factor de carga
                    ajustar_arreglo();
                }
                return;
            }
        }

        ajustar_arreglo(); // Redimensionar si no hay espacio
        agregar_pedido(pedido); // Intentar nuevamente
    }

    Pedido* get_pedido(int id, bool tipo) {
        for (size_t i = 0; i < size; ++i) {
            if (tipo && pedidos[i].precio_total() == id) { // Pedido "servir"
                return &pedidos[i];
            } else if (!tipo && pedidos[i].precio_total() == id) { // Pedido "llevar"
                return &pedidos[i];
            }
        }
        return nullptr; // No encontrado
    }

    Pedido* eliminar_pedido(int id, bool tipo) {
        Pedido* pedido = get_pedido(id, tipo);
        if (pedido) {
            ganancias += pedido->precio_total();
            pedido->~Pedido();
        }
        return pedido;
    }
};

// Función para cargar platos desde un archivo
std::vector<Plato> cargar_menu(const std::string& filename) {
    std::vector<Plato> menu;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << "\n";
        return menu;
    }

    std::string line;
    int num_platos;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> num_platos;
    }

    while (std::getline(file, line)) {
        size_t pos = line.find('-');
        if (pos != std::string::npos) {
            std::string nombre = line.substr(0, pos - 1);
            int precio = std::stoi(line.substr(pos + 1));
            menu.push_back(Plato{nombre, precio});
        }
    }

    file.close();
    return menu;
}

#define MAX_PLATOS 100 // Máximo número de platos que puede tener el menú

// Función para cargar platos desde un archivo
int cargar_menu(const std::string& filename, Plato menu[], int& num_platos) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << "\n";
        return -1;
    }

    std::string line;
    if (std::getline(file, line)) {
        num_platos = std::stoi(line); // Leer el número de platos
    }

    int count = 0;
    while (count < num_platos && std::getline(file, line)) {
        size_t pos = line.find('-');
        if (pos != std::string::npos) {
            menu[count].nombre = line.substr(0, pos - 1);
            menu[count].precio = std::stoi(line.substr(pos + 1));
            count++;
        }
    }

    file.close();
    return 0;
}

int main() {
    Plato menu[MAX_PLATOS];
    int num_platos = 0;

    // Cargar el menú desde el archivo
    std::string menu_file = "Menu.txt";
    if (cargar_menu(menu_file, menu, num_platos) != 0) {
        return 1;
    }

    std::cout << "Menú cargado exitosamente:\n";
    for (int i = 0; i < num_platos; i++) {
        std::cout << menu[i].nombre << " - " << menu[i].precio << " CLP\n";
    }

    size_t num_mesas;
    std::cout << "\nIngrese el número de mesas: ";
    std::cin >> num_mesas;

    Registro registro(num_mesas);
    std::cin.ignore(); // Limpiar el buffer de entrada

    std::string comando;
    while (true) {
        std::cout << "\nIngrese un comando: ";
        std::getline(std::cin, comando);

        if (comando == "cerrar") {
            std::cout << "Mostrando pedidos pendientes y ganancias del día:\n";
            // Mostrar pendientes y ganancias
            break;
        }

        if (comando.find("registrar") == 0) {
            Pedido* pedido = new Pedido();
            if (comando.find("mesa") != std::string::npos) {
                int mesa_id = std::stoi(comando.substr(comando.find_last_of(' ') + 1));
                registro.agregar_pedido(pedido); // Adaptar lógica para registrar "mesa"
                std::cout << "Pedido registrado para mesa " << mesa_id << "\n";
            } else if (comando.find("llevar") != std::string::npos) {
                registro.agregar_pedido(pedido); // Adaptar lógica para registrar "llevar"
                std::cout << "Pedido registrado para llevar\n";
            } else {
                std::cout << "Comando no reconocido para registrar.\n";
            }

        } else if (comando.find("agregar") == 0) {
            std::string nombre_plato = comando.substr(comando.find(' ') + 1);

            bool plato_encontrado = false;
            for (int i = 0; i < num_platos; i++) {
                if (menu[i].nombre == nombre_plato) {
                    // Lógica para agregar plato al pedido en curso
                    plato_encontrado = true;
                    break;
                }
            }

            if (!plato_encontrado) {
                std::cout << "Plato no encontrado en el menú.\n";
            }

        } else if (comando.find("info") == 0) {
            // Implementar la lógica para mostrar información de un pedido
        } else if (comando.find("pagar") == 0) {
            // Implementar la lógica para eliminar un pedido y mostrar resumen
        } else {
            std::cout << "Comando no reconocido.\n";
        }
    }

    return 0;
}