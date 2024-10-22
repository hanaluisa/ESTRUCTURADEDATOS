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
    double* vector = new double[tamanio];

    srand(time(0));

    // Generar elementos del vector aleatorios
    cout << "Elementos del vector:" << endl;
    for (int i = 0; i < tamanio; i++) {
        vector[i] = rand() % max_num_random;
        cout << vector[i] << " ";
    }

    // Calcular la suma de los elementos
    double suma = 0.0;
    for (int i = 0; i < tamanio; i++) {
        suma += vector[i];
    }

    // Calcular el promedio
    double promedio = suma / tamanio;

    // Mostrar el resultado
    cout << "\nEl valor promedio de los elementos del vector es: " << promedio << endl;

    // Liberar la memoria
    delete[] vector;

    return 0;
}
