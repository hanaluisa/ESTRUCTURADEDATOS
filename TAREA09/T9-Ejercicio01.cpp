#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// estructura nodo horizontal para las líneas
struct NodoHorizontalMaterias  {
    string materia;
    NodoHorizontalMaterias * siguiente;
};

// estructura nodo vertical para las cursoes
struct NodoVerticalMaterias  {
    string curso;
    NodoHorizontalMaterias * materias;   // agregar líneas a la canción
    NodoVerticalMaterias * siguiente; 
};

// crear un nodo vertical
NodoVerticalMaterias * crearNodoVerticalMaterias (const string& curso) {
    NodoVerticalMaterias * nuevo = new NodoVerticalMaterias ();
    nuevo->curso = curso;
    nuevo->materias = nullptr;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// crea un nodo horizontal
NodoHorizontalMaterias * crearNodoHorizontalMaterias (const string& materia) {
    NodoHorizontalMaterias * nuevo = new NodoHorizontalMaterias ();
    nuevo->materia = materia;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// agrega una materia a un curso
void agregarMateria(NodoVerticalMaterias * curso, const string& materia) {
    NodoHorizontalMaterias * nuevaLinea = crearNodoHorizontalMaterias (materia);
    if (curso->materias == nullptr) {
        curso->materias = nuevaLinea;
    } else {
        NodoHorizontalMaterias * temp = curso->materias;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevaLinea;
    }
}

// imprime cursoes y líneas
void mostrar(NodoVerticalMaterias * inicio) {
    NodoVerticalMaterias * temp = inicio;
    while (temp != nullptr) {
        cout << temp->curso << endl;
        NodoHorizontalMaterias * linea = temp->materias;
        while (linea != nullptr) {
            cout << "  " << linea->materia << endl;
            linea = linea->siguiente;
        }
        temp = temp->siguiente;
        cout << endl;
    }
}

// guardar cursoes en un archivo
void guardarEnArchivo(NodoVerticalMaterias * inicio, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar" << endl;
        return;
    }

    NodoVerticalMaterias * temp = inicio;
    while (temp != nullptr) {
        archivo << temp->curso << endl;
        NodoHorizontalMaterias * linea = temp->materias;
        while (linea != nullptr) {
            archivo << linea->materia << endl;
            linea = linea->siguiente;
        }
        archivo << endl; // Separar cursoes con una línea vacía
        temp = temp->siguiente;
    }

    archivo.close();
    cout << "Cursos guardados en el archivo: " << nombreArchivo << endl;
}

int main() {
    NodoVerticalMaterias * inicio = nullptr; // Inicio de la lista vertical
    NodoVerticalMaterias * actual = nullptr;

    int opcion;
    do {
        cout << "Ingrese el curso: ";
        string curso;
        getline(cin, curso);

        NodoVerticalMaterias * nuevaMateria = crearNodoVerticalMaterias ("Materia: " + curso);
        if (inicio == nullptr) {
            inicio = nuevaMateria;
        } else {
            actual->siguiente = nuevaMateria;
        }
        actual = nuevaMateria;

        cout << "Ingrese las materias (escriba 'fin' para terminar):" << endl;
        string linea;
        while (true) {
            getline(cin, linea);
            if (linea == "fin") break;
            agregarMateria(actual, "Materia: " + linea);
        }
        cout << "Registros actuales:" << endl;
        mostrar(inicio);
        string nombreArchivo = "Archivo_nuevo.txt";
        guardarEnArchivo(inicio, nombreArchivo);
        int continuar;
        
        do {
            cout << "Salir (0)" << endl;
            cout << "Continuar (1)" << endl;
            cin >> continuar;
            cin.ignore();
            if (continuar != 0 && continuar != 1) {
                cout << "Valor inválido. Por favor, introduzca 0 o 1." << endl;
            }
        } while (continuar != 0 && continuar != 1);

        opcion = continuar;
    } while (opcion != 0);

    cout << "Programa finalizado." << endl;
    return 0;
}
