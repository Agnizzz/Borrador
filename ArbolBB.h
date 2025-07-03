#pragma once
#include <functional>
#include <iostream>

// Estructura del Nodo para el árbol
template <typename T>
struct NodoArbol {
    T dato;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(T d) : dato(d), izq(nullptr), der(nullptr) {}
};

// Clase del Árbol Binario de Búsqueda
template <typename T>
class ArbolBinarioBusqueda {
private:
    NodoArbol<T>* raiz;

    // Método auxiliar privado para insertar un nodo recursivamente
    void insertar(NodoArbol<T>*& nodo, T dato, const std::function<int(T, T)>& comparador) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>(dato);
        }
        else {
            int cmp = comparador(dato, nodo->dato);
            if (cmp < 0) {
                insertar(nodo->izq, dato, comparador);
            }
            else if (cmp > 0) {
                insertar(nodo->der, dato, comparador);
            }
            // Si cmp es 0, el ítem está duplicado, así que no lo insertamos.
        }
    }

    // Método auxiliar privado para buscar un nodo recursivamente
    NodoArbol<T>* buscar(NodoArbol<T>* nodo, T clave, const std::function<int(T, T)>& comparador) {
        if (nodo == nullptr) {
            return nullptr;
        }

        int cmp = comparador(clave, nodo->dato);
        if (cmp == 0) {
            return nodo; // Encontrado
        }
        else if (cmp < 0) {
            return buscar(nodo->izq, clave, comparador);
        }
        else {
            return buscar(nodo->der, clave, comparador);
        }
    }

    // Método auxiliar privado para limpiar el árbol y liberar memoria
    void destruir(NodoArbol<T>* nodo) {
        if (nodo) {
            destruir(nodo->izq);
            destruir(nodo->der);
            // Si T es un puntero, el objeto al que apunta debe ser eliminado por separado.
            delete nodo;
        }
    }


public:
    ArbolBinarioBusqueda() : raiz(nullptr) {}

    ~ArbolBinarioBusqueda() {
        destruir(raiz);
    }

    // Método público para insertar datos
    // La función de comparación debe devolver:
    // -1 si a < b
    //  0 si a == b
    //  1 si a > b
    void insertar(T dato, const std::function<int(T, T)>& comparador) {
        insertar(raiz, dato, comparador);
    }

    // Método público para buscar datos
    NodoArbol<T>* buscar(T clave, const std::function<int(T, T)>& comparador) {
        return buscar(raiz, clave, comparador);
    }
};