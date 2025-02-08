#include <iostream>
using namespace std;

// Definición de un nodo del árbol binario

struct Nodo {
    int valor; // Valor del nodo
    Nodo* izquierdo; // Valor del nodo
    Nodo* derecho; // Puntero al nodo derecho

    // Declara el constructor de la clase Nodo Recibe un parámetro int v 
    // valor(v) Esto se llama lista de inicialización de miembros,
    // Inicializa directamente el atributo valor con el valor de v

    //También inicializa los punteros izquierdo y derecho a nullptr (nulo).

    // El cuerpo del constructor. En este caso, está vacío 
    // porque toda la inicialización se realiza en la lista de inicialización de miembros.
    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

// Función para insertar un valor en el Árbol Binario de Búsqueda (ABB)
Nodo* insertar(Nodo* raiz, int valor) {

    // Si raiz es nullptr, significa que se ha llegado a una posición vacía en el árbol 
    // donde se puede insertar un nuevo nodo.
    if (raiz == nullptr) {
        return new Nodo(valor);
    }
    // Si el valor es menor que el valor almacenado en el nodo actual (raiz->valor), 
    // se llama recursivamente a la función para insertar el valor en el subárbol izquierdo (raiz->izquierdo).
    if (valor < raiz->valor) {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    } else {
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    return raiz;
}

// Recorrido en Preorden: Raíz, Izquierdo, Derecho
void preorden(Nodo* raiz) {
    if (raiz != nullptr) {
        cout << raiz->valor << " "; // Primero, se visita la raíz
        preorden(raiz->izquierdo); // Luego, se recorre el subárbol izquierdo
        preorden(raiz->derecho); // Finalmente, se recorre el subárbol derecho
    }
}

// Recorrido en Inorden: Izquierdo, Raíz, Derecho
void inorden(Nodo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierdo); // Primero, se recorre el subárbol izquierdo
        cout << raiz->valor << " "; // Luego, se visita la raíz
        inorden(raiz->derecho); // Finalmente, se recorre el subárbol derecho
    }
}

// Recorrido en Postorden: Izquierdo, Derecho, Raíz
void postorden(Nodo* raiz) {
    if (raiz != nullptr) {
        postorden(raiz->izquierdo); // Primero, se recorre el subárbol izquierdo
        postorden(raiz->derecho); // Luego, se recorre el subárbol derecho
        cout << raiz->valor << " "; // Luego, se recorre el subárbol derecho
    }
}

// Búsqueda en un Árbol Binario de Búsqueda.
bool buscar(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        return false;
    }
    if (raiz->valor == valor) {
        return true;
    }
    // Si el valor a buscar es menor que raiz procede a buscar por el lado izquierdo.
    if (valor < raiz->valor) {
        return buscar(raiz->izquierdo, valor);
    } else {
        return buscar(raiz->derecho, valor);
    }
}

// Función principal
int main() {
    Nodo* raiz = nullptr;

    // Insertar valores en el árbol
    raiz = insertar(raiz, 8);
    insertar(raiz, 3); 
    insertar(raiz, 10);
    insertar(raiz, 1);
    insertar(raiz, 6);
    insertar(raiz, 14);
    insertar(raiz, 4);
    insertar(raiz, 7);
    insertar(raiz, 13);

    // Mostrar recorridos
    cout << "Recorrido en Preorden: ";
    preorden(raiz);
    cout << endl;

    cout << "Recorrido en Inorden: ";
    inorden(raiz);
    cout << endl;

    cout << "Recorrido en Postorden: ";
    postorden(raiz);
    cout << endl;

    // Buscar un valor
    int valorABuscar = 100;
    if (buscar(raiz, valorABuscar)) {
        cout << "El valor " << valorABuscar << " se encuentra en el árbol." << endl;
    } else {
        cout << "El valor " << valorABuscar << " no se encuentra en el árbol." << endl;
    }
    return 0;
}