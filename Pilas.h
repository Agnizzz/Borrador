#pragma once
#include <stack>
#include "Nodo.h"

using namespace std;

template <class T>
class Pila {
private:
    Nodo<T>* tope;

public:
    Pila() {
        tope = nullptr;
    }

    void apilar(T v);
    T desapilar();
    bool esVacia();
};
template <class T>
void Pila<T>::apilar(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v);
    nuevo->set_Sgte(tope);
    tope = nuevo;
}
template <class T>
T Pila<T>::desapilar() {
    if (esVacia()) {
        return T();
    }
    else {
        Nodo<T>* nodoTemp = tope;
        T elemento = nodoTemp->get_Elem();
        tope = tope->get_Sgte();
        delete nodoTemp;
        return elemento;
    }
}
template <class T>
bool Pila<T>::esVacia() {
    return tope == nullptr;
}


