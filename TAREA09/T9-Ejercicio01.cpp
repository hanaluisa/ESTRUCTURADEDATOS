#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// estructura nodo horizontal para las líneas
struct NodoHorizontalLineas {
    string letra;
    NodoHorizontalLineas* siguiente;
};

// estructura nodo vertical para las canciones
struct NodoVerticalCanciones {
    string titulo;
    NodoHorizontalLineas* lineas;   // agregar líneas a la canción
    NodoVerticalCanciones* siguiente; 
};

// crear un nodo vertical
NodoVerticalCanciones* crearNodoVerticalCanciones(const string& titulo) {
    NodoVerticalCanciones* nuevo = new NodoVerticalCanciones();
    nuevo->titulo = titulo;
    nuevo->lineas = nullptr;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// crea un nodo horizontal
NodoHorizontalLineas* crearNodoHorizontalLineas(const string& letra) {
    NodoHorizontalLineas* nuevo = new NodoHorizontalLineas();
    nuevo->letra = letra;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// agrega una línea a una canción
void agregarLinea(NodoVerticalCanciones* cancion, const string& letra) {
    NodoHorizontalLineas* nuevaLinea = crearNodoHorizontalLineas(letra);
    if (cancion->lineas == nullptr) {
        cancion->lineas = nuevaLinea;
    } else {
        NodoHorizontalLineas* temp = cancion->lineas;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevaLinea;
    }
}

// imprime canciones y líneas
void mostrarCanciones(NodoVerticalCanciones* inicio) {
    NodoVerticalCanciones* temp = inicio;
    while (temp != nullptr) {
        cout << temp->titulo << endl;
        NodoHorizontalLineas* linea = temp->lineas;
        while (linea != nullptr) {
            cout << "  " << linea->letra << endl;
            linea = linea->siguiente;
        }
        temp = temp->siguiente;
        cout << endl;
    }
}

// guardar canciones en un archivo
void guardarEnArchivo(NodoVerticalCanciones* inicio, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar" << endl;
        return;
    }

    NodoVerticalCanciones* temp = inicio;
    while (temp != nullptr) {
        archivo << temp->titulo << endl;
        NodoHorizontalLineas* linea = temp->lineas;
        while (linea != nullptr) {
            archivo << linea->letra << endl;
            linea = linea->siguiente;
        }
        archivo << endl; // Separar canciones con una línea vacía
        temp = temp->siguiente;
    }

    archivo.close();
    cout << "Canciones guardadas en el archivo: " << nombreArchivo << endl;
}

int main() {
    NodoVerticalCanciones* inicio = nullptr; // Inicio de la lista vertical
    NodoVerticalCanciones* actual = nullptr;

    int opcion;
    do {
        cout << "1. Agregar canción" << endl;
        cout << "2. Mostrar canciones" << endl;
        cout << "3. Guardar en archivo" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer de entrada

        if (opcion == 1) {
            cout << "Ingrese el título de la canción: ";
            string titulo;
            getline(cin, titulo);

            NodoVerticalCanciones* nuevaCancion = crearNodoVerticalCanciones("Cancion: " + titulo);
            if (inicio == nullptr) {
                inicio = nuevaCancion;
            } else {
                actual->siguiente = nuevaCancion;
            }
            actual = nuevaCancion;

            cout << "Ingrese las líneas de la canción (escriba 'fin' para terminar):" << endl;
            string linea;
            while (true) {
                getline(cin, linea);
                if (linea == "fin") break;
                agregarLinea(actual, "linea: " + linea);
            }
        } else if (opcion == 2) {
            cout << "Canciones actuales:" << endl;
            mostrarCanciones(inicio);
        } else if (opcion == 3) {
            string nombreArchivo = "Archivo_nuevo.txt";
            guardarEnArchivo(inicio, nombreArchivo);
        }
    } while (opcion != 4);

    cout << "Programa finalizado." << endl;
    return 0;
}
