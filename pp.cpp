#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Pelicula {
    string nombre;
    string director;
    float rating;
};

// Director ----------------------------------------------------------------------------------------------------------------------------

class Director {
private:
    struct lNodo {
        Pelicula* val;
        lNodo* sig;
    };

    lNodo* head;
    lNodo* tail;
    size_t size;
    string nombre_director;
    float rating_promedio;

public:
    Director();
    ~Director();
    void agregar_pelicula(Pelicula* pelicula);
    void ordenar();
    void calcular_rating_promedio();
    void mostrar_peliculas();
    string get_nombre();
    void colocar_nombre_director(string dir);
    float get_rank();
    Pelicula* buscar_pelicula(const string& nombre_pelicula);
};

void Director::mostrar_peliculas() {
    if (!head) {
        cout << "No hay películas disponibles para este director." << endl;
        return;
    }

    lNodo* temp = head;
    while (temp != nullptr) {
        cout << "Película: " << temp->val->nombre << " / Rating: " << temp->val->rating << endl;
        temp = temp->sig;
    }
}

Director::Director() : head(nullptr), tail(nullptr), size(0), rating_promedio(0.0) {}

Director::~Director() {
    lNodo* i;
    while (head != nullptr) {
        i = head;
        head = head->sig;
        delete i->val; // Destruir la película
        delete i; // Destruir el nodo
    }
}

void Director::agregar_pelicula(Pelicula* pelicula) {
    lNodo* nuevo_Nodo = new lNodo;
    nuevo_Nodo->val = pelicula;
    nuevo_Nodo->sig = nullptr;
    
    if (!head) {
        head = tail = nuevo_Nodo;
    } else {
        tail->sig = nuevo_Nodo;
        tail = nuevo_Nodo;
    }
    size++;
    calcular_rating_promedio(); // Actualizar rating promedio al agregar una película
}

void Director::ordenar() {
    if (!head || !head->sig) return;

    lNodo* sorted = nullptr;

    while (head != nullptr) {
        lNodo* aux = head;
        head = head->sig;

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

void Director::calcular_rating_promedio() {
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

string Director::get_nombre() {
    return nombre_director;
}

void Director::colocar_nombre_director(string director) {
    nombre_director = director;
}

float Director::get_rank() {
    return rating_promedio;
}

Pelicula* Director::buscar_pelicula(const string& nombre_pelicula) {
    lNodo* temp = head;
    while (temp != nullptr) {
        if (temp->val->nombre == nombre_pelicula) {
            return temp->val;
        }
        temp = temp->sig;
    }
    return nullptr;
}

// Arbol ----------------------------------------------------------------------------------------------------------------------------

class Arboles {
private:
    struct aNodo {
        Director* val;
        aNodo* izq;
        aNodo* der;
    };

    aNodo* root_1; // raiz arbol ordenado por directores
    aNodo* root_2; // raiz arbol ordenado por rating
    size_t size_1;
    size_t size_2;

public:
    Arboles();
    ~Arboles();
    void insertar_pelicula(Pelicula* pelicula);
    void copiar_arbol();
    Director* buscar_director(string director);
    void mejores_directores(int n);
    void peores_directores(int n);

private:
    void insertar_alf(aNodo*& nodo, Director* director);
    Director* buscar_en_arbol(aNodo* nodo, string& dir);
    void delete_recursivo(aNodo* nodo);
    void copia_preOrden(aNodo* original, aNodo* copia);
    void mejores_directores_HELP(aNodo* nodo, int& count, int n);
    void peores_directores_HELP(aNodo* nodo, int& count, int n);
};

Arboles::Arboles() : root_1(nullptr), root_2(nullptr), size_1(0), size_2(0) {}

Arboles::~Arboles() {
    delete_recursivo(root_1);
    delete_recursivo(root_2);
}

void Arboles::delete_recursivo(aNodo* nodo) {
    if (nodo) {
        delete_recursivo(nodo->izq);
        delete_recursivo(nodo->der);
        delete nodo->val; // Destruir el director
        delete nodo; // Destruir el nodo
    }
}

void Arboles::insertar_pelicula(Pelicula* pelicula) {
    Director* dir = buscar_director(pelicula->director);
    if (dir == nullptr) {
        dir = new Director();
        dir->colocar_nombre_director(pelicula->director);
        insertar_alf(root_1, dir);
    }
    dir->agregar_pelicula(pelicula);
    dir->ordenar();
}

void Arboles::insertar_alf(aNodo*& nodo, Director* director) {
    if (nodo == nullptr) {
        nodo = new aNodo{ director, nullptr, nullptr };
        return;
    }

    if (director->get_nombre() < nodo->val->get_nombre()) {
        insertar_alf(nodo->izq, director);
    } else if (director->get_nombre() > nodo->val->get_nombre()) {
        insertar_alf(nodo->der, director);
    }
}

void Arboles::copiar_arbol() {
    copia_preOrden(root_1, root_2);
}

void Arboles::copia_preOrden(aNodo* original, aNodo* copia) {
    if (!original) return;

    Director* nDirector = new Director(*original->val);
    nDirector->calcular_rating_promedio();
    insertar_alf(copia, nDirector);

    copia_preOrden(original->izq, copia);
    copia_preOrden(original->der, copia);
}

Director* Arboles::buscar_director(string director) {
    return buscar_en_arbol(root_1, director);
}

Director* Arboles::buscar_en_arbol(aNodo* nodo, string& dir) {
    if (nodo == nullptr) return nullptr;
    if (dir == nodo->val->get_nombre()) return nodo->val;
    if (dir < nodo->val->get_nombre()) return buscar_en_arbol(nodo->izq, dir);
    return buscar_en_arbol(nodo->der, dir);
}

void Arboles::mejores_directores(int n) {
    cout << "Mejores " << n << " directores:" << endl;
    int count = 0;
    mejores_directores_HELP(root_2, count, n);
}

void Arboles::mejores_directores_HELP(aNodo* nodo, int& count, int n) {
    if (!nodo || count >= n) return;

    mejores_directores_HELP(nodo->der, count, n);
    if (count < n) {
        cout << "(" << (count + 1) << ") " << nodo->val->get_nombre() << " - Rating Promedio: " << nodo->val->get_rank() << endl;
        count++;
    }
    mejores_directores_HELP(nodo->izq, count , n);
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

int main() {
    ifstream archivo("Peliculas.txt");
    if (!archivo) {
        cout << "No se logró encontrar el archivo" << endl;
        return 1;
    }

    Arboles arbol;
    string linea;
    int cant_peliculas;

    archivo >> cant_peliculas;
    archivo.ignore();

    for (int i = 0; i < cant_peliculas; i++) {
        getline(archivo, linea);
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);

        Pelicula* pelicula = new Pelicula();
        pelicula->nombre = linea.substr(0, pos1);
        pelicula->director = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        pelicula->rating = stof(linea.substr(pos2 + 1));

        arbol.insertar_pelicula(pelicula);
    }

    archivo.close();

    arbol.copiar_arbol();

    string comando;
    while (true) {
        cout << "> ";
        getline(cin, comando);

        if (comando.substr(0, 2) == "sd") {
            string nombre_director = comando.substr(3);
            Director* director = arbol.buscar_director(nombre_director);
            if (director) {
                director->mostrar_peliculas();
            } else {
                cout << "Director no encontrado." << endl;
            }
        } else if (comando.substr(0, 2) == "br") {
            try {
                int n = stoi(comando.substr(3));
                arbol.mejores_directores(n);
            } catch (const invalid_argument& e) {
                cout << "Comando no válido. Debe seguir el formato: br <n>" << endl;
            }
        } else if (comando.substr(0, 2) == "wr") {
            try {
                int n = stoi(comando.substr(3));
                arbol.peores_directores(n);
            } catch (const invalid_argument& e) {
                cout << "Comando no válido. Debe seguir el formato: wr <n>" << endl;
            }
        } else if (comando.substr(0, 1) == "e") {
            break;
        } else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0;
}