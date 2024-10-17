class Arboles {
private :
struct aNodo {
Director * val ;
aNodo * izq ;
aNodo * der ;
};
aNodo * root_1 ; // raiz arbol ordenado por directores
aNodo * curr_1 ;
size_t size_1 ;
aNodo * root_2 ; // raiz arbol ordenado por rating
aNodo * curr_2 ;
size_t size_2 ;
public :
Arboles () ; // constructor
~ Arboles () ; // destructor
void insertar_pelicula ( Pelicula * pelicula );
void copiar_arbol () // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
Director * buscar_director ( string director ); // retorna arreglo de p
void mejores_directores ( int n); // Muestra por pantalla los mejores n directores .
//Enumerando de 1 a n.
void peores_directores ( int n ); // Muestra por pantalla los peores n directores .
//Enumerando desde m ( cantidad de directores ) hasta m-n.
}