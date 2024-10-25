#ifndef DIRECTOR_H
#define DIRECTOR_H
#include <string>

class Director {
    private :
        struct lNodo {
            Pelicula * val ;
            lNodo * sig ;
        };
        lNodo * head ;
        lNodo * curr ;
        lNodo * tail ;
        size_t size ; // longitud lista
        string nombre_director ;
    public :
        Director () ; // constructor
        ~ Director () ; // destructor
        void agregar_pelicula ( Peliculas * pelicula ); // agrega pelicula al final de la lista
        void ordenar () ; // ordena la lista
        void calcular_rating_promedio () ;
        void mostrar_peliculas () ;
};

#endif