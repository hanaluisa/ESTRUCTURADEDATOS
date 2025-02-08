#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iomanip>

using namespace std;

#define Principal_Max_Hash 18
#define Total_Registros 59

const char fich[17] = "archivo_hash.dat";

FILE* fh = NULL;

typedef struct {
    char codigo[7];
    char autor[41];
    char titulo[41];
} Libro;

#define desplazamiento(n) ((n) * sizeof(Libro))

void creacion();
void alta();
void baja();
void consulta();
void colisiones(Libro lib);
int indexSinonimo(const char c[]);
int Funcion_Hash(string clave);
long Transformar_Clave(string clave);
void mostrar(Libro lib, int posicion);
void mostrarTodos();
void mostrarOcupacion();

int main() {
    cout << "Función Hash con Archivos\n";

    char opcion;
    fh = fopen(fich, "r");
    if (fh == NULL) {
        puts("Crear archivo");
        creacion();
    } else {
        fclose(fh);  // Se cierra el archivo después de verificar si existe
    }

    do {
        cout << "\n#################";
        cout << "\n1. Alta";
        cout << "\n2. Baja";
        cout << "\n3. Consulta";
        cout << "\n4. Consulta Todo";
        cout << "\n5. Mostrar Ocupacion";
        cout << "\n0. Salir";
        
        do {
            cout << "\nOpcion: ";
            cin >> opcion;
        } while (opcion < '0' || opcion > '6');

        switch (opcion) {
            case '1': alta(); break;
            case '2': baja(); break;
            case '3': consulta(); break;
            case '4': mostrarTodos(); break;
            case '5': mostrarOcupacion(); break;
        }
    } while (opcion != '0');

    if (fh != NULL)
        fclose(fh);
}

void creacion() {
    Libro lib = {"*", "", ""};
    fh = fopen(fich, "wb+");
    if (fh == NULL) {
        cout << "Error al crear el archivo\n";
        return;
    }
    for (int i = 0; i < Total_Registros; i++)
        fwrite(&lib, sizeof(lib), 1, fh);
    fclose(fh);
}

void mostrarOcupacion() {
    Libro lib;
    int ocupados = 0;
    fh = fopen(fich, "rb");

    for (int i = Principal_Max_Hash; i <= Total_Registros; i++) {
        fseek(fh, desplazamiento(i), SEEK_SET);
        fread(&lib, sizeof(Libro), 1, fh);
        if (strcmp(lib.codigo, "*") != 0)
            ocupados++;
    }

    fclose(fh);
	cout << "\nTamanio del area de colisiones: " << Total_Registros - Principal_Max_Hash << " espacios";
    cout << "\nNumero de elementos en area de colisiones: " << ocupados;
	cout << "\nPorcentaje de Ocupacion: ";
    std::cout << std::fixed << std::setprecision(2) << (ocupados * 100.0 / (Total_Registros - Principal_Max_Hash)) << "%\n";
}

void alta() {
    Libro libro_Nuevo, libro_Actual;
    long posicion;
    fh = fopen(fich, "rb+");

    if (fh == NULL) {
        cout << "Error al abrir el archivo\n";
        return;
    }

    cout << "Codigo: "; cin >> libro_Nuevo.codigo;
    cout << "Autor: "; cin >> libro_Nuevo.autor;
    cout << "Titulo: "; cin >> libro_Nuevo.titulo;

    posicion = Funcion_Hash(libro_Nuevo.codigo);
    long desplazamientoPos = desplazamiento(posicion);

    fseek(fh, desplazamientoPos, SEEK_SET);
    fread(&libro_Actual, sizeof(Libro), 1, fh);

    if (strcmp(libro_Actual.codigo, "*") == 0) {
        fseek(fh, -sizeof(Libro), SEEK_CUR);
        fwrite(&libro_Nuevo, sizeof(Libro), 1, fh);
        cout << "Registro en direccion: " << posicion << "\n";
    } else if (strcmp(libro_Nuevo.codigo, libro_Actual.codigo) == 0) {
        cout << "\nCodigo repetido";
    } else {
        colisiones(libro_Nuevo);
    }
    fflush(fh);
}

void baja() {
    Libro libro_Actual;
    char codigo[7], r;
    long posicion;
    if (fh == NULL) fh = fopen(fich, "rb+");
    cout << "Codigo:"; cin >> codigo;
    posicion = Funcion_Hash(codigo);

    long Valor_Desplazamiento = desplazamiento(posicion);
    posicion = Valor_Desplazamiento;

    fseek(fh, posicion, SEEK_SET);
    fread(&libro_Actual, sizeof(Libro), 1, fh);

    if (strcmp(libro_Actual.codigo, codigo) != 0)
        posicion = indexSinonimo(codigo);

    if (posicion != -1) {
        mostrar(libro_Actual, posicion);
        cout << "\n¿Confirma los datos a borrar(S/N)?";
        cin >> r;
        if (toupper(r) == 'S') {
            strcpy(libro_Actual.codigo, "*");

            long Salto = (-1) *  static_cast<long>(sizeof(Libro));


            //fseek(fh, (-1)* sizeof(Libro), SEEK_CUR);
            fseek(fh, Salto, SEEK_CUR);

            fwrite(&libro_Actual, sizeof(Libro), 1, fh);
        }
    }
    else
        cout << "No hay registro con ese código";
    fflush(fh);
}


void consulta() {
    Libro lib;
    char codigo[7];
    long posicion;
    if (fh == NULL) fh = fopen(fich, "rb+");

    cout << "Código a Buscar:"; 
    cin >> codigo;
    posicion = Funcion_Hash(codigo);

    long Valor_Desplazamiento = desplazamiento(posicion);
    posicion = Valor_Desplazamiento;

    fseek(fh, posicion, SEEK_SET);
    fread(&lib, sizeof(Libro), 1, fh);

    if (strcmp(lib.codigo, codigo) == 0)
        mostrar(lib,posicion);
    else {
        int posicion;
        posicion = indexSinonimo(codigo);
        if (posicion != -1) {
            long Salto = (-1) *  static_cast<long>(sizeof(Libro));

            //fseek(fh, (-1)* sizeof(Libro), SEEK_CUR);
            fseek(fh, Salto, SEEK_CUR);
            fread(&lib, sizeof(Libro), 1, fh);
            mostrar(lib,posicion);
        }
        else
            cout <<"No se encuentra.";
    }
}

void colisiones(Libro lib) {
    Libro libar;
    int pos = Principal_Max_Hash;
    int encontrado = 0;

    fseek(fh, desplazamiento(pos), SEEK_SET);
    while (pos < Total_Registros && !encontrado) {
        fread(&libar, sizeof(Libro), 1, fh);
        pos++;
        if (strcmp(libar.codigo, "*") == 0) {
            encontrado = 1;
            fseek(fh, -sizeof(Libro), SEEK_CUR);
            fwrite(&lib, sizeof(Libro), 1, fh);
            cout << "Guardado en área de colisiones\n";
        }
    }
    if (!encontrado)
        cout << "Área de colisiones llena\n";
    fflush(fh);
}

int indexSinonimo(const char c[]) {
    Libro libro_Actual;
    int Valor_Desplazamiento = desplazamiento(Principal_Max_Hash);
    int pos = Valor_Desplazamiento;
    int j = Principal_Max_Hash;
    int encontrado;
    fseek(fh, pos, SEEK_SET);
    encontrado = 0;
    while ((j < Total_Registros) && !encontrado) {
        fread(&libro_Actual, sizeof(Libro), 1, fh);
        j++;
        if (strcmp(libro_Actual.codigo, c) == 0)
            encontrado = 1;
    }
    if (!encontrado) j = -1;
    return j;
}

int Funcion_Hash(string clave) {
    long ClaveTransformada = Transformar_Clave(clave);
    return ClaveTransformada % Principal_Max_Hash;
}

long Transformar_Clave(string clave) {
    long d = 0;
    for (char c : clave) {
        d = d + tolower(c);
    }
    return (d < 0) ? -d : d;
}

void mostrar(Libro lib, int posicion) {
    cout << "\nPosición: " << posicion;
    cout << "\nCodigo: " << lib.codigo;
    cout << "\nAutor: " << lib.autor;
    cout << "\nTitulo: " << lib.titulo << "\n";
}

void mostrarTodos() {
    Libro lib;
    fh = fopen(fich, "rb");
    
    cout << "\nP\tCodigo\tAutor\tTitulo";
    for (int i = 0; i < Total_Registros; i++) {
        fseek(fh, desplazamiento(i), SEEK_SET);
        fread(&lib, sizeof(Libro), 1, fh);
        if (strcmp(lib.codigo, "*") != 0) {
            cout << "\n" << i << "\t" << lib.codigo << "\t" << lib.autor << "\t" << lib.titulo;
        }
    }
    fclose(fh);
}