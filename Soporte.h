#pragma once
#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include "Pilas.h"

using namespace std;

stack<string> pilaaReclamos;
const string ARCHIVO_RECLAMOS = "Reclamos.txt";
class CartadeReclamos {
private:
    Pila<string>* pilaReclamos;
public:
    CartadeReclamos() {
        pilaReclamos = new Pila<string>();
    }
    ~CartadeReclamos() {
        delete pilaReclamos;
    }
    void guardarPilaEnArchivo() {
        ofstream archivo(ARCHIVO_RECLAMOS, ios::trunc);
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo." << endl;
            return;
        }
        stack<string> aux = pilaaReclamos;
        while (!aux.empty()) {
            archivo << aux.top() << "\n";
            aux.pop();
        }
        cout << "\n\t\tGuardando reclamo en el sistema." << endl;
        Sleep(2000);
    }

    void cargarPilaDesdeArchivo() {
        ifstream archivo(ARCHIVO_RECLAMOS);
        if (!archivo.is_open()) return;
        stack<string> temp;
        string linea;
        while (getline(archivo, linea)) {
            temp.push(linea);
        }
        archivo.close();
        while (!temp.empty()) {
            pilaaReclamos.push(temp.top());
            temp.pop();
        }
    }

    void ingresarReclamo() {
        cin.ignore(INT_MAX, '\n');
        string reclamo;
        cout << "\n\t\tIngrese su reclamo:\n\t\t";
        getline(cin, reclamo);
        pilaaReclamos.push(reclamo);
        guardarPilaEnArchivo();
        cout << "\n\t\tSu reclamo ha sido registrado correctamente." << endl;
    }

};
