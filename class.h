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
        int id_pedido;
    public:
        int get_cant_platos();
        std::string get_nombre(int i);
        void set_id(int valor);
        void set_servir(bool tipo);
        int get_id();
        void set_cant_platos();
        bool get_servir();
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
        void cerrar();
        void Registrar_pedido(int id, bool tipo, Plato* menu);
        int f_hash(int id); // retorna la posición en la que se encuentra el pedido en la tabla de hashing
        void Ingreso_mesas(int numero_mesas);
        Registro();
        ~Registro();
        void agregar_pedido(Pedido* pedido);
        Pedido* get_pedido(int id, bool tipo); // Retorna el pedido según id y tipo (servir true
        // llevar false)
        Pedido* eliminar_pedido(int id, bool tipo); // Elimina el pedido según id y tipo
};

#endif 