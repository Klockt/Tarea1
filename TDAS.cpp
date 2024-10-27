#include <string>
using namespace std;

struct Pelicula {
    string nombre ;
    string director ;
    float rating ;
};

// Director ----------------------------------------------------------------------------------------------------------------------------

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
        float rating_promedio ;
    public :
        Director () ; // constructor
        ~ Director () ; // destructor
        void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista
        void ordenar () ; // ordena la lista
        void calcular_rating_promedio () ;
        void mostrar_peliculas () ;
        string get_nombre();
};


Director::Director(): head(nullptr), curr(nullptr), tail(nullptr), size(0), rating_promedio(0.0){}

void Director::agregar_pelicula( Pelicula * pelicula ){
        lNodo* nuevo_Nodo = new lNodo;
        nuevo_Nodo->val = pelicula;
        nuevo_Nodo->sig = nullptr;
        if (!head) {
            head = tail = nuevo_Nodo;
        }
        else {
            tail->sig = nuevo_Nodo;
            tail = nuevo_Nodo;
        }
        size++;
}

void Director::ordenar(){
    if (!head || !head->sig) return; // Si la lista está vacía o tiene solo un elemento, no necesita ordenarse.
    lNodo* sorted = nullptr; // Lista para almacenar los elementos ordenados.
    while (head != nullptr) {
        lNodo* aux = head;    // Toma el primer nodo de la lista original.
        head = head->sig;     // Actualiza el head para que apunte al siguiente nodo.
        // Inserta el nodo en la posición correcta en la lista ordenada.
        if (!sorted || aux->val->get_nombre() < sorted->val->get_nombre()) {
            aux->sig = sorted;
            sorted = aux;
        } else {
            lNodo* temp = sorted;
            while (temp->sig != nullptr && temp->sig->val->get_nombre() < aux->val->get_nombre()) {
                temp = temp->sig;
            }
            aux->sig = temp->sig;
            temp->sig = aux;
        }
    }
    head = sorted;
}

void Director::calcular_rating_promedio(){
    if (!head) return;
    float suma_ratings = 0.0;
    int contador = 0;
    lNodo* temp = head;
    while (temp != nullptr) {
        suma_ratings += temp->val->rating; 
        contador++;
        temp = temp->sig; 
    }
    rating_promedio = suma_ratings / contador; 
}

void Director::mostrar_peliculas(){
    lNodo* temp = head;
    while(temp != nullptr){
        cout << temp->val->nombre << " ";
        temp = temp->sig;
    }
    cout << endl;
}

string Director::get_nombre(){
    return nombre_director;
}
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Arbol ----------------------------------------------------------------------------------------------------------------------------

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
        void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
        Director * buscar_director ( string director ); // retorna arreglo de p
        void mejores_directores ( int n); // Muestra por pantalla los mejores n directores .
        //Enumerando de 1 a n.
        void peores_directores ( int n ); // Muestra por pantalla los peores n directores .
        //Enumerando desde m ( cantidad de directores ) hasta m-n.
        void insertar_alf( aNodo* nodo , Director* director);
        Director* buscar_en_arbol(aNodo* nodo , string& dir)
};


Arboles::Arboles():root_1(nullptr), root_2(nullptr), curr_1(nullptr), curr_2(nullptr), size_1(0), size_2(0) {}


Arboles::~Arboles(){}

void Arboles::insertar_pelicula( Pelicula * pelicula ){
    Director* dir = buscar_director(pelicula->director);
        if (!dir) {
            dir = new Director();
            dir -> nombre_director = pelicula -> director;
            insertar_alf( root_1, dir);
        }
        dir->agregar_pelicula(pelicula);
        dir->ordenar();

}

void Arboles::insertar_alf( aNodo* nodo , Director* director) { // Inserta los nodos dentro del  arbol 1 alfabeticamente en in-orden
    if (!nodo){
        return nullptr;
    }
    if ( director -> get_nombre() < nodo -> val -> get_nombre() ){
        insertar_alf ( nodo -> izq , director);
    }
    if ( director -> get_nombre() > nodo -> val -> get_nombre() ){
            insertar_alf ( nodo -> der , director );
    }
}


void Arboles::copiar_arbol(){}

Director * Arboles::buscar_director( string director ){ //no entendi el arreglo de p
    return buscar_en_arbol(root_1, director);
}

Director* Arboles::buscar_en_arbol(aNodo* nodo , string& dir) {
        if ( nodo == nullptr){
            return nullptr;
        }
        if ( dir == nodo -> val -> get_nombre()) {
            return nodo -> val;
        }
        if ( dir < nodo -> val -> get_nombre() ) {
            return buscar_en_arbol( nodo -> izq , dir )
        }
        else {
            return buscar_en_arbol( nodo -> der, dir)
        }
}

void Arboles::mejores_directores( int n ){

}

void Arboles::peores_directores( int n ){
    
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
