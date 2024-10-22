#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;

void transponerMatriz(int** matriz, int filas, int columnas) {
    // Crear la matriz transpuesta
    int** matrizTranspuesta = new int*[columnas];
    for (int i = 0; i < columnas; i++) {
        matrizTranspuesta[i] = new int[filas];
    }

    // Transposición
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizTranspuesta[j][i] = matriz[i][j];
        }
    }

    // Imprimir la matriz transpuesta
    cout << "Matriz transpuesta:" << endl;
    for (int i = 0; i < columnas; i++) {
        for (int j = 0; j < filas; j++) {
            cout << matrizTranspuesta[i][j] << " ";
        }
        cout << endl;
    }

    // Liberar la memoria de la matriz transpuesta
    for (int i = 0; i < columnas; i++) {
        delete[] matrizTranspuesta[i];
    }
    delete[] matrizTranspuesta;
}

int main() {
    int filas, columnas;
    int max_num_random = 11;

    cout << "Introduce el número de filas: ";
    cin >> filas;
    cout << "Introduce el número de columnas: ";
    cin >> columnas;

    // Crear la matriz se usan punteros
    // int** matriz declara un puntero bidireccional
    // new es palabra reservada para el uso de memoria en tiempo de ejecución 
    // int*[filas] hace referencia a un puntero unidereccional
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    // Inicializar el generador de números aleatorios con la semilla basada en el tiempo actual
    srand(time(0));

    // Llenar la matriz con valores aleatorios entre 0 y 10
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = rand() % max_num_random;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    // Llamar a la función para transponer la matriz
    transponerMatriz(matriz, filas, columnas);

    // Liberar la memoria de la matriz original
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
