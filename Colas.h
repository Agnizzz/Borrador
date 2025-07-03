#pragma once
#include "Nodo.h"
#include <iostream>
using namespace std;

template <class T>
class Cola
{
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;
public:
    Cola()
    {
        this->inicio = nullptr;
        this->fin = nullptr;
    }
    void encolar(T v);
    T desencolar();
    bool esVacia() const;
    // NUEVO MÉTODO para ver el primer elemento sin quitarlo
    T frente() const {
        if (esVacia()) {
            throw std::out_of_range("La cola está vacía");
        }
        return inicio->get_Elem();
    }
    void mostrarTodos() const;
    int size() const;
};

template <class T>
bool Cola<T>::esVacia() const {
    return (inicio == nullptr);
}

template <class T>
void Cola<T>::encolar(T v) {
    Nodo<T>* nodo = new Nodo<T>(v);
    if (esVacia()) {
        inicio = nodo;
        fin = inicio;
    }
    else {
        fin->set_Sgte(nodo);
        fin = nodo;
    }
}

template <class T>
T Cola<T>::desencolar() {
    if (esVacia()) {
        throw std::out_of_range("La cola está vacía");
    }
    T dato = inicio->get_Elem();
    Nodo<T>* temp = inicio;
    inicio = inicio->get_Sgte();
    delete temp;
    if (inicio == nullptr) {
        fin = nullptr;
    }
    return dato;
}

// ✅ IMPLEMENTACIÓN CORRECTA - Como método de la clase Cola
template <class T>
void Cola<T>::mostrarTodos() const {
    if (esVacia()) {
        cout << "\t\t>> No hay pedidos pendientes." << endl;
        return;
    }

    cout << "\n\t\t=== TODOS LOS PEDIDOS PENDIENTES ===" << endl;
    Nodo<T>* actual = inicio;
    int contador = 1;

    while (actual != nullptr) {
        T elemento = actual->get_Elem();
        cout << "\t\t" << contador << ". ";
        // Para Boleta*, ajusta estos métodos según tu clase Boleta
        cout << "Boleta Nro: " << elemento->getNumeroBoleta()
            << " - Cliente: " << elemento->getCliente()
            << " - Total: S/. " << elemento->getTotal() << endl;

        actual = actual->get_Sgte();
        contador++;
    }
    cout << "\t\t=======================================" << endl;
}

// ✅ IMPLEMENTACIÓN CORRECTA - Como método de la clase Cola
template <class T>
int Cola<T>::size() const {
    if (esVacia()) return 0;

    int contador = 0;
    Nodo<T>* actual = inicio;
    while (actual != nullptr) {
        contador++;
        actual = actual->get_Sgte();
    }
    return contador;
}