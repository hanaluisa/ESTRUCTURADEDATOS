#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time(), que se usará para inicializar srand()
using namespace std;


int main() {
    int dimension;
    int maxNumRandom = 100;
    cout << "Introduce el tamaño de la matriz (para filas y columnas): ";
    cin >> dimension;

    // Declarar las matrices cuadradas
    int matriz1[dimension][dimension];
    
    // Inicializar el generador de números aleatorios con la semilla basada en el tiempo actual
    srand(time(0));

    // Inicializar el menor valor par a -1 (o a un número impar)
    int menorImPar = -1; 
    bool hayImPares = false; // Variable para verificar si hay números pares

    // Llenar matriz con números aleatorios -> Mejora con memoria dinámica
    cout << "Primera matriz (valores aleatorios):" << endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matriz1[i][j] = rand() % maxNumRandom;
            cout << matriz1[i][j] << " ";
            if (matriz1[i][j] % 2 != 0) {
                if (menorImPar == -1 || matriz1[i][j] < menorImPar) {
                    menorImPar = matriz1[i][j]; // Actualizar menor valor impar
                    hayImPares = true; // Encontró al menos un impar
                }
            }

        }
        cout << endl;
    }

    // Mostrar el resultado
    if (hayImPares) {
        cout << "\nEl menor valor impar del vector es: " << menorImPar << endl;
    } else {
        cout << "\nNo se encontraron valores impares en el vector." << endl;
    }
    return 0; 
}