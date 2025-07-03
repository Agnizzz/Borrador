#pragma once
#include "Nodo.h"
#include <iostream>
#include <functional>
#include <iomanip>

using namespace std;

typedef unsigned int uint;

template <class T>
class Lista {
private:
    Nodo<T>* ini;
    uint lon;

public:
    Lista() : ini(nullptr), lon(0) {}
    ~Lista() {
        vaciarLista();
    }

    // Operaciones básicas
    bool esVacia() const { return lon == 0; }
    int getTam() const { return static_cast<int>(lon); }

    uint longitud() const;
    void agregaInicial(T elem);
    void agregaFinal(T elem);
    void agregaPos(T elem, uint pos);
    void eliminaInicial();
    void eliminaFinal();
    void eliminaPos(uint pos);

    //agregamos limpiar
    void limpiar();
	

    // ✅ Métodos de acceso corregidos
    T obtenerPos(uint pos) const;
    T& obtenerReferencia(uint pos);

    // ✅ Método específico para obtener punteros de forma segura
    T obtenerPuntero(uint pos) const;

    void setValor(int pos, T nuevoValor);

    // Funciones adicionales
    void reemplazarPos(uint pos, T nuevoElem);
    T buscarProducto(std::function<bool(T)> criterio);
    void vaciarLista();

    // Acceso por índice
    T getValor(int pos) const { return obtenerPos(pos); }

    // Mostrar lista
    void mostrar() const;
};

// Agrega al inicio
template <class T>
void Lista<T>::agregaInicial(T elem) {
    Nodo<T>* nuevo = new Nodo<T>(elem);
    nuevo->set_Sgte(ini);
    ini = nuevo;
    lon++;
}

// Agrega al final
template <class T>
void Lista<T>::agregaFinal(T elem) {
    if (esVacia()) {
        agregaInicial(elem);
        return;
    }

    Nodo<T>* aux = ini;
    while (aux->get_Sgte() != nullptr) {
        aux = aux->get_Sgte();
    }
    aux->set_Sgte(new Nodo<T>(elem));
    lon++;
}

// Agrega en posición
template <class T>
void Lista<T>::agregaPos(T elem, uint pos) {
    if (pos == 0) {
        agregaInicial(elem);
    }
    else if (pos >= lon) {
        agregaFinal(elem);
    }
    else {
        Nodo<T>* aux = ini;
        for (uint i = 1; i < pos; i++) {
            aux = aux->get_Sgte();
        }
        Nodo<T>* nuevo = new Nodo<T>(elem);
        nuevo->set_Sgte(aux->get_Sgte());
        aux->set_Sgte(nuevo);
        lon++;
    }
}

// Eliminar por posición
template <class T>
void Lista<T>::eliminaPos(uint pos) {
    if (pos >= lon) return;
    if (pos == 0) {
        eliminaInicial();
        return;
    }

    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos - 1; i++) {
        aux = aux->get_Sgte();
    }
    Nodo<T>* temp = aux->get_Sgte();
    aux->set_Sgte(temp->get_Sgte());
    delete temp;
    lon--;
}

template <class T>
void Lista<T>::eliminaInicial() {
    if (ini == nullptr) return;
    Nodo<T>* temp = ini;
    ini = ini->get_Sgte();
    delete temp;
    lon--;
}

template <class T>
void Lista<T>::eliminaFinal() {
    eliminaPos(lon - 1);
}

// ✅ Obtener por posición - versión segura
template <class T>
T Lista<T>::obtenerPos(uint pos) const {
    if (pos >= lon || ini == nullptr) {
        // Para punteros, devolver nullptr
        if constexpr (std::is_pointer_v<T>) {
            return nullptr;
        }
        // Para otros tipos, lanzar excepción
        throw out_of_range("Índice fuera de rango");
    }

    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos; ++i) {
        if (aux == nullptr) {
            if constexpr (std::is_pointer_v<T>) {
                return nullptr;
            }
            throw out_of_range("Nodo nulo encontrado");
        }
        aux = aux->get_Sgte();
    }

    if (aux == nullptr) {
        if constexpr (std::is_pointer_v<T>) {
            return nullptr;
        }
        throw out_of_range("Nodo nulo en posición solicitada");
    }

    return aux->get_Elem();
}

// ✅ Obtener referencia - versión segura
template <class T>
T& Lista<T>::obtenerReferencia(uint pos) {
    if (pos >= lon || ini == nullptr) {
        throw out_of_range("Índice fuera de rango");
    }

    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos; ++i) {
        if (aux == nullptr) {
            throw out_of_range("Nodo nulo encontrado");
        }
        aux = aux->get_Sgte();
    }

    if (aux == nullptr) {
        throw out_of_range("Nodo nulo en posición solicitada");
    }

    return aux->get_Elem();
}

// ✅ Método específico para obtener punteros de forma segura
template <class T>
T Lista<T>::obtenerPuntero(uint pos) const {
    static_assert(std::is_pointer_v<T>, "Este método solo funciona con tipos puntero");

    if (pos >= lon || ini == nullptr) {
        return nullptr;
    }

    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos; ++i) {
        if (aux == nullptr) {
            return nullptr;
        }
        aux = aux->get_Sgte();
    }

    return (aux != nullptr) ? aux->get_Elem() : nullptr;
}

// Reemplazar por posición
template <class T>
void Lista<T>::reemplazarPos(uint pos, T nuevoElem) {
    if (pos >= lon) return;
    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos; ++i) {
        aux = aux->get_Sgte();
    }
    aux->set_Elem(nuevoElem);
}

// Buscar por función lambda
template <class T>
T Lista<T>::buscarProducto(std::function<bool(T)> criterio) {
    Nodo<T>* aux = ini;
    while (aux != nullptr) {
        if (criterio(aux->get_Elem())) {
            return aux->get_Elem();
        }
        aux = aux->get_Sgte();
    }
    return T(); // Default
}

// Vaciar lista
template <class T>
void Lista<T>::vaciarLista() {
    while (!esVacia()) {
        eliminaInicial();
    }
}

template <class T>
uint Lista<T>::longitud() const {
    return lon;
}

// Mostrar lista
template <class T>
void Lista<T>::mostrar() const {
    Nodo<T>* aux = ini;
    int i = 1;
    while (aux != nullptr) {
        T elem = aux->get_Elem();
        if constexpr (std::is_pointer_v<T>) {
            if (elem != nullptr) {
                cout << "\t\t\t" << i << ". " << elem->getNombre() << endl;
            }
            else {
                cout << "\t\t\t" << i << ". (Producto nulo)" << endl;
            }
        }
        else {
            cout << "\t\t\t" << i << ". " << elem.getNombre() << endl;
        }
        aux = aux->get_Sgte();
        ++i;
    }
    if (i == 1) {
        cout << "\t\t\t(No hay productos en esta categoría)" << endl;
    }
}

template <class T>
void Lista<T>::setValor(int pos, T nuevoValor) {
    if (pos < 0 || pos >= (int)lon) return;

    Nodo<T>* actual = ini;
    for (int i = 0; i < pos && actual != nullptr; ++i) {
        actual = actual->get_Sgte();
    }

    if (actual != nullptr) {
        actual->set_Elem(nuevoValor);
    }
}
template <class T>
void Lista<T>::limpiar() {
	vaciarLista();
	ini = nullptr;
	lon = 0;
}
