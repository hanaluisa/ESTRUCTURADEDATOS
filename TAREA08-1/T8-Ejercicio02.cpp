#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

struct Persona {
    std::string nombre;
    std::string fechaNacimiento; // Formato YYYY-MM-DD
    Persona* siguiente;
};

// Cola implementada con punteros enlazados
struct Cola {
    Persona* frente;
    Persona* final;

    Cola() : frente(nullptr), final(nullptr) {}

    void encolar(const std::string& nombre, const std::string& fechaNacimiento) {
        Persona* nuevaPersona = new Persona;
        nuevaPersona->nombre = nombre;
        nuevaPersona->fechaNacimiento = fechaNacimiento;
        nuevaPersona->siguiente = nullptr;

        if (final) {
            final->siguiente = nuevaPersona;
        } else {
            frente = nuevaPersona;
        }
        final = nuevaPersona;
    }

    void desencolar() {
        if (frente) {
            Persona* temp = frente;
            frente = frente->siguiente;
            if (!frente) {
                final = nullptr;
            }
            delete temp;
        }
    }

    void mostrar() {
        Persona* actual = frente;
        while (actual) {
            std::cout << actual->nombre << " (" << actual->fechaNacimiento << ")\n";
            actual = actual->siguiente;
        }
    }
};

// Función para calcular si una persona cumple con la edad requerida
bool cumpleCondicionEdad(const std::string& fechaNacimiento) {
    int year, month, day;
    sscanf(fechaNacimiento.c_str(), "%d-%d-%d", &year, &month, &day);

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    int ageYears = currentYear - year;
    int ageMonths = currentMonth - month;
    int ageDays = currentDay - day;

    if (ageMonths < 0 || (ageMonths == 0 && ageDays < 0)) {
        ageYears--;
    }
    if (ageMonths < 0) {
        ageMonths += 12;
    }
    if (ageDays < 0) {
        ageDays += 30; // Aproximación
    }

    // Verificar si la edad es al menos 18 años, 6 meses y 15 días
    return (ageYears > 18 || (ageYears == 18 && (ageMonths > 6 || (ageMonths == 6 && ageDays >= 15))));
}

void procesarArchivo(const std::string& nombreArchivo, Cola& cola) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre, fechaNacimiento;
        std::getline(ss, nombre, ',');
        std::getline(ss, fechaNacimiento);

        if (cumpleCondicionEdad(fechaNacimiento)) {
            cola.encolar(nombre, fechaNacimiento);
        }
    }

    archivo.close();
}

int main() {
    Cola cola;
    std::string nombreArchivo = "personas.txt";

    procesarArchivo(nombreArchivo, cola);

    std::cout << "Personas en la cola que cumplen con la condición de edad:\n";
    cola.mostrar();

    return 0;
}
