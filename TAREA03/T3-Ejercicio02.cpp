#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time(), que se usará para inicializar srand()
#include <algorithm>   // Para sort()
using namespace std;


int main() {
    int dimension;
    int arreglo_tamanio = 0;
    int max_num_random = 100;
    cout << "Introduce el tamaño de la matriz (para filas y columnas): ";
    cin >> dimension;

    // Declarar las matrices cuadradas
    int matriz1[dimension][dimension], resultado[dimension][dimension];
    int array_aux[dimension * dimension];
    
    // Inicializar el generador de números aleatorios con la semilla basada en el tiempo actual
    srand(time(0));


    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    cout << "Matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz1[i][j] = rand() % max_num_random;
            array_aux[arreglo_tamanio] = matriz1[i][j];
            cout << matriz1[i][j] << " ";
            arreglo_tamanio++; 
        }
        cout << endl;
    }

    // Inicializar la matriz resultado con ceros
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            resultado[i][j] = 0;
        }
    }

    // Metodo de ordenamiento viene de la biblioteca <algorithm> de mayor a menor
    // sort(array_aux, array_aux + dimension * dimension, greater<int>());
    // Metodo de ordenamiento viene de la biblioteca <algorithm> de menor a mayor
    sort(array_aux, array_aux + dimension * dimension);


    // Asignar valores a la matriz resultado tomando en cuenta los valores de dimension
    // Imprimir valores de resultado 
    cout << "\nMatriz (valores ordenados):" << endl;
    int index = 0;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            resultado[i][j] = array_aux[index++];
            cout << resultado[i][j] << " ";
        }
        cout << endl;
    }

    return 0;     
}