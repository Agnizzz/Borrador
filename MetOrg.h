#pragma once
#include <list>
#include <string>
#include <iostream>
#include"GestionCategorias.h"
using namespace std;
//tabla hasheada para almacenar boletas
const int TAM_HASH = 10;
template <typename T>
class HashTable {
private:
    list<Boleta*> tabla[TAM_HASH];

    int hash(string dni) {
        int suma = 0;
        for (char c : dni) suma += c;
        return suma % TAM_HASH;
    }

public:
    void insertar(Boleta* b, string dni) {
        int indice = hash(dni);
        tabla[indice].push_back(b);
    }

    Boleta* buscar(string dni, int numeroBoleta) {
        int indice = hash(dni);
        for (Boleta* b : tabla[indice]) {
            if (b->getNumeroBoleta() == numeroBoleta) return b;
        }
        return nullptr;
    }

    void mostrarTodas() {
        for (int i = 0; i < TAM_HASH; ++i) {
            if (!tabla[i].empty()) {
                cout << "\n--- Boletas en índice " << i << " ---\n";
                for (Boleta* b : tabla[i]) {
                    b->mostrarBoleta();
                }
            }
        }
    }
    void buscarPorDNI(string dni) {
        int indice = hash(dni);
        bool encontrado = false;
        for (Boleta* b : tabla[indice]) {
            if (b->getDNI() == dni) {
                b->mostrarBoleta();
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron boletas con DNI: " << dni << endl;
        }
    }
};

