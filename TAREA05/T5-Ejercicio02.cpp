#include <iostream>
#include <cmath>  // Para usar la función sqrt()

struct Nodo {
    int valor;
    Nodo* siguiente;
};

// Función para agregar un nodo al final de la lista enlazada
void agregarNodo(Nodo*& cabeza, int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = nullptr;
    
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

// Función para cargar múltiplos de 5 en la lista enlazada hasta un límite dado
void cargarMultiplosDe5(Nodo*& cabeza, int limite) {
    for (int i = 5; i <= limite; i += 5) {
        agregarNodo(cabeza, i);
    }
}

// Función para cargar numeros pares en la lista enlazada hasta un límite dado
void cargarNumerosPares(Nodo*& cabeza, int limite) {
    for (int i = 0; i < limite; i++) {
        if (i % 2 == 0) {
            agregarNodo(cabeza, i);
        }
    }
}

// Función para cargar numeros primos en la lista enlazada hasta un límite dado
void cargarNumerosPrimos(Nodo*& cabeza, int limite) {
    // Recorrer la lista y verificar si cada número es primo
    for (int i = 0; i < limite; i++) {
        int num = i;
        
        // Verificar si el número es menor o igual a 1 (no primo)
        if (num <= 1) {
            continue;  // Si el número no es primo, continuar con el siguiente
        }
        
        // Verificar divisibilidad de 'num' desde 2 hasta la raíz cuadrada de 'num'
        bool esPrimo = true;
        for (int j = 2; j <= std::sqrt(num); j++) {
            if (num % j == 0) {
                esPrimo = false;  // Si tiene un divisor, no es primo
                break;  // No es necesario seguir buscando más divisores
            }
        }
        
        // Si es primo, mostrarlo
        if (esPrimo) {
            agregarNodo(cabeza, i);
        }
    }
}

// Función para cargar numeros de fibonnaci en la lista enlazada hasta un límite dado
void cargarNumerosFibonacci(Nodo*& cabeza, int limite){
    int a = 0, b = 1; 
    agregarNodo(cabeza, a);
    while (b <= limite) {  // Mientras el número b sea menor o igual al límite
        agregarNodo(cabeza, b);
        //std::cout << b << " ";  // Imprimir el siguiente número
        int temp = b;
        b = a + b;  // Calcular el siguiente número de Fibonacci
        a = temp;  // Actualizar 'a' para el siguiente ciclo
    }
}


// Función para imprimir la lista enlazada
void imprimirLista(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        std::cout << temp->valor << " -> ";
        temp = temp->siguiente;
    }
    std::cout << "FIN\n";
}

// Función para liberar la memoria de la lista enlazada
void liberarLista(Nodo*& cabeza) {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

int main() {
    Nodo* lista = nullptr;
    Nodo* listaDePares = nullptr;
    Nodo* listaDePrimos = nullptr;
    Nodo* listaDeFibonacci = nullptr;

    int limite;

    std::cout << "Ingrese el tamaño de la lista: ";
    std::cin >> limite;

    // Cargar múltiplos de 5 en la lista enlazada
    cargarMultiplosDe5(lista, limite);
    cargarNumerosPares(listaDePares, limite);
    cargarNumerosPrimos(listaDePrimos, limite);
    cargarNumerosFibonacci(listaDeFibonacci, limite);

    // Imprimir la lista enlazada
    std::cout << "Lista de múltiplos de 5  " << limite << ":\n";
    imprimirLista(lista);
    std::cout << "Lista de numeros pares " << limite << ":\n";
    imprimirLista(listaDePares);
    std::cout << "Lista de numeros primos " << limite << ":\n";
    imprimirLista(listaDePrimos);
    std::cout << "Lista de fibonacci " << limite << ":\n";
    imprimirLista(listaDeFibonacci);

    // Liberar la memoria de la lista
    liberarLista(lista);
    liberarLista(listaDePares);
    liberarLista(listaDePrimos);
    liberarLista(listaDeFibonacci);

    return 0;
}
