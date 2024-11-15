#include <iostream>
#include <iomanip> // Para setw
using namespace std;

int main() {
    
    int height;
    
    bool flag = false;
    while (flag == false) {
        cout << "Ingrese la altura del triángulo de Pascal: ";
        cin >> height;
        if (height > 0 and height <= 20) {
            flag = true;
        }  else {
            cout << "Altura inválida. Tiene que se entre 0 y 20."<<endl;
        }
    }   

    int array[height][height];

    // inicializa todos los items en 0 para evitar valores basura
    int i = 0;
    while (i < height) {
        int j = 0;
        while (j < height) {
            array[i][j] = 0;
            j++;
        }
        i++;
    }

    // genera el triángulo de Pascal
    i = 0;
    while (i < height) {
        array[i][0] = 1; // el primer item de cada fila es 1
        int j = 1;
        while (j <= i) {
            // el resultado va a ser la suma de los dos items de arriba
            array[i][j] = array[i - 1][j - 1] + array[i - 1][j];
            j++;
        }
        i++;
    }

    // imprimir triángulo de Pascal
    i = 0;
    while (i < height) {
        cout << setw((height - i) * 2); // Ajusta el espaciado
        int j = 0;
        while (j <= i) {
            cout << array[i][j] << "   ";
            j++;
        }
        cout << endl;
        i++;
    }

    return 0;
}
