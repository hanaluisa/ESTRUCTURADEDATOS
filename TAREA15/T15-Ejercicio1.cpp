#include <iostream>
using namespace std;

// Definición de la estructura del nodo
struct node {
    int data;
    struct node* izq;
    struct node* der;
};

// Prototipos de funciones
void Insertar(node*& pRaiz, int Valor);
void DesplegarArbol_EnOrden(node* pRaiz);
void DesplegarArbol_PreOrden(node* pRaiz);
void DesplegarArbol_PostOrden(node* pRaiz);
void LiberarMemoria(node*& pRaiz);

int main() {
    cout << "Arbol Binario de Busqueda\n";

    // Inicializamos el árbol como vacío
    node* pRaiz = NULL;
    int valor;

    // Pedir al usuario ingresar valores
    cout << "Introduce numeros para insertar en el arbol (0 para terminar):\n";
    while (true) {
        cout << "Numero: ";
        cin >> valor;

        // Verificar si la entrada es válida (solo números)
        if (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(10000, '\n'); // Descartar la entrada inválida
            cout << "Entrada invalida. Solo numeros son permitidos.\n";
            continue;
        }

        if (valor == 0) break; // Termina la inserción

        Insertar(pRaiz, valor);
    }

    // Mostrar recorridos del árbol
    cout << "\nRecorrido En Orden:\n";
    DesplegarArbol_EnOrden(pRaiz);
    cout << "\nRecorrido Pre Orden:\n";
    DesplegarArbol_PreOrden(pRaiz);
    cout << "\nRecorrido Post Orden:\n";
    DesplegarArbol_PostOrden(pRaiz);

    // Liberar memoria antes de salir
    LiberarMemoria(pRaiz);

    return 0;
}

// Función para insertar valores en el árbol
void Insertar(node*& pRaiz, int Valor) {
    node* pX = pRaiz;
    node* pUltimoNodo = NULL;

    while (pX != NULL) {
        pUltimoNodo = pX;
        if (Valor < pX->data)
            pX = pX->izq;
        else if (Valor > pX->data)
            pX = pX->der;
        else
            return; // Valor ya existe, no se inserta duplicado
    }

    node* pNuevo = new node;
    pNuevo->data = Valor;
    pNuevo->izq = pNuevo->der = NULL;

    if (pUltimoNodo == NULL) {
        pRaiz = pNuevo; // Árbol estaba vacío
    } else {
        if (Valor < pUltimoNodo->data)
            pUltimoNodo->izq = pNuevo;
        else
            pUltimoNodo->der = pNuevo;
    }
}

// Recorrido en orden (Izquierda - Raíz - Derecha)
void DesplegarArbol_EnOrden(node* pRaiz) {
    if (pRaiz != NULL) {
        DesplegarArbol_EnOrden(pRaiz->izq);
        cout << pRaiz->data << " ";
        DesplegarArbol_EnOrden(pRaiz->der);
    }
}

// Recorrido en preorden (Raíz - Izquierda - Derecha)
void DesplegarArbol_PreOrden(node* pRaiz) {
    if (pRaiz != NULL) {
        cout << pRaiz->data << " ";
        DesplegarArbol_PreOrden(pRaiz->izq);
        DesplegarArbol_PreOrden(pRaiz->der);
    }
}

// Recorrido en postorden (Izquierda - Derecha - Raíz)
void DesplegarArbol_PostOrden(node* pRaiz) {
    if (pRaiz != NULL) {
        DesplegarArbol_PostOrden(pRaiz->izq);
        DesplegarArbol_PostOrden(pRaiz->der);
        cout << pRaiz->data << " ";
    }
}

// Función para liberar la memoria del árbol
void LiberarMemoria(node*& pRaiz) {
    if (pRaiz != NULL) {
        LiberarMemoria(pRaiz->izq);
        LiberarMemoria(pRaiz->der);
        delete pRaiz;
        pRaiz = NULL;
    }
}
