#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "Catalogo.h"
#include "CategoriasEstructura.h"
#include "Tabla.h"
#include "Colas.h"
#include "Boleta.h"

using namespace std;

Catalogo catalogo;

//accedemos a  la lista.h para agregar un producto
Lista<Categoria*>* productosSeleccionados = new Lista<Categoria*>();
Cola<Boleta*> colaDePedidos;

Categoria gestionarCategorias(bool modoSeleccion = false) {

	system("cls");
	cout << "\n\t\t\t------ CATEGORIAS ------" << endl;
	int nCat = sizeof(categoriasPrincipales) / sizeof(categoriasPrincipales[0]);
	for (int i = 0; i < nCat; ++i) {
		cout << "\t\t\t" << (i + 1) << ". " << categoriasPrincipales[i] << endl;
	}
	cout << "\n\t\t\t0. Salir\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;

	switch (opcion) {
	case 0:
		system("cls");
		break;
	case 1: { // Abarrotes
		system("cls");
		int nSub = sizeof(subcategoriasAbarrotes) / sizeof(subcategoriasAbarrotes[0]);
		cout << "\n\t\t\t-- " << categoriasPrincipales[0] << " --" << endl;
		for (int i = 0; i < nSub; ++i) {
			cout << "\t\t\t" << (i + 1) << ". " << subcategoriasAbarrotes[i] << endl;
		}
		cout << "\n\t\t\t0. Salir\n";
		cout << "\n\t\t\tSeleccione una opcion: ";
		int subopcion;
		cin >> subopcion;
		if (subopcion == 1) { // Arroz
			system("cls");
			int nTer = sizeof(terciariasArroz) / sizeof(terciariasArroz[0]);
			cout << "\n\t\t\t-- " << subcategoriasAbarrotes[0] << " --" << endl;
			for (int i = 0; i < nTer; ++i) {
				cout << "\t\t\t" << (i + 1) << ". " << terciariasArroz[i] << endl;
			}
			cout << "\n\t\t\t0. Salir\n";
			cout << "\n\t\t\tSeleccione una opcion: ";
			int tercopcion;
			cin >> tercopcion;

			if (tercopcion > 0 && tercopcion <= nTer) {
				system("cls");
				string nombreTerciaria = terciariasArroz[tercopcion - 1];
				cout << "\n\t\t\t-- Productos de Arroz " << nombreTerciaria << " --" << endl;
				try {
					const Lista<Categoria>& productos = catalogo.getPorCategoria(1, "Arroz", nombreTerciaria);

					if (modoSeleccion) {
						int idx = seleccionarProductoEnTabla(productos);

						if (idx != -1) {
							const Categoria& seleccionado = productos.getValor(idx);
							// Pedir cantidad al usuario
							int cantidad;
							cout << "\nIngrese la cantidad que desea comprar: ";
							cin >> cantidad;

							// Crear una copia para modificarla y guardar cantidad (si la clase lo permite)
							Categoria* seleccionadoConCantidad = new Categoria(seleccionado);
							seleccionadoConCantidad->setCantidad(cantidad); // Asegúrate de tener este método
						
							productosSeleccionados->agregaInicial(seleccionadoConCantidad);
							cout << "Producto agregado correctamente" << endl;

							system("pause>0");
						}
					}
					else {
						mostrarTablaProductos(productos);
						system("pause>0");
					}
				}
				catch (const out_of_range&) {
					cout << "\t\t\tNo hay productos en esta categoría." << endl;
					system("pause>0");
				}
			}
			else if (tercopcion == 0) {
				system("cls");
			}
		}
		else if (subopcion == 2) { // Conservas
			system("cls");
			int nTer = sizeof(terciariasConservas) / sizeof(terciariasConservas[0]);
			cout << "\n\t\t\t-- " << subcategoriasAbarrotes[1] << " --" << endl;
			for (int i = 0; i < nTer; ++i) {
				cout << "\t\t\t" << (i + 1) << ". " << terciariasConservas[i] << endl;
			}
			cout << "\n\t\t\t0. Salir\n";
			cout << "\n\t\t\tSeleccione una opcion: ";
			int tercopcion;
			cin >> tercopcion;
			if (tercopcion > 0 && tercopcion <= nTer) {
				system("cls");
				string nombreTerciaria = terciariasConservas[tercopcion - 1];
				cout << "\n\t\t\t-- Productos de Conservas " << nombreTerciaria << " --" << endl;
				try {
					const Lista<Categoria>& productos = catalogo.getPorCategoria(1, "Conservas", nombreTerciaria);
					if (modoSeleccion) {
						int idx = seleccionarProductoEnTabla(productos);
						if (idx != -1) {
							const Categoria& seleccionado = productos.getValor(idx);
							// Pedir cantidad al usuario
							int cantidad;
							cout << "\nIngrese la cantidad que desea comprar: ";
							cin >> cantidad;

							// Crear una copia para modificarla y guardar cantidad (si la clase lo permite)
							Categoria* seleccionadoConCantidad = new Categoria(seleccionado);
							seleccionadoConCantidad->setCantidad(cantidad); // Asegúrate de tener este método

							productosSeleccionados->agregaInicial(seleccionadoConCantidad);
							cout << "Producto agregado correctamente" << endl;
							system("pause>0");
						}
					}
					else {
						mostrarTablaProductos(productos);
						system("pause>0");
					}
				}
				catch (const out_of_range&) {
					cout << "\t\t\tNo hay productos en esta categoría." << endl;
					system("pause>0");
				}
			}
			else if (tercopcion == 0) {
				system("cls");
			}
		}
		else if (subopcion == 3) { // Aceite
			system("cls");
			int nTer = sizeof(terciariasAceite) / sizeof(terciariasAceite[0]);
			cout << "\n\t\t\t-- " << subcategoriasAbarrotes[2] << " --" << endl;
			for (int i = 0; i < nTer; ++i) {
				cout << "\t\t\t" << (i + 1) << ". " << terciariasAceite[i] << endl;
			}
			cout << "\n\t\t\t0. Salir\n";
			cout << "\n\t\t\tSeleccione una opcion: ";
			int tercopcion;
			cin >> tercopcion;
			if (tercopcion > 0 && tercopcion <= nTer) {
				system("cls");
				string nombreTerciaria = terciariasAceite[tercopcion - 1];
				cout << "\n\t\t\t-- Productos de Aceite " << nombreTerciaria << " --" << endl;
				try {
					const Lista<Categoria>& productos = catalogo.getPorCategoria(1, "Aceite", nombreTerciaria);
					if (modoSeleccion) {
						int idx = seleccionarProductoEnTabla(productos);
						if (idx != -1) {
							const Categoria& seleccionado = productos.getValor(idx);
							// Pedir cantidad al usuario
							int cantidad;
							cout << "\nIngrese la cantidad que desea comprar: ";
							cin >> cantidad;

							// Crear una copia para modificarla y guardar cantidad (si la clase lo permite)
							Categoria* seleccionadoConCantidad = new Categoria(seleccionado);
							seleccionadoConCantidad->setCantidad(cantidad); // Asegúrate de tener este método

							productosSeleccionados->agregaInicial(seleccionadoConCantidad);
							cout << "Producto agregado correctamente" << endl;

							system("pause>0");
						}
					}
					else {
						mostrarTablaProductos(productos);
						system("pause>0");
					}
				}
				catch (const out_of_range&) {
					cout << "\t\t\tNo hay productos en esta categoría." << endl;
					system("pause>0");
				}
			}
			else if (tercopcion == 0) {
				system("cls");
			}
		}
		else if (subopcion == 4) { // Pasta
			system("cls");
			int nTer = sizeof(terciariasPasta) / sizeof(terciariasPasta[0]);
			cout << "\n\t\t\t-- " << subcategoriasAbarrotes[3] << " --" << endl;
			for (int i = 0; i < nTer; ++i) {
				cout << "\t\t\t" << (i + 1) << ". " << terciariasPasta[i] << endl;
			}
			cout << "\n\t\t\t0. Salir\n";
			cout << "\n\t\t\tSeleccione una opcion: ";
			int tercopcion;
			cin >> tercopcion;
			if (tercopcion > 0 && tercopcion <= nTer) {
				system("cls");
				string nombreTerciaria = terciariasPasta[tercopcion - 1];
				cout << "\n\t\t\t-- Productos de Pasta " << nombreTerciaria << " --" << endl;
				try {
					const Lista<Categoria>& productos = catalogo.getPorCategoria(1, "Pasta", nombreTerciaria);
					if (modoSeleccion) {
						int idx = seleccionarProductoEnTabla(productos);
						if (idx != -1) {
							const Categoria& seleccionado = productos.getValor(idx);
							// Pedir cantidad al usuario
							int cantidad;
							cout << "\nIngrese la cantidad que desea comprar: ";
							cin >> cantidad;

							// Crear una copia para modificarla y guardar cantidad (si la clase lo permite)
							Categoria* seleccionadoConCantidad = new Categoria(seleccionado);
							seleccionadoConCantidad->setCantidad(cantidad); // Asegúrate de tener este método

							productosSeleccionados->agregaInicial(seleccionadoConCantidad);
							cout << "Producto agregado correctamente" << endl;

							system("pause>0");
						}
					}
					else {
						mostrarTablaProductos(productos);
						system("pause>0");
					}
				}
				catch (const out_of_range&) {
					cout << "\t\t\tNo hay productos en esta categoría." << endl;
					system("pause>0");
				}
			}
			else if (tercopcion == 0) {
				system("cls");
			}
		}
		else if (subopcion == 5) { // Menestras
			system("cls");
			int nTer = sizeof(terciariasMenestras) / sizeof(terciariasMenestras[0]);
			cout << "\n\t\t\t-- " << subcategoriasAbarrotes[4] << " --" << endl;
			for (int i = 0; i < nTer; ++i) {
				cout << "\t\t\t" << (i + 1) << ". " << terciariasMenestras[i] << endl;
			}
			cout << "\n\t\t\t0. Salir\n";
			cout << "\n\t\t\tSeleccione una opcion: ";
			int tercopcion;
			cin >> tercopcion;
			if (tercopcion > 0 && tercopcion <= nTer) {
				system("cls");
				string nombreTerciaria = terciariasMenestras[tercopcion - 1];
				cout << "\n\t\t\t-- Productos de Menestras " << nombreTerciaria << " --" << endl;
				try {
					const Lista<Categoria>& productos = catalogo.getPorCategoria(1, "Menestras", nombreTerciaria);
					if (modoSeleccion) {
						int idx = seleccionarProductoEnTabla(productos);
						if (idx != -1) {
							const Categoria& seleccionado = productos.getValor(idx);
							// Pedir cantidad al usuario
							int cantidad;
							cout << "\nIngrese la cantidad que desea comprar: ";
							cin >> cantidad;

							// Crear una copia para modificarla y guardar cantidad (si la clase lo permite)
							Categoria* seleccionadoConCantidad = new Categoria(seleccionado);
							seleccionadoConCantidad->setCantidad(cantidad); // Asegúrate de tener este método

							productosSeleccionados->agregaInicial(seleccionadoConCantidad);
							cout << "Producto agregado correctamente" << endl;

							system("pause>0");
						}
					}
					else {
						mostrarTablaProductos(productos);
						system("pause>0");
					}
				}
				catch (const out_of_range&) {
					cout << "\t\t\tNo hay productos en esta categoría." << endl;
					system("pause>0");
				}
			}
			else if (tercopcion == 0) {
				system("cls");
			}
		}
		else if (subopcion == 0) {
			system("cls");
			break;
		}
		break;
	}
	case 2:
		cout << "\t\t\tDESAYUNOS" << endl;
		break;
	case 3:
		cout << "\t\t\tLACTEOS Y QUESOS" << endl;
		break;
	case 4:
		cout << "\t\t\tHUEVOS Y FIAMBRES" << endl;
		break;
	case 5:
		cout << "\t\t\tFRUTAS Y VERDURAS" << endl;
		break;
	case 6:
		cout << "\t\t\tCARNES" << endl;
		break;
	case 7:
		cout << "\t\t\tPESCADOS Y MARISCOS" << endl;
		break;
	case 8:
		cout << "\t\t\tCONGELADOS" << endl;
		break;
	case 9:
		cout << "\t\t\tPANADERIA Y PASTELERIA" << endl;
		break;
	case 10:
		cout << "\t\t\tDULCES Y GALLETAS" << endl;
		break;
	case 11:
		cout << "\t\t\tSNACK Y FRUTOS SECOS" << endl;
		break;
	case 12:
		cout << "\t\t\tCERVEZAS" << endl;
		break;
	case 13:
		cout << "\t\t\tBEBIDAS ALCOHOLICAS" << endl;
		break;
	case 14:
		cout << "\t\t\tGASEOSAS, AGUAS Y JUGOS" << endl;
		break;
	case 15:
		cout << "\t\t\tLIMPIEZA" << endl;
		break;
	case 16:
		cout << "\t\t\tCUIDADO PERSONAL" << endl;
		break;
	case 17:
		cout << "\t\t\tBELLEZA" << endl;
		break;
	case 18:
		cout << "\t\t\tBEBES Y NINOS" << endl;
		break;
	case 19:
		cout << "\t\t\tMUNDO MASCOTAS" << endl;
		break;
	default:
		cout << "\t\tOpción invalida\n";
		system("pause");
	}

	return Categoria();
	//char pausa = _getch(); // Captura el valor devuelto
}
