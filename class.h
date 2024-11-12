#ifndef CLASS_H
#define CLASS_H
#include <string>

struct Plato{
    std::string nombre;
    int precio;
};

class Pedido{
    private:
        Plato* platos; // arreglo de platos en el pedido, tamaño inicial 25
        bool servir; // true para servir, false para llevar
        size_t cant_platos;
    public:
        Pedido();
        ~Pedido();
        void agregar_plato(Plato* plato); // agrega un plato al pedido
        int precio_total(); // retorna la suma del precio de todos los platos del pedido
};

class Registro{
    private:
        Pedido* pedidos; // arreglo de pedidos, tamaño inicial n (cantidad de mesas)
        size_t size;
        void ajustar_arreglo(); //ajusta el tamaño de la tabla de hashing
        int ganancias;
    public:
        Registro();
        ~Registro();
        void agregar_pedido(Pedido* pedido);
        Pedido* get_pedido(int id, bool tipo); // Retorna el pedido según id y tipo (servir true
        // llevar false)
        Pedido* eliminar_pedido(int id, bool tipo); // Elimina el pedido según id y tipo
};

#endif 