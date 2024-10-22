#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time(), que se usará para inicializar srand()
using namespace std;


int main() {
    int dimension;
    int max_num_random = 20;
    cout << "Introduce el tamaño de la matriz (para filas y columnas): ";
    cin >> dimension;

    // Declarar las matrices cuadradas
    int matriz1[dimension][dimension];
    
    // Inicializar el generador de números aleatorios con la semilla basada en el tiempo actual
    srand(time(0));


    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    // Calcular promedio
    double suma = 0.0;
    cout << "Matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz1[i][j] = rand() % max_num_random;
            suma += matriz1[i][j];
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }

    // Calcular el promedio
    double promedio = suma / (dimension * dimension);

    // Mostrar el resultado
    cout << "\nEl valor promedio de los elementos del vector es: " << promedio << endl;

    return 0;
}