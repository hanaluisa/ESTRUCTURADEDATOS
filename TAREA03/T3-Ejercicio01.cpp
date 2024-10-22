#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time(), que se usará para inicializar srand()
using namespace std;


int main() {
    int dimension;
    int max_num_random = 4;
    cout << "Introduce el tamaño de la matriz (para filas y columnas): ";
    cin >> dimension;

    // Declarar las matrices cuadradas
    int matriz1[dimension][dimension], matriz2[dimension][dimension], resultado[dimension][dimension];
    
    // Inicializar el generador de números aleatorios con la semilla basada en el tiempo actual
    srand(time(0));

    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    cout << "Primera matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz1[i][j] = rand() % max_num_random;
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }
    
    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    cout << "Segunda matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz2[i][j] = rand() % max_num_random;
            cout << matriz2[i][j] << " ";
        }
        cout << endl;
    }
    
    // Inicializar la matriz resultado con ceros
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            resultado[i][j] = 0;
        }
    }
    
    // Multiplicar las matrices
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // K cumple con una regla importante - recorrer y y x en la posicionm de i y j de la nueva matriz
            for (int k = 0; k < dimension; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
    
    // Mostrar la matriz resultante
    cout << "Resultado de la multiplicación de matrices:" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            cout << resultado[i][j] << "  ";
        }
        cout << endl;
    }
    
    return 0;
}
