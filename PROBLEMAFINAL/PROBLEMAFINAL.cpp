#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>  // Para strcpy, memset
#include <cctype>   // Para isdigit
using namespace std;

struct Libro {
    char codigo[7];
    char autor[41];
    char titulo[41];
    int anio;
};

// Tamaños de áreas
const int TOTAL_REGISTROS = 1000;
const int AREA_1_SIZE = TOTAL_REGISTROS * 0.6;   // 60% = 480 registros
const int AREA_2_SIZE = TOTAL_REGISTROS * 0.3;   // 30% = 240 registros
const int COLISIONES_SIZE = TOTAL_REGISTROS * 0.1; // 10% = 80 registros
const char *ARCHIVO_BINARIO = "libros.dat";

// Función para verificar si una cadena contiene solo números
bool esNumero(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Crear un registro vacío con '*'
Libro registroVacio() {
    Libro libro;
    memset(libro.codigo, '*', sizeof(libro.codigo) - 1);
    memset(libro.autor, '*', sizeof(libro.autor) - 1);
    memset(libro.titulo, '*', sizeof(libro.titulo) - 1);
    libro.codigo[6] = '\0';
    libro.autor[40] = '\0';
    libro.titulo[40] = '\0';
    libro.anio = -1;
    return libro;
}

// Inicializar archivo con registros vacíos (Automático)
void inicializarArchivoBinario() {
    ifstream checkFile(ARCHIVO_BINARIO);
    if (checkFile.good()) {
        checkFile.close();
        return;  // Si el archivo ya existe, no lo inicializamos nuevamente
    }

    ofstream file(ARCHIVO_BINARIO, ios::binary);
    if (!file) {
        cout << "Error al crear el archivo binario." << endl;
        return;
    }

    Libro libroVacio = registroVacio();
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        file.write(reinterpret_cast<const char*>(&libroVacio), sizeof(Libro));
    }

    file.close();
    cout << "Archivo inicializado con registros vacíos automáticamente." << endl;
}

// Funciones hash
int hashFunction1(const string& codigo) {
    int hashValue = 0;
    string reversedCodigo = string(codigo.rbegin(), codigo.rend()); // Invierte el string

    for (size_t i = 0; i < reversedCodigo.length(); i += 2) {
        int sum = reversedCodigo[i];
        if (i + 1 < reversedCodigo.length()) {
            sum += reversedCodigo[i + 1];  // Suma de dos en dos
        }
        hashValue += sum;
    }

    return hashValue % AREA_1_SIZE;  // Asegura que esté dentro del área 1 (60%)
}

int hashFunction2(const string& codigo) {
    int hashValue = 0;

    for (size_t i = 0; i < codigo.length(); i += 2) {  // Saltamos de 2 en 2
        int sum = codigo[i];
        if (i + 2 < codigo.length()) {
            sum += codigo[i + 2];  // Suma el siguiente carácter saltando 1
        }
        hashValue += sum * 42;  // Multiplicamos por 42
    }

    return (hashValue % AREA_2_SIZE) + AREA_1_SIZE;  // Asegurar que esté en área 2
}


// Verificar si el código ya existe en el archivo binario
bool existeRegistro(const string& codigo) {
    ifstream file(ARCHIVO_BINARIO, ios::binary);
    if (!file) return false;

    Libro libro;
    while (file.read(reinterpret_cast<char*>(&libro), sizeof(Libro))) {
        if (codigo == libro.codigo) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Función para verificar si el código cumple con las reglas establecidas
bool validarCodigo(const string& codigo) {
    if (codigo.length() != 4) return false;  // Debe ser de longitud 4

    // Caso 1: Código con 4 letras mayúsculas
    if (isupper(codigo[0]) && isupper(codigo[1]) && isupper(codigo[2]) && isupper(codigo[3])) {
        return true;
    }

    // Caso 2: Código con 4 dígitos (solo 1,2,3,4)
    if (codigo.find_first_not_of("1234") == string::npos) {
        return true;
    }

    // Caso 3: Código con 4 dígitos (solo 5,6,7,8)
    if (codigo.find_first_not_of("5678") == string::npos) {
        return true;
    }

    return false;  // Si no cumple con ninguno, se rechaza
}

// Escribir registro en archivo binario
void escribirRegistroBinario(const Libro& libro) {
    // Verificar que el código cumpla con las reglas
    if (!validarCodigo(libro.codigo)) {
        cout << "Error: El código '" << libro.codigo << "' no cumple con los requisitos." << endl;
        return;
    }

    if (existeRegistro(libro.codigo)) {
        cout << "Error: El código " << libro.codigo << " ya existe." << endl;
        return;
    }

    fstream file(ARCHIVO_BINARIO, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error al abrir el archivo binario." << endl;
        return;
    }

    int posicion = hashFunction1(libro.codigo);
    file.seekg(posicion * sizeof(Libro), ios::beg);

    Libro existente;
    file.read(reinterpret_cast<char*>(&existente), sizeof(Libro));

    if (existente.codigo[0] == '*') {
        file.seekp(posicion * sizeof(Libro), ios::beg);
        cout << "Registro guardado en Área 1 (60%) en posición: " << posicion << endl;
    } else {
        posicion = hashFunction2(libro.codigo);
        file.seekg(posicion * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&existente), sizeof(Libro));

        if (existente.codigo[0] == '*') {
            file.seekp(posicion * sizeof(Libro), ios::beg);
            cout << "Registro guardado en Área 2 (30%) en posición: " << posicion << endl;
        } else {
            bool guardado = false;
            for (int i = AREA_1_SIZE + AREA_2_SIZE; i < TOTAL_REGISTROS; i++) {
                file.seekg(i * sizeof(Libro), ios::beg);
                file.read(reinterpret_cast<char*>(&existente), sizeof(Libro));
                if (existente.codigo[0] == '*') {
                    file.seekp(i * sizeof(Libro), ios::beg);
                    cout << "Registro guardado en Área de Colisión (10%) en posición: " << i << endl;
                    guardado = true;
                    break;
                }
            }
            if (!guardado) {
                cout << "Error: No hay espacio disponible en el archivo binario." << endl;
                file.close();
                return;
            }
        }
    }

    file.write(reinterpret_cast<const char*>(&libro), sizeof(Libro));
    file.close();
}


// Agregar registro manualmente
void agregarRegistroManual() {
    Libro libro;
    cout << "Ingrese código (4 caracteres 1 al 4) (4 caracteres 5 al 8) (4 caracteres A a la Z en mayusculas): ";
    cin >> libro.codigo;

    if (existeRegistro(libro.codigo)) {
        cout << "Error: El código " << libro.codigo << " ya existe." << endl;
        return;
    }

    cout << "Ingrese autor: ";
    cin.ignore();
    cin.getline(libro.autor, 41);
    cout << "Ingrese título: ";
    cin.getline(libro.titulo, 41);
    string inputAnio;
    do {
        cout << "Ingrese año (número entero): ";
        cin >> inputAnio;

        if (!esNumero(inputAnio)) {
            cout << "Error: El año debe ser un número entero válido." << endl;
            cin.clear();  // Limpiar el estado de cin
            cin.ignore(10000, '\n');  // Limpiar buffer
        }
    } while (!esNumero(inputAnio));

    libro.anio = stoi(inputAnio);

    escribirRegistroBinario(libro);
}

// Leer registros desde el archivo binario
void leerRegistrosBinarios() {
    ifstream file(ARCHIVO_BINARIO, ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo binario." << endl;
        return;
    }

    Libro libro;
    while (file.read(reinterpret_cast<char*>(&libro), sizeof(Libro))) {
        if (libro.codigo[0] != '*') {
            cout << "Código: " << libro.codigo << endl;
            cout << "Autor: " << libro.autor << endl;
            cout << "Título: " << libro.titulo << endl;
            cout << "Año: " << libro.anio << endl;
            cout << "-----------------" << endl;
        }
    }

    file.close();
}

// Función para limpiar espacios en blanco al inicio y final de un string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // Si solo hay espacios, devolver vacío
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Leer archivo TXT y guardar en binario
void leerArchivoTxt(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de texto." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        vector<string> columnas;

        // Separar los valores por tabulaciones ('\t')
        while (getline(ss, campo, '\t')) {
            columnas.push_back(trim(campo));  // Limpiar espacios en blanco
        }

        // Verificar que hay al menos 4 columnas antes de continuar
        if (columnas.size() < 4) {
            cout << "Error: Línea con formato incorrecto -> " << linea << endl;
            continue;
        }

        // Verificar que el año sea numérico antes de convertirlo
        if (!esNumero(columnas[3])) {
            cout << "Error: Año inválido en línea -> '" << columnas[3] << "'" << endl;
            continue;
        }

        // Convertir el año a entero
        int anio = stoi(columnas[3]);

        // Guardar los datos en la estructura Libro
        Libro libro;
        strcpy(libro.codigo, columnas[0].c_str());
        strcpy(libro.autor, columnas[1].c_str());
        strcpy(libro.titulo, columnas[2].c_str());
        libro.anio = anio;

        // Guardar el registro en el archivo binario
        escribirRegistroBinario(libro);
    }

    archivo.close();
}

// Función para verificar si un registro está vacío
bool esRegistroVacio(const Libro& libro) {
    return libro.codigo[0] == '*';
}

// Función para mostrar el porcentaje de ocupación de cada área
void mostrarPorcentajeOcupacion() {
    ifstream file(ARCHIVO_BINARIO, ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo binario para leer ocupación." << endl;
        return;
    }

    int ocupadosArea1 = 0, ocupadosArea2 = 0, ocupadosColisiones = 0;
    Libro libro;

    // Contar registros ocupados en cada área
    for (int i = 0; i < AREA_1_SIZE; i++) {
        file.seekg(i * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
        if (!esRegistroVacio(libro)) ocupadosArea1++;
    }

    for (int i = AREA_1_SIZE; i < AREA_1_SIZE + AREA_2_SIZE; i++) {
        file.seekg(i * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
        if (!esRegistroVacio(libro)) ocupadosArea2++;
    }

    for (int i = AREA_1_SIZE + AREA_2_SIZE; i < TOTAL_REGISTROS; i++) {
        file.seekg(i * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
        if (!esRegistroVacio(libro)) ocupadosColisiones++;
    }

    file.close();

    // Calcular y mostrar porcentajes
    double porcentaje1 = (ocupadosArea1 * 100.0) / AREA_1_SIZE;
    double porcentaje2 = (ocupadosArea2 * 100.0) / AREA_2_SIZE;
    double porcentajeColisiones = (ocupadosColisiones * 100.0) / COLISIONES_SIZE;

    cout << "\n--- Porcentaje de Ocupación ---\n";
    cout << "Área 1 (60% del archivo): " << porcentaje1 << "% (" << ocupadosArea1 << "/" << AREA_1_SIZE << ")\n";
    cout << "Área 2 (30% del archivo): " << porcentaje2 << "% (" << ocupadosArea2 << "/" << AREA_2_SIZE << ")\n";
    cout << "Área de Colisiones (10% del archivo): " << porcentajeColisiones << "% (" << ocupadosColisiones << "/" << COLISIONES_SIZE << ")\n";
    cout << "--------------------------------\n";
}

// Función para eliminar un registro del archivo binario
void eliminarRegistroBinario(const string& codigo) {
    fstream file(ARCHIVO_BINARIO, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error al abrir el archivo binario." << endl;
        return;
    }

    int posicion;
    Libro libro;
    Libro libroVacio = registroVacio();  // Crear una variable para almacenar el registro vacío

    // Buscar en Área 1
    posicion = hashFunction1(codigo);
    file.seekg(posicion * sizeof(Libro), ios::beg);
    file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

    if (codigo == libro.codigo) {
        // Marcar como eliminado
        file.seekp(posicion * sizeof(Libro), ios::beg);
        file.write(reinterpret_cast<const char*>(&libroVacio), sizeof(Libro)); // Escribir desde la variable
        cout << "Registro eliminado en Área 1 (60%) en posición: " << posicion << endl;
        file.close();
        return;
    }

    // Buscar en Área 2
    posicion = hashFunction2(codigo);
    file.seekg(posicion * sizeof(Libro), ios::beg);
    file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

    if (codigo == libro.codigo) {
        file.seekp(posicion * sizeof(Libro), ios::beg);
        file.write(reinterpret_cast<const char*>(&libroVacio), sizeof(Libro)); // Escribir desde la variable
        cout << "Registro eliminado en Área 2 (30%) en posición: " << posicion << endl;
        file.close();
        return;
    }

    // Buscar en Área de Colisión
    for (int i = AREA_1_SIZE + AREA_2_SIZE; i < TOTAL_REGISTROS; i++) {
        file.seekg(i * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

        if (codigo == libro.codigo) {
            file.seekp(i * sizeof(Libro), ios::beg);
            file.write(reinterpret_cast<const char*>(&libroVacio), sizeof(Libro)); // Escribir desde la variable
            cout << "Registro eliminado en Área de Colisión (10%) en posición: " << i << endl;
            file.close();
            return;
        }
    }

    cout << "Error: No se encontró el código '" << codigo << "' en el archivo binario." << endl;
    file.close();
}

// Función para buscar un registro en el archivo binario
void buscarRegistroBinario(const string& codigo) {
    ifstream file(ARCHIVO_BINARIO, ios::binary);
    if (!file) {
        cout << "Error al abrir el archivo binario." << endl;
        return;
    }

    int posicion;
    Libro libro;

    // Buscar en Área 1
    posicion = hashFunction1(codigo);
    file.seekg(posicion * sizeof(Libro), ios::beg);
    file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

    if (codigo == libro.codigo) {
        cout << "Registro encontrado en Área 1 (60%) en posición: " << posicion << endl;
        cout << "Código: " << libro.codigo << ", Autor: " << libro.autor << ", Título: " << libro.titulo << ", Año: " << libro.anio << endl;
        file.close();
        return;
    }

    // Buscar en Área 2
    posicion = hashFunction2(codigo);
    file.seekg(posicion * sizeof(Libro), ios::beg);
    file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

    if (codigo == libro.codigo) {
        cout << "Registro encontrado en Área 2 (30%) en posición: " << posicion << endl;
        cout << "Código: " << libro.codigo << ", Autor: " << libro.autor << ", Título: " << libro.titulo << ", Año: " << libro.anio << endl;
        file.close();
        return;
    }

    // Buscar en Área de Colisión
    for (int i = AREA_1_SIZE + AREA_2_SIZE; i < TOTAL_REGISTROS; i++) {
        file.seekg(i * sizeof(Libro), ios::beg);
        file.read(reinterpret_cast<char*>(&libro), sizeof(Libro));

        if (codigo == libro.codigo) {
            cout << "Registro encontrado en Área de Colisión (10%) en posición: " << i << endl;
            cout << "Código: " << libro.codigo << ", Autor: " << libro.autor << ", Título: " << libro.titulo << ", Año: " << libro.anio << endl;
            file.close();
            return;
        }
    }

    cout << "Error: No se encontró el código '" << codigo << "' en el archivo binario." << endl;
    file.close();
}

int main() {
    inicializarArchivoBinario();

    int opcion;
    string codigo;
    do {
        cout << "1. Leer archivo de texto y guardar en binario" << endl;
        cout << "2. Agregar registro manualmente" << endl;
        cout << "3. Leer registros desde archivo binario" << endl;
        cout << "4. Mostrar ocupación" << endl;
        cout << "5. Buscar registro" << endl;
        cout << "6. Eliminar registro" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                leerArchivoTxt("libros.txt");
                break;
            case 2:
                agregarRegistroManual();
                break;
            case 3:
                leerRegistrosBinarios();
                break;
            case 4:
                mostrarPorcentajeOcupacion();
                break;
            case 5:
                cout << "Ingrese el código a buscar: ";
                cin >> codigo;
                buscarRegistroBinario(codigo);
                break;
            case 6:
                cout << "Ingrese el código a eliminar: ";
                cin >> codigo;
                eliminarRegistroBinario(codigo);
                break;
            case 7:
                cout << "Saliendo..." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}
