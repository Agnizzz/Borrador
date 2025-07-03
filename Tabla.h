#pragma once
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include "CategoriaGeneral.h"
#include "Utilidades.h"
#include "Lista.h"

using namespace std;

//colocar variables globales seleccion y cantidad de que se muestre en la tabla
const int seleccionado = 0;
const int cantidad = 10;




void mostrarTablaProductos(const Lista<Categoria>& productos) {

    const int productosPorPagina = 10;
    int pagina = 0;
    int seleccionado = 0;
    int totalProductos = productos.getTam();
    int totalPaginas = (totalProductos + productosPorPagina - 1) / productosPorPagina;

    while (true) {
        system("cls");
        printHeader(); // Encabezado bonito

        int inicio = pagina * productosPorPagina;
        int fin = min(inicio + productosPorPagina, totalProductos);

        for (int i = inicio; i < fin; ++i) {
            const Categoria& prod = productos.getValor(i);

            if (i == seleccionado) setColor(0, 15); // Resaltado si está seleccionado
            else setColor(15, 0); // Normal

            cout << left << setw(15) << prod.getID().substr(0, 13)
                << setw(45) << prod.getNombre().substr(0, 44)
                << setw(10) << prod.getUnidadMedida().substr(0, 9)
                << "S/." << setw(8) << fixed << setprecision(2) << prod.getPrecioUnitario()
                << setw(10);

            if (prod.getPrecioDescuento() > 0.0)
                cout << fixed << setprecision(2) << prod.getPrecioDescuento();
            else
                cout << "";

            cout << endl;
        }

        setColor(15, 0); // Restaurar color normal
        cout << "\n[<-] Anterior  [->] Siguiente  [ESC] Salir\n";

        int key = _getch();
        if (key == 27) break; // ESC
        if (key == 224) {
            key = _getch();
            if (key == 72 && seleccionado > 0) seleccionado--; // Flecha arriba
            else if (key == 80 && seleccionado < totalProductos - 1) seleccionado++; // Flecha abajo
            else if (key == 75 && pagina > 0) pagina--; // Flecha izquierda
            else if (key == 77 && pagina < totalPaginas - 1) pagina++; // Flecha derecha
        }

        // Asegura que el resaltado esté dentro del rango de la página actual
        if (seleccionado < pagina * productosPorPagina)
            seleccionado = pagina * productosPorPagina;
        if (seleccionado >= fin)
            seleccionado = fin - 1;
    }
}

int seleccionarProductoEnTabla(const Lista<Categoria>& productos) {
    const int productosPorPagina = 10;
    int pagina = 0;
    int totalProductos = productos.getTam();
    int totalPaginas = (totalProductos + productosPorPagina - 1) / productosPorPagina;
    int seleccion = 0;

    while (true) {
        system("cls");
        printHeader();

        int inicio = pagina * productosPorPagina;
        int fin = min(inicio + productosPorPagina, totalProductos);
        for (int i = inicio; i < fin; ++i) {
            const Categoria& prod = productos.getValor(i);
            if (i == seleccion) setColor(0, 15); // Resalta la fila seleccionada
            else setColor(15, 0);

            cout << left << setw(15) << prod.getID().substr(0, 13)
                << setw(45) << prod.getNombre().substr(0, 44)
                << setw(10) << prod.getUnidadMedida().substr(0, 9)
                << "S/." << setw(8) << fixed << setprecision(2) << prod.getPrecioUnitario()
                << setw(10);
            if (prod.getPrecioDescuento() > 0.0)
                cout << fixed << setprecision(2) << prod.getPrecioDescuento();
            else
                cout << "";
            cout << endl;
        }

        setColor(15, 0);
        cout << "\n[] Mover  [<-] Anterior  [->] Siguiente  [Enter] Seleccionar  [ESC] Cancelar";

        int key = _getch();
        if (key == 27) {
            cout << "Cancelado por el usuario con ESC" << endl;
            system("pause");
            return -1;
        }       // ESC
        if (key == 13) return seleccion; // Enter
        if (key == 224) {
            key = _getch();
            if (key == 72 && seleccion > 0) seleccion--; // Flecha arriba
            else if (key == 80 && seleccion < totalProductos - 1) seleccion++; // Flecha abajo
            else if (key == 75 && pagina > 0) {
                pagina--;
                seleccion = pagina * productosPorPagina;
            }
            else if (key == 77 && pagina < totalPaginas - 1) {
                pagina++;
                seleccion = pagina * productosPorPagina;
            }
        }

        // Ajustar selección si se sale de rango
        if (seleccion < pagina * productosPorPagina)
            seleccion = pagina * productosPorPagina;
        if (seleccion >= min((pagina + 1) * productosPorPagina, totalProductos))
            seleccion = min((pagina + 1) * productosPorPagina, totalProductos) - 1;
    }
}


