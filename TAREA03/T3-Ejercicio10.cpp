#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time(), que se usará para inicializar srand()
using namespace std;

int main() {
    int dimension;
    int maxNumRandom = 9; 
    // Solicitar al usuario el tamaño de la matriz (n x n)
    cout << "Introduce el tamaño de la matriz (n para n x n): ";
    cin >> dimension;

    // Crear una matriz dinámica
    int** matriz = new int*[dimension];
    for (int i = 0; i < dimension; i++) {
        matriz[i] = new int[dimension];
    }

    srand(time(0));

    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    cout << "Matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz[i][j] = rand() % maxNumRandom;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    // Sumar los elementos pares de la diagonal
    int sumaPares = 0;

    for (int i = 0; i < dimension; i++) {
        if (matriz[i][i] % 2 == 0) { // Verificar si el elemento de la diagonal es par
            sumaPares += matriz[i][i];
        }
    }

    // Mostrar el resultado
    cout << "\nLa suma de los elementos pares de la diagonal es: " << sumaPares << endl;

    // Liberar la memoria
    for (int i = 0; i < dimension; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
