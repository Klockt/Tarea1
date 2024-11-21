#include <iostream>
#include <string>
#include <fstream>

struct Plato {
    std::string nombre;
    int precio;
};

class Pedido {
private:
    Plato* platos; // Array of dishes in the order, initial size 25
    bool servir; // true for serving, false for takeout
    size_t cant_platos;

public:
    Pedido() : platos(new Plato[25]), servir(true), cant_platos(0) {} // Constructor
    ~Pedido() { delete[] platos; } // Destructor

    void agregar_plato(const Plato& plato) {
        if (cant_platos < 25) {
            platos[cant_platos++] = plato; // Add the dish to the order
        } else {
            std::cerr << "Error: No more space to add plates." << std::endl;
        }
    }

    int precio_total() {
        int total = 0;
        for (size_t i = 0; i < cant_platos; i++) {
            total += platos[i].precio; // Sum the prices of all dishes
        }
        return total;
    }

    void mostrar_pedido() {
        std::cout << "Platos en el pedido:" << std::endl;
        for (size_t i = 0; i < cant_platos; i++) {
            std::cout << platos[i].nombre << " - $" << platos[i].precio << std::endl;
        }
    }
};

int main() {
    const int MAX_PLATOS = 100; // Max number of dishes in the menu
    Plato menu[MAX_PLATOS]; // Array to hold the menu
    int num_platos = 0; // Number of dishes read from the menu file

    std::ifstream archivo("Menu.txt");
    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo Menu.txt" << std::endl;
        return 1;
    }

    // Read dishes from the menu file
    std::string linea;
    while (std::getline(archivo, linea) && num_platos < MAX_PLATOS) {
        size_t comma_pos = linea.find('-');
        if (comma_pos != std::string::npos) {
            std::string nombre = linea.substr(0, comma_pos); // Get the name
            std::string precio_str = linea.substr(comma_pos + 1); // Get the price part

            try {
                int precio = std::stoi(precio_str); // Convert price to integer
                menu[num_platos++] = {nombre, precio}; // Store the Plato in the menu
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Precio inválido en la línea: " << linea << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: Precio fuera de rango en la línea: " << linea << std::endl;
            }
        } else {
            std::cerr << "Error: Formato de línea inválido: " << linea << std::endl;
        }
    }

    archivo.close();

    // Display the menu to the user
    std::cout << "Menu:" << std::endl;
    for (int i = 0; i < num_platos; i++) {
        std::cout << i + 1 << ". " << menu[i].nombre << " - $" << menu[i].precio << std::endl;
    }

    Pedido pedido; // Create a new Pedido
    int opcion;
    std::cout << "Ingrese el número del plato que desea agregar al pedido (0 para finalizar): " << std::endl;
    while (true) {
        std::cin >> opcion;
        if (opcion == 0) {
            break; // Exit the loop if the user inputs 0
        }
        if (opcion > 0 && opcion <= num_platos) {
            pedido.agregar_plato(menu[opcion - 1]); // Add the selected dish to the order
            std::cout << "Plato agregado: " << menu[opcion - 1].nombre << std::endl;
        } else {
            std::cerr << "Opción inválida. Intente de nuevo." << std::endl;
        }
    }

    // Output total price of the order
    pedido.mostrar_pedido();
    return 0;
}