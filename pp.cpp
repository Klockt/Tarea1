#include <iostream>
#include <fstream>
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
        void colocar_nombre_director( string dir );
        float get_rank();
};


Director::Director(): head(nullptr), curr(nullptr), tail(nullptr), size(0), rating_promedio(0.0){}

Director::~Director() {
    lNodo* i;
    while (head != nullptr) {
        i = head;
        head = head -> sig;
        delete i -> val;
        delete i;
    }

}

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

void Director::ordenar() {
    if (!head || !head->sig) return; // Si la lista está vacía o tiene solo un elemento, no necesita ordenarse.
    
    lNodo* sorted = nullptr; // Lista para almacenar los elementos ordenados.
    
    while (head != nullptr) {
        lNodo* aux = head;
        head = head->sig;

        // Insertar el nodo en la posición correcta en la lista ordenada
        if (!sorted || aux->val->nombre < sorted->val->nombre) {
            aux->sig = sorted;
            sorted = aux;
        } else {
            lNodo* temp = sorted;
            while (temp->sig != nullptr && temp->sig->val->nombre < aux->val->nombre) {
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

void Director::colocar_nombre_director( string director ){
    nombre_director = director;
    return;
}

float Director::get_rank(){
    return rating_promedio;
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
        void insertar_alf( aNodo*& nodo , Director* director, aNodo* &curr);
        Director* buscar_en_arbol(aNodo* nodo , string& dir);
        void delete_recursivo(aNodo* nodo);
        void copia_preOrden(aNodo* original, aNodo* copia);
        void mejores_directores_HELP(aNodo* nodo, int& count, int n );
        void peores_directores_HELP(aNodo* nodo, int& count, int n);
  


};


Arboles::Arboles():root_1(nullptr), root_2(nullptr), curr_1(nullptr), curr_2(nullptr), size_1(0), size_2(0) {}


Arboles::~Arboles(){
    delete_recursivo(root_1);
    delete_recursivo(root_2);
}

void Arboles::delete_recursivo(aNodo* nodo) { //Supongo que la copia del arbol tambien son nodos de listas [dir,x]
     if (nodo){
        delete_recursivo(nodo -> izq);
        delete_recursivo(nodo -> der);
        delete nodo -> val;
        delete nodo;
     }
}

void Arboles::insertar_pelicula( Pelicula * pelicula ){
    Director* dir = buscar_director(pelicula->director);
        if (dir == nullptr) {
            dir = new Director();
            dir -> colocar_nombre_director(pelicula -> director);
            insertar_alf(root_1, dir, curr_1);
        }
        dir->agregar_pelicula(pelicula);
        dir->ordenar();

}

void Arboles::insertar_alf(aNodo*& nodo, Director* director, aNodo* &curr) {
    if (nodo == nullptr) {
        nodo = new aNodo{ director, nullptr, nullptr };
        curr = nodo;
        return;
    }
    
    if (director->get_nombre() < nodo->val->get_nombre()) {
        insertar_alf(nodo->izq, director, nodo->izq);
    } else if (director->get_nombre() > nodo->val->get_nombre()) {
        insertar_alf(nodo->der, director, nodo->der);
    }
}



void Arboles::copiar_arbol(){
    copia_preOrden(root_1, root_2);
}

void Arboles::copia_preOrden(aNodo* original, aNodo* copia){
    if (!original){
        return;
    }
    Director* nDirector = new Director(*original -> val);
    nDirector -> calcular_rating_promedio();
    insertar_alf(copia, nDirector, curr_2);
    copia_preOrden(original->izq, copia);
    copia_preOrden(original->der, copia);
}

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
            return buscar_en_arbol( nodo -> izq , dir );
        }
        else {
            return buscar_en_arbol( nodo -> der, dir);
        }
}

void Arboles::mejores_directores(int n) {
    cout << "Mejores " << n << " directores:" << endl;
    int count = 0;
    mejores_directores_HELP(root_2, count, n);
}

void Arboles::mejores_directores_HELP(aNodo* nodo, int& count, int n) {
    if (!nodo || count >= n){
        cout << count << endl;
     return;
    }
    mejores_directores_HELP(nodo->der, count, n);
    if (count < n) {
        cout << "(" << (count + 1) << ") " << nodo->val->get_nombre() << " - Rating Promedio: " << nodo->val->get_rank() << endl;
        count++;
    }
    mejores_directores_HELP(nodo->izq, count, n);
}

void Arboles::peores_directores(int n) {
    cout << "Peores " << n << " directores:" << endl;
    int count = 0;
    peores_directores_HELP(root_2, count, n);
}

void Arboles::peores_directores_HELP(aNodo* nodo, int& count, int n) {
    if (!nodo || count >= n) return;
    peores_directores_HELP(nodo->izq, count, n);
    if (count < n) {
        cout << "(" << (count + 1) << ") " << nodo->val->get_nombre() << " - Rating Promedio: " << nodo->val->get_rank() << endl;
        count++;
    }
    peores_directores_HELP(nodo->der, count, n);
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


// Estructuras y Clases deben estar definidas en TDAS.cpp
// Aquí solo está el código principal que usa esas estructuras

int main() {
    ifstream archivo("Peliculas.txt");
    if (!archivo) {
        cout << "No se logró encontrar el archivo" << endl;
        return 1;
    }

    Arboles arbol;
    string linea;
    int cant_peliculas;

    // Leer la cantidad de películas
    archivo >> cant_peliculas;
    archivo.ignore();

    // Leer las películas y almacenarlas en el árbol
    for (int i = 0; i < cant_peliculas; i++) {
        getline(archivo, linea);
        int pos1 = linea.find(';'); // Busca el carácter ';' y regresa su posición
        int pos2 = linea.find(';', pos1 + 1); // Busca el carácter ';' justo después del anterior
        
        Pelicula* pelicula = new Pelicula(); // Crea el espacio para Pelicula
        pelicula->nombre = linea.substr(0, pos1); // Obtiene el nombre de la película
        pelicula->director = linea.substr(pos1 + 1, pos2 - pos1 - 1); // Obtiene el nombre del director
        pelicula->rating = stof(linea.substr(pos2 + 1)); // Obtiene el rating

        arbol.insertar_pelicula(pelicula); // Inserta la película en el árbol
    }

    archivo.close();
    
    // Copiar el árbol para ordenarlo por rating promedio
    arbol.copiar_arbol();

    string comando;
    while (true) {
        cout << "> ";
        getline(cin, comando);

        // Buscar películas por director
        if (comando.substr(0, 2) == "sd") {
            string nombre_director = comando.substr(3);
            Director* director = arbol.buscar_director(nombre_director);
            if (director) {
                director->mostrar_peliculas();
            } else {
                cout << "Director no encontrado." << endl;
            }
        }

        // Buscar película específica (si decides implementar la función buscar_pelicula)
        else if (comando.substr(0, 2) == "sm") {
            /*string nombre_pelicula = comando.substr(3);
            Pelicula* pelicula = arbol.buscar_pelicula(nombre_pelicula);
            if (pelicula) {
                cout << pelicula->nombre << " / " << pelicula->director << " / " << pelicula->rating << endl;
            } else {
                cout << "Película no encontrada." << endl;
            }*/
        }

        // Mostrar los mejores directores según el rating promedio
        else if (comando.substr(0, 2) == "br") {
            try {
                int n = stoi(comando.substr(3));
                arbol.mejores_directores(n);
            } catch (const invalid_argument& e) {
                cout << "Comando no válido. Debe seguir el formato: br <n>" << endl;
            }
        }

        // Mostrar los peores directores según el rating promedio
        else if (comando.substr(0, 2) == "wr") {
            try {
                int n = stoi(comando.substr(3));
                arbol.peores_directores(n);
            } catch (const invalid_argument& e) {
                cout << "Comando no válido. Debe seguir el formato: wr <n>" << endl;
            }
        }

        // Terminar la ejecución del programa
        else if (comando.substr(0, 1) == "e") {
            break;
        }

        // Comando no reconocido
        else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0;
}
