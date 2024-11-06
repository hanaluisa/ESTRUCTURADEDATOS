#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>  //Para usar ceil metodo que ayuda a redondear valores
#include <ctime> // Para usar time()
using namespace std;

struct PersonaNacida {
    string identificacion;
    string lugarNacimiento;
    double pesoNacimiento;
    double tallaNacimiento;
    char genero;
    int edadMadre;
};

void ingresarDatosPersona(PersonaNacida &persona) {
    long long identificacion = rand() % 10000000000LL;
    persona.identificacion = to_string(identificacion);
    persona.lugarNacimiento = (rand() % 3) == 0 ? "GYE" : (rand() % 2 == 0 ? "UIO" : "CUE");
    persona.pesoNacimiento = (rand() % (4500 - 2500 + 1) + 2500) / 1000.0;
    persona.tallaNacimiento = rand() % (55 - 45 + 1) + 45;
    persona.genero = (rand() % 2) == 0 ? 'F' : 'M';
    persona.edadMadre = rand() % (40 - 18 + 1) + 18;
}

void mostrarDatosPersona(const PersonaNacida &persona) {
    cout << persona.identificacion << ", ";
    cout << persona.lugarNacimiento << ", ";
    cout << persona.pesoNacimiento << ", ";
    cout << persona.tallaNacimiento << ", ";
    cout << persona.genero << ", ";
    cout << persona.edadMadre << endl;
}

int validarCantidadNacidos() {
    int cantidadPersonas = 0; 
    bool flag = false;

    while (!flag) {
        cout << "Ingresa la cantidad de personas nacidas vivas (mínimo 20): ";
        cin >> cantidadPersonas;
        if (cantidadPersonas >= 20) {
            flag = true;
        } else {
            cout << "Debe ser de al menos 20 nacidos vivos." << endl;
        }
    }

    return cantidadPersonas;
}

int main() {
    // inicializa generador de números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    int cantidadPersonas = validarCantidadNacidos();
    double pesoSuma = 0;
    double tallaSuma = 0;
    double edadMadre = 0;

    PersonaNacida *ArrPersonasNacidas = new PersonaNacida[cantidadPersonas];

    for (int i = 0; i < cantidadPersonas; i++) {
        ingresarDatosPersona(ArrPersonasNacidas[i]);
    }

    cout << "\nDatos de las personas nacidas vivas:" << endl;
    for (int i = 0; i < cantidadPersonas; i++) {
        mostrarDatosPersona(ArrPersonasNacidas[i]);
        pesoSuma += ArrPersonasNacidas[i].pesoNacimiento;
        tallaSuma += ArrPersonasNacidas[i].tallaNacimiento;
        edadMadre += ArrPersonasNacidas[i].edadMadre;
    }

    cout << endl;
    cout << "El peso promedio de los nacimientos es: " << pesoSuma / cantidadPersonas << " kg" << endl;
    cout << "La talla promedio de los nacimientos es: " << tallaSuma / cantidadPersonas << " cm" << endl;
    cout << "La edad promedio de la madre es: " << ceil(edadMadre / cantidadPersonas)<< " años" << endl;

    delete[] ArrPersonasNacidas;
    return 0;
}