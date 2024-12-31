#include <string.h>
#include <iostream>
#include <stdio.h>

#define Principal_Max_Hash 199
#define Total_Registros 240

const char fich[17] = "archivo_hash.dat";
FILE* fh = NULL;

using namespace std;

// Declarar la estructura del libro que contiene codigo, autor y titulo
typedef struct {
    char codigo[7];
    char autor[41];
    char titulo[41];
} Libro;

// Macro que calcula el desplazamiento o offset de un elemento binario
// Ejemplo: sizeof(Libro) sería 157 bytes 
// Desplazamiento recibe la posicion 3 esto multiplicado por 157 = 471
// Entonces, para leer o escribir el registro en la posición 3, 
// el puntero de archivo se movería 471 bytes hacia adelante desde el principio del archivo.
#define desplazamiento(n) ((n) * sizeof(Libro))

// Declarar los prototipos de funciones que son implementadas despues de la funcion principal
void creacion(void);
void alta(void);
void baja(void);
void consulta(void);
void colisiones(Libro lib);
int indexSinonimo(const char c[]);
int Funcion_Hash(string Clave);
long Transformar_Clave(string Clave);
void mostrar(Libro lib, int posicion);
void mostrarTodos(void);

int main() {
    cout << "Función Hash con Archivos\n";
    char opcion;
    // Crear espacio de memoria que contiene el arreglo de libros con valor inicial de [*]
    creacion();
    // Bucle do while, que solicita al usuario el ingreso de una opcion
    // Mientras la opcion es diferente de cero se seguira ejecutando
    do {
        cout << "\n#################";
        cout << "\n1. Alta";
        cout << "\n2. Baja";
        cout << "\n3. Consulta";
        cout << "\n4. Consulta Todo";
        cout << "\n0. Salir";

        // Bucle que solicita al usuario ingresar nuevamente la opcion en caso de que
        // los valores ingresados sean menores a cero o mayores a 5 los valores son validados
        // ACII para caracteres
        do {
            cout << "\nOpcion:";
            cin >> opcion;
        } while (opcion < '0' || opcion > '5');
        // Ejecuta el metodo segun la opcion ingresada por e usuario  
        switch (opcion) {
        case '1':
            alta();
            break;
        case '2':
            baja();
            break;
        case '3':
            consulta();
            break;
        case '4':
            mostrarTodos();
            break;
        }
    } while (opcion != '0');

    return 0;
}

// Funcion de inicializacion de un arreglo 
void creacion(void) {
    // Inicializar la estrcutura de ibro con valores por defecto
    Libro lib = {"*", "", ""};
    // Se abre un archivo binario
    fh = fopen(fich, "wb+");
    // Verifica si el archivo pudo ser abierto
    if (fh == NULL) {
        cout << "Error al crear el archivo." << endl;
        return;
    }
    // Bucle que copia - escribe la estructura al archivo
    for (int i = 0; i < Total_Registros; i++) {
        fwrite(&lib, sizeof(lib), 1, fh);
    }
    // Cierre del archivo 
    fclose(fh);
    fh = NULL;
}

void alta(void) {
    // libro_Nuevo es el libro que el usuario desea registrar. Se inicializa con valores vacíos para los campos codigo, autor y titulo
    // libro_Actual Se usara para almacenar el libro que ya está en la posición de memoria que se va a revisar en el archivo.
    Libro libro_Nuevo = {"", "", ""}, libro_Actual;
    long posicion;
    // Se le pide al usuario que ingrese el codigo, autor y titulo del libro que desea registrar.
    // Estos datos se almacenan en la variable libro_Nuevo.
    cout << "Codigo:";
    cin >> libro_Nuevo.codigo;
    cout << "Autor:";
    cin >> libro_Nuevo.autor;
    cout << "Titulo:";
    cin >> libro_Nuevo.titulo;

    // genera una posición (índice) en el archivo donde se intentará almacenar el libro
    posicion = Funcion_Hash(libro_Nuevo.codigo);

    // Se abre un archivo binario
    fh = fopen(fich, "rb+");
    // Verifica si el archivo pudo ser abierto
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    // Se mueve el puntero de archivo a la posición calculada posicion (usando la función desplazamiento(posicion) 
    // para calcular el desplazamiento en bytes). Luego, se lee el libro almacenado en esa posición y se guarda 
    // en la variable libro_Actual.
    fseek(fh, desplazamiento(posicion), SEEK_SET);
    fread(&libro_Actual, sizeof(libro_Actual), 1, fh);

    if (strcmp(libro_Actual.codigo, "*") == 0) { // Si encuentra una posicion vacia ingresa el valor del nuevo registro
        fseek(fh, desplazamiento(posicion), SEEK_SET);
        fwrite(&libro_Nuevo, sizeof(libro_Nuevo), 1, fh);
        cout << "Registro en direccion: " << posicion << "\n";
    } else if (strcmp(libro_Nuevo.codigo, libro_Actual.codigo) == 0) { // Identifica valores repetidos
        cout << "\nCodigo repetido";
    } else { // Llamada de funcion para el manejo de colisiones
        fclose(fh);
        colisiones(libro_Nuevo);
        return;
    }

    fclose(fh);
}

void baja(void) {
    Libro libro_Actual;
    char codigo[7], r;
    long posicion;
    
    // Solicita al usuario e ingreso del codigo a encontrar
    cout << "Codigo:";
    cin >> codigo;
    posicion = Funcion_Hash(codigo);

    // Se abre un archivo binario
    fh = fopen(fich, "rb+");
    // Verifica si el archivo pudo ser abierto
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    
    // Desplaza el puntero del archivo a la ubicacion requerida y lee la posicion del codigo ingresado
    fseek(fh, desplazamiento(posicion), SEEK_SET);
    fread(&libro_Actual, sizeof(libro_Actual), 1, fh);
    
    // Verificar si el codigo desde el archivo coincide con el codigo ingresado 
    if (strcmp(libro_Actual.codigo, codigo) != 0)
        posicion = indexSinonimo(codigo);

    // Verifica si el registro existe
    if (posicion != -1) {
        mostrar(libro_Actual, posicion);
        cout << "\n¿Confirma los datos a borrar(S/N)?";
        cin >> r;
        if (toupper(r) == 'S') {
            // Se asigna el valor definido por defecto en la posicion encontrada en el archivo 'Elimina los registros'
            strcpy(libro_Actual.codigo, "*");
            strcpy(libro_Actual.autor, "");
            strcpy(libro_Actual.titulo, "");
            fseek(fh, desplazamiento(posicion), SEEK_SET);
            fwrite(&libro_Actual, sizeof(libro_Actual), 1, fh);
        }
    } else {
        cout << "No hay registro con ese código";
    }

    fclose(fh);
}

void consulta(void) {
    Libro lib;
    char codigo[7];
    long posicion;

    cout << "Código a Buscar:";
    cin >> codigo;
    posicion = Funcion_Hash(codigo);

    fh = fopen(fich, "rb");
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    fseek(fh, desplazamiento(posicion), SEEK_SET);
    fread(&lib, sizeof(lib), 1, fh);

    if (strcmp(lib.codigo, codigo) == 0) {
        mostrar(lib, posicion);
    } else {
        int posicion = indexSinonimo(codigo);
        if (posicion != -1) {
            fseek(fh, desplazamiento(posicion), SEEK_SET);
            fread(&lib, sizeof(lib), 1, fh);
            mostrar(lib, posicion);
        } else {
            cout << "No se encuentra.";
        }
    }

    fclose(fh);
}

void colisiones(Libro libro_Nuevo) {
    Libro libro_Actual;
    // CORRECCION: La asignacipn se hace directo a la variable pos
    int pos = Principal_Max_Hash; // Punto inicial del área de colisiones
    int j = Principal_Max_Hash; // Contador para el límite superior
    int encontrado = 0;
    // Se abre un archivo binario
    fh = fopen(fich, "rb+");
    // Verifica si el archivo pudo ser abierto
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    // Recorremos el área de sinónimos hasta encontrar un espacio vacío o llegar al límite
    // CORRECCION: Aqui si ingresa al bucle
    while ((j < Total_Registros) && !encontrado) {
        // Funcion que mueve el puntero de archivo a la posicion de pos calculada por la macro
        // desplazamiento SEEK_SET es un argumento que indica que e desplazamiento va desde el
        // inicio del archivo
        fseek(fh, desplazamiento(pos), SEEK_SET); 
        // Leer el registro
        fread(&libro_Actual, sizeof(libro_Actual), 1, fh);
        if (strcmp(libro_Actual.codigo, "*") == 0) { // Espacio vacío encontrado
            encontrado = 1;
            fseek(fh, desplazamiento(pos), SEEK_SET);
            fwrite(&libro_Nuevo, sizeof(libro_Nuevo), 1, fh); // Insertamos el libro
            cout << "Datos grabados en Área de Colisiones en la posición: " << pos << ".\n";
        } else {
            pos++; // CORRECCION: Avanzamos a la siguiente posición
            if (pos >= Total_Registros) {
                pos = Principal_Max_Hash; // Volvemos al inicio del área de sinónimos
            }
            j++;
        }
    }

    if (!encontrado)
        cout << "Área de sinónimos completa.\n";

    fclose(fh);
}

int indexSinonimo(const char c[]) {
    Libro libro_Actual;
    int pos = Principal_Max_Hash;
    int j = Principal_Max_Hash;
    int encontrado = 0;
    // Abrir archivo binario
    fh = fopen(fich, "rb");
    // Verificar correcta apertura
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return -1;
    }

    while ((j < Total_Registros) && !encontrado) {
        // Mover el puntero de un archivo fh a una posicion especifica dentro del archivo
        fseek(fh, desplazamiento(pos), SEEK_SET);
        // Lee el bloque de datos a los que se apunto previamente, sabe el tamanio del bloque por sizeof
        fread(&libro_Actual, sizeof(libro_Actual), 1, fh);
        // Encontar el codigo solicitado c es el parametro de entrado
        if (strcmp(libro_Actual.codigo, c) == 0)
            encontrado = 1;
        else {
            pos++;
            if (pos >= Total_Registros) {
                pos = Principal_Max_Hash;
            }
            j++;
        }
    }

    fclose(fh);
    // Operador ternario que indica si encontrado es verdadero 'diferente de cero'
    // retorna 1 en caso contrario retorna -1 
    return encontrado ? pos : -1;
}

int Funcion_Hash(string clave) {
    // Se obtiene la longitud de a cadena
    int l = clave.length();
    // Cada caracter es cambiado a mayusculas 
    for (int i = 0; i < l; i++) {
        clave[i] = toupper(clave[i]);
    }
    // Se obtiene el hash del valor str ingresado
    int ClaveTransformada = Transformar_Clave(clave);
    // Retorno del residuo tomando en cuenta la posicion maxima en la tabla principal
    return ClaveTransformada % Principal_Max_Hash;
}

long Transformar_Clave(string clave) {
    // Inicializacion de variables
    long hash = 0;
    const long prime = 31;  // Usamos un valor primo para multiplicar y distribuir mejor las claves.

    // Resultado de hash [abc] -> 93984 dentro de bucle 
    for (char c : clave) {
        // [a] -> 97 {0 * 31 + 97 = 97}
        // [b] -> 98 {97 * 31 + 98 = 3025}
        // [c] -> 99 {3025 * 31 + 99 = 93984}
        hash = hash * prime + c;  // Multiplicamos por un número primo y sumamos el valor del carácter.
    }

    return hash;
}

void mostrar(Libro lib, int posicion) {
    // Muestra el valor de la estructura que se envia como parametro, al igual que la posicion
    cout << "\nPosición: \t" << posicion;
    cout << "\nCodigo: \t" << lib.codigo;
    cout << "\nAutor: \t" << lib.autor;
    cout << "\nTitulo: \n" << lib.titulo;
}

void mostrarTodos() {
    Libro lib;
    // Se abre un archivo binario
    fh = fopen(fich, "rb");
    // Verifica si el archivo pudo ser abierto
    if (fh == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    cout << "\nTodos: \t";
    cout << "\n P\t Codigo\t Autor\t Titulo";
    // Iterar sobre todos los registros del archivo
    for (int i = 0; i < Total_Registros; i++) {
        // Mover el puntero de un archivo fh a una posicion especifica dentro del archivo
        fseek(fh, desplazamiento(i), SEEK_SET);
        // Lee el bloque de datos a los que se apunto previamente, sabe el tamanio del bloque por sizeof
        fread(&lib, sizeof(lib), 1, fh);
        cout << "\n" << i << "\t" << lib.codigo << "\t" << lib.autor << "\t" << lib.titulo;
    }

    fclose(fh);
}
