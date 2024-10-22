#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

int main() {
    int tamanio;
    int max_num_random = 100;

    // Solicitar al usuario el tamaño del vector
    cout << "Introduce el tamaño del vector: ";
    cin >> tamanio;

    // Crear un vector dinámico
    int* vector = new int[tamanio];

    srand(time(0));

    // Generar elementos del vector aleatorios
    cout << "Elementos del vector:" << endl;
    for (int i = 0; i < tamanio; i++) {
        vector[i] = rand() % max_num_random;
        cout << vector[i] << " ";
    }

    // Inicializar el menor valor par a -1 (o a un número impar)
    int menorPar = -1; 
    bool hayPares = false; // Variable para verificar si hay números pares

    // Buscar el menor valor par en el vector
    for (int i = 0; i < tamanio; i++) {
        if (vector[i] % 2 == 0) { // Verificar si el número es par
            if (vector[i] < menorPar) {
                menorPar = vector[i]; // Actualizar menor valor par
                hayPares = true; // Encontró al menos un par
            }
        }
    }

    // Mostrar el resultado
    if (hayPares) {
        cout << "\nEl menor valor par del vector es: " << menorPar << endl;
    } else {
        cout << "\nNo se encontraron valores pares en el vector." << endl;
    }

    // Liberar la memoria
    delete[] vector;

    return 0;
}
