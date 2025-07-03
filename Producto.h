#pragma once
#include <iostream>
#include <conio.h>
#include "GestionCategorias.h"
#include "FuncionesProducto.h"

using namespace std;

void categorias() {
	gestionarCategorias();
}

void funcionesProducto() {
    system("cls");
    cout << "\n\n\t\t\t------ FUNCIONES PRODUCTO ------" << endl;
	cout << "\n\t\t\t1. Agregar producto\n";
	cout << "\n\t\t\t2. Editar producto\n";
	cout << "\n\t\t\t3. Eliminar producto\n";
	cout << "\n\t\t\t0. Salir\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;
	if (opcion < 0 || opcion > 3) {
		cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
		system("pause>0");
		system("cls");
	}
	if (opcion == 0) {
		system("cls");
	}
	else if (opcion == 1) {
		agregarProductoInteractivo();
	}
	else if (opcion == 2) {
		editarProductoPorID();
	}
	else if (opcion == 3) {
		eliminarProductoPorID();
	}
    //char pausa = _getch(); // Captura el valor devuelto
}

void buscarProductos() {
    system("cls");
    cout << "\n\n\t\t\t------ BUSCAR PRODUCTOS ------" << endl;
	cout << "\n\t\t\t1. Buscar por ID\n";
	cout << "\n\t\t\t2. Buscar por nombre\n";
	cout << "\n\t\t\t3. Buscar por precio\n";
	cout << "\n\t\t\t0. Salir\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;
	if (opcion < 0 || opcion > 3) {
		cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
		system("pause>0");
		system("cls");
	}
	if (opcion == 0) {
		system("cls");
	}
	else if (opcion == 1) { 
		cout << "\t\t\tBUSCANDO POR ID..." << endl;
	}
	else if (opcion == 2) {
		cout << "\t\t\tBUSCANDO POR NOMBRE..." << endl;
	}
	else if (opcion == 3) {
		cout << "\t\t\tBUSCANDO POR PRECIO..." << endl;
	}
    //char pausa = _getch(); // Captura el valor devuelto 
}

void ordenarProductos() {
    system("cls");
    cout << "\n\n\t\t\t------ ORDENAR PRODUCTOS ------" << endl;
	cout << "\n\n\t\t\t1. Ordenar por precio\n";
	cout << "\n\t\t\t2. Ordenar por nombre\n";
	cout << "\n\t\t\t0. Salir\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;
	if (opcion < 0 || opcion > 2) {
		cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
		system("pause>0");
		system("cls");
	}
	if (opcion == 0) {
		system("cls");
	}
	else if (opcion == 1) {
		cout << "\t\t\tORDENANDO POR PRECIO..." << endl;
	}
	else if (opcion == 2) {
		cout << "\t\t\tORDENANDO POR NOMBRE..." << endl;
	}
    //char pausa = _getch(); // Captura el valor devuelto
}

void funcionesOferta() {
    system("cls");
    cout << "\n\n\t\t\t------ FUNCIONES OFERTA ------" << endl;
    cout << "\n\t\t\t1. Agregar oferta\n";
    cout << "\n\t\t\t2. Editar oferta\n";
    cout << "\n\t\t\t3. Eliminar oferta\n";
    cout << "\n\t\t\t4. Mostrar ofertas\n";
    cout << "\n\t\t\t0. Salir\n";
    cout << "\n\t\t\tSeleccione una opcion: ";
    int opcion;
    cin >> opcion;
    if (opcion < 0 || opcion > 4) {
        cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
		system("pause>0");
		system("cls");
    }
    if (opcion == 0) {
        system("cls");
    }
    else if (opcion == 1) {
        cout << "\t\t\tAGREGANDO OFERTA..." << endl;
    }
    else if (opcion == 2) {
        cout << "\t\t\tEDITANDO OFERTA..." << endl;
    }
    else if (opcion == 3) {
        cout << "\t\t\tELIMINANDO OFERTA..." << endl;
    }
    else if (opcion == 4) {
        cout << "\t\t\tMOSTRANDO OFERTAS..." << endl;
    }
    //char pausa = _getch(); // Captura el valor devuelto
}
