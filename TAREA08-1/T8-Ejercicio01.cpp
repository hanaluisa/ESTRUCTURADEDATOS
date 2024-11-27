#include <iostream>
#include <string>

using namespace std;

// Estructura de Nodo para la Cola
struct Nodo {
    string nombre;
    int edad;
    Nodo* siguiente;
};

// Función para insertar en la cola
void insertar(Nodo*& frente, Nodo*& final, string nombre, int edad) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->siguiente = nullptr;

    if (frente == nullptr) { // Si la cola está vacía
        frente = nuevo;
    } else {
        final->siguiente = nuevo;
    }
    final = nuevo;
}

// Función para mostrar la cola
void mostrar(Nodo* frente) {
    if (frente == nullptr) {
        cout << "La cola está vacía.\n";
        return;
    }

    cout << "Personas en la cola:\n";
    Nodo* actual = frente;
    while (actual != nullptr) {
        cout << "Nombre: " << actual->nombre << ", Edad: " << actual->edad << endl;
        actual = actual->siguiente;
    }
}

// Función para liberar memoria de la cola
void liberarCola(Nodo*& frente) {
    while (frente != nullptr) {
        Nodo* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

int main() {
    Nodo* frente = nullptr;
    Nodo* final = nullptr;
    string nombre;
    int edad;

    cout << "Simulación de una cola para personas mayores de 65 años.\n";
    cout << "Introduce los datos de las personas (Edad 0 para finalizar):\n";

    while (true) {
        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Edad: ";
        cin >> edad;
        cin.ignore(); // Limpiar el buffer

        if (edad == 0) {
            break;
        }

        if (edad > 65) {
            insertar(frente, final, nombre, edad);
            cout << "Persona añadida a la cola.\n";
        } else {
            cout << "Edad menor o igual a 65, no se puede añadir a la cola.\n";
        }
    }

    cout << "\nMostrando la cola:\n";
    mostrar(frente);

    // Liberar memoria antes de salir
    liberarCola(frente);

    return 0;
}
