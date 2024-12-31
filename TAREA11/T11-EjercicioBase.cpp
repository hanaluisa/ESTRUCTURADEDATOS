using namespace std;

#include <string.h>
#include <iostream>

#define Principal_Max_Hash 199
#define Total_Registros 240

typedef struct {
    char codigo[7];
    char autor[41];
    char titulo[41];
} Libro;

Libro Arreglo_TablaHash[Total_Registros];

void creacion();
void alta(void);
void baja(void);
void consulta();
void colisiones(Libro lib);
int indexSinonimo(const char c[]);
int Funcion_Hash(string Clave);
long Transformar_Clave(string Clave);
void mostrar(Libro lib, int posicion);
void mostrarTodos();

int main(){

    cout << "Función Hash con Arreglos\n";
    char opcion;
    creacion();
    do {
        cout << "\n#################";
        cout << "\n1. Alta";
        cout << "\n2. Baja";
        cout << "\n3. Consulta";
        cout << "\n4. Consulta Todo";
        cout << "\n0. Salir";
        do {
            cout << "\nOpcion:";
            cin >> opcion;
        } while (opcion < '0' || opcion > '5');

        switch (opcion) {
        case '1':
            alta(); break;
        case '2':
            baja(); break;
        case '3':
            consulta(); break;
        case '4':
            mostrarTodos(); break;

        }
    } while (opcion != '0');

    return 0;
}


void creacion(void) {
    Libro lib = { "*", "", "" };
    int i;
    for (i = 0; i < Total_Registros; i++)
        Arreglo_TablaHash[i] = lib;
}

void alta(void) {
    Libro libro_Nuevo = { "", "", "" }, libro_Actual;
    long posicion;

    cout << "Codigo:" ; cin >> libro_Nuevo.codigo;
    cout << "Autor:"  ; cin >> libro_Nuevo.autor;
    cout << "Titulo:" ; cin >> libro_Nuevo.titulo;
    posicion = Funcion_Hash(libro_Nuevo.codigo);

    long Valor_Desplazamiento = posicion;
    posicion = Valor_Desplazamiento;
    libro_Actual = Arreglo_TablaHash[posicion];

    if (strcmp(libro_Actual.codigo, "*") == 0) {
        Arreglo_TablaHash[posicion] = libro_Nuevo;
        cout << "Registro en direccion: " <<  posicion << "\n";
    }
    else if (strcmp(libro_Nuevo.codigo, libro_Actual.codigo) == 0) {
        cout << "\nCodigo repetido";
        return;
    }
    else
        colisiones(libro_Nuevo);

}

void baja() {
    Libro libro_Actual;
    char codigo[7], r;
    long posicion;
    cout << "Codigo:"; cin >> codigo;
    posicion = Funcion_Hash(codigo);

    libro_Actual = Arreglo_TablaHash[posicion];

    if (strcmp(libro_Actual.codigo, codigo) != 0)
        posicion = indexSinonimo(codigo);

    if (posicion != -1) {

        mostrar(libro_Actual, posicion);
        cout << "\n¿Confirma los datos a borrar(S/N)?";
        cin >> r;
        if (toupper(r) == 'S') {
            strcpy(libro_Actual.codigo, "*");
            Arreglo_TablaHash[posicion] = libro_Actual;
        }
    }
    else
        cout << "No hay registro con ese código";

}


void consulta() {
    Libro lib;
    char codigo[7];
    long posicion;

    cout << "Código a Buscar:";
    cin >> codigo;
    posicion = Funcion_Hash(codigo);

    lib = Arreglo_TablaHash[posicion];
    if (strcmp(lib.codigo, codigo) == 0)
        mostrar(lib,posicion);
    else {
        int posicion;
        posicion = indexSinonimo(codigo);
        if (posicion != -1) {
            lib = Arreglo_TablaHash[posicion];
            mostrar(lib, posicion);
        }
        else
            cout <<"No se encuentra.";
    }
}

void colisiones(Libro libro_Nuevo) {
//La presente función tiene un error. Debe encontrarlo y corregirlo.

    Libro libro_Actual;

    // ERROR: Existe una asignacion redundante dado que el mismo valor es asignado a dos  variables
    // en el codigo solo se usa 1
    int Valor_Desplazamiento = Principal_Max_Hash;
    int pos = Valor_Desplazamiento;
    int j = Principal_Max_Hash;
    int encontrado;
    encontrado = 0;

    // ERROR: El error esta en la validacion para ingresar al bucle J empieza en 199
    // y pide que sea mayor que el total de registros cuyo valor es de 240 

    // ERROR: El valor de la varianble pos deberia incrementar, esto no ocurre en este algoritmo
    while ((j > Total_Registros) && !encontrado) {
        libro_Actual = Arreglo_TablaHash[pos];
        j++;
        if (strcmp(libro_Actual.codigo, "*") == 0) {
            encontrado = 1;
            Arreglo_TablaHash[pos] = libro_Nuevo;
            cout << "Datos grabados en Área de Colisiones.";
        }
    }

    if (!encontrado) 
        cout << "Area de sinonimos completa";
}

int indexSinonimo(const char c[]) {    
    Libro libro_Actual;
    int pos = Principal_Max_Hash;
    int j = Principal_Max_Hash;
    int encontrado;
    encontrado = 0;
    while ((j < Total_Registros) && !encontrado) {
        libro_Actual = Arreglo_TablaHash[pos];
        pos++;
        j++;
        if (strcmp(libro_Actual.codigo, c) == 0)
            encontrado = 1;
    }
    if (!encontrado) j = -1;
    return j;
}

int Funcion_Hash(string clave) {
    int l = clave.length();
    for (int i = 0; i < l ; i++){
        clave[i] = toupper(clave[i]);
    }
    int  ClaveTransformada = Transformar_Clave(clave);
    int ClaveHash = ClaveTransformada % 198;
    return ClaveHash;
}

long Transformar_Clave(string clave) {
    long d;
    d = 0;
    int l = clave.length();
    for (int j = 0; j < l; j++) {
        d = d * 27 + clave[j];
    }
    if (d < 0) d = -d;
    return d;
}

void mostrar(Libro lib, int posicion) {
    cout << "\nPosición: \t"<< posicion;
    cout << "\nCodigo: \t"<< lib.codigo;
    cout << "\nAutor: \t"<< lib.autor;
    cout << "\nTitulo: \n"<< lib.titulo;
}

void mostrarTodos(){
   cout << "\nTodos: \t";
    Libro lib;
    cout << "\n P"<< "\t Codigo\t Autor\t Titulo";
    for (int i = 0; i < Total_Registros; i++){
        lib = Arreglo_TablaHash[i];
        cout << "\n" << i<< "\t" << lib.codigo << "\t" << lib.autor<< "\t" << lib.titulo;
    }
}