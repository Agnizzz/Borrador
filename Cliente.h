#pragma once
#include <iostream>
#include <conio.h>
#include <algorithm> 
#include <cmath>     
#include <cctype> 
#include "MetOrg.h"
#include"Usuario.h"

//SE HIZO CAMBIOSSSSSS

using namespace std;
//variables globales

Lista<Categoria> listaProductos;
HashTable<Boleta*> tablaBoletas;

 Lista<Boleta*> listaBoletas;


User usuarioActual;
//para ignorar mayusuclas
string toLowerCase(const string& str) {
	string result = str;
	for (char& c : result)
		c = tolower(c);
	return result;
}

void comprar() {
	gestionarCategorias(true);
}
void verCarrito() {
	system("cls");
	system("cls");

	// Encabezado visual
	setColor(15, 4);
	cout << "                              SUPERMERCADO VIRTUAL                                         \n";
	setColor(0, 14);
	cout << "                                CARRITO DE COMPRAS                                         \n";
	setColor(0, 7);
	cout << left
		<< setw(5) << "ID"
		<< setw(45) << "Producto"
		<< setw(12) << "Cantidad"
		<< setw(12) << "Precio (S/.)" << endl;
	setColor(15, 0);

	if (productosSeleccionados->esVacia()) {
		cout << "\n\t\t\tNo hay productos en el carrito." << endl;
	}
	else {
		for (int i = 0; i < productosSeleccionados->longitud(); i++) {
			Categoria* producto = productosSeleccionados->getValor(i);
			float precioTotal = producto->getPrecioUnitario() * producto->getCantidad();

			cout << left
				<< setw(5) << (i + 1)
				<< setw(45) << producto->getNombre()
				<< setw(12) << producto->getCantidad()
				<< fixed << setprecision(2)
				<< "S/. " << precioTotal << endl;
		}
	}

	cout << endl;
	system("pause>0");
	system("pause>0");
}
void eliminarProducto() {
	system("cls");
	cout << "\n\t\t\t-- Eliminar Producto --" << endl;
	if (productosSeleccionados->esVacia()) {
		cout << "\n\t\t\tNo hay productos en el carrito." << endl;
	}
	else {
		cout << "\n\t\t\tProductos en el carrito:" << endl;
		for (int i = 0; i < productosSeleccionados->longitud(); i++) {
			Categoria* producto = productosSeleccionados->getValor(i);
			cout << "\t\t\t" << (i + 1) << ". " << producto->getNombre() << " - Cantidad: " << producto->getCantidad() << endl;
		}
		int opcion;
		cout << "\n\t\t\tSeleccione el producto a eliminar (0 para cancelar): ";
		cin >> opcion;
		if (opcion > 0 && opcion <= productosSeleccionados->longitud()) {
			productosSeleccionados->eliminaPos(opcion - 1);
			cout << "\n\t\t\tProducto eliminado correctamente." << endl;
		}
		else if (opcion == 0) {
			cout << "\n\t\t\tOperación cancelada." << endl;
		}
		else {
			cout << "\n\t\t\tOpción inválida." << endl;
		}
	}
	system("pause>0");
}
void verOfertas() {
	system("cls");
	cout << "\n\t\t\t-- Ver Ofertas --" << endl;
	if (productosSeleccionados->esVacia()) {
		cout << "\n\t\t\tNo hay productos en el carrito." << endl;
	}
	else {
		cout << "\n\t\t\tOfertas disponibles:" << endl;
		for (int i = 0; i < productosSeleccionados->longitud(); i++) {
			Categoria* producto = productosSeleccionados->getValor(i);
			if (producto->getPrecioDescuento() > 0) {
				cout << "\t\t\t" << (i + 1) << ". " << producto->getNombre()
					<< " - Precio Original: S/." << producto->getPrecioUnitario()
					<< " - Precio con Descuento: S/." << producto->getPrecioDescuento()
					<< endl;
			}
		}
	}
	system("pause>0");
}
void procesarCompra() {

}

Categoria** convertirAArreglo(Lista<Categoria*>* lista, int& n) {
	n = lista->longitud();
	Categoria** arreglo = new Categoria * [n];
	for (int i = 0; i < n; ++i) {
		arreglo[i] = lista->getValor(i);  // ya es puntero
	}
	return arreglo;
}

//comparadores por nombre, precio y cantidad para el metodo binary search
bool compararPorNombre(const Categoria* a, const Categoria* b) {
	return toLowerCase(a->getNombre()) < toLowerCase(b->getNombre());
}
bool compararPorPrecio(const Categoria* a, const Categoria* b) {
	return a->getPrecioUnitario() < b->getPrecioUnitario();
}
bool compararPorCantidad(const Categoria* a, const Categoria* b) {
	return a->getCantidad() < b->getCantidad();
}
bool compararPorPrecioPtr(const Categoria* a, const Categoria* b) {
	return a->getPrecioUnitario() < b->getPrecioUnitario();
}
//aca van los metodos binary search para buscar por nombre, precio y cantidad
int binarySearchPorNombre(Categoria** productos, int n, const string& nombreBuscado) {
	string buscadoLower = toLowerCase(nombreBuscado);
	int izquierda = 0, derecha = n - 1;

	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		string actual = toLowerCase(productos[medio]->getNombre());

		if (actual == buscadoLower)
			return medio;
		else if (actual < buscadoLower)
			izquierda = medio + 1;
		else
			derecha = medio - 1;
	}
	return -1;
}

int binarySearchPorPrecio(Categoria** productos, int n, float precioBuscado) {
	int izquierda = 0, derecha = n - 1;

	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		float actual = productos[medio]->getPrecioUnitario();

		if (fabs(actual - precioBuscado) < 0.01f)
			return medio;
		else if (actual < precioBuscado)
			izquierda = medio + 1;
		else
			derecha = medio - 1;
	}
	return -1;
}

int binarySearchPorCantidad(Categoria** productos, int n, int cantidadBuscada) {
	int izquierda = 0, derecha = n - 1;

	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		int actual = productos[medio]->getCantidad();

		if (actual == cantidadBuscada)
			return medio;
		else if (actual < cantidadBuscada)
			izquierda = medio + 1;
		else
			derecha = medio - 1;
	}
	return -1;
}

//funcion para buscar en el que se incluira los 3 metodos binary search
void buscarProducto() {
	system("cls");
	cout << "\n\t\t\t--- BUSCAR PRODUCTO ---\n";
	cout << "\t\t\t1. Por nombre\n";
	cout << "\t\t\t2. Por precio\n";
	cout << "\t\t\t3. Por cantidad\n";
	cout << "\t\t\t0. Volver\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;

	if (opcion == 0) return;

	int n;
	Categoria** productos = convertirAArreglo(productosSeleccionados, n);
	if (opcion == 1) {
		sort(productos, productos + n, compararPorNombre);
		string nombre;
		cout << "\n\t\t\tIngrese el nombre a buscar: ";
		cin.ignore();
		getline(cin, nombre);
		int pos = binarySearchPorNombre(productos, n, nombre);
		if (pos != -1)
			cout << "\n\t\t\tProducto encontrado: " << productos[pos]->getNombre() << endl;
		else
			cout << "\n\t\t\tNo se encontró el producto.\n";
	}
	else if (opcion == 2) {
		sort(productos, productos + n, compararPorPrecio);
		float precio;
		cout << "\n\t\t\tIngrese el precio a buscar: ";
		cin >> precio;
		int pos = binarySearchPorPrecio(productos, n, precio);
		if (pos != -1)
			cout << "\n\t\t\tProducto encontrado: " << productos[pos]->getNombre()
			<< " - S/. " << productos[pos]->getPrecioUnitario() << endl;
		else
			cout << "\n\t\t\tNo se encontró ningún producto con ese precio.\n";
	}
	else if (opcion == 3) {
		sort(productos, productos + n, compararPorCantidad);
		int cantidad;
		cout << "\n\t\t\tIngrese la cantidad a buscar: ";
		cin >> cantidad;
		int pos = binarySearchPorCantidad(productos, n, cantidad);
		if (pos != -1)
			cout << "\n\t\t\tProducto encontrado: " << productos[pos]->getNombre()
			<< " - Cantidad: " << productos[pos]->getCantidad() << endl;
		else
			cout << "\n\t\t\tNo se encontro ningun producto con esa cantidad.\n";
	}
	else {
		cout << "\n\t\t\tOpcion invalida.\n";
	}

	delete[] productos;
	system("pause");
}

void merge(Categoria** arr, int left, int mid, int right, bool (*comparador)(const Categoria*, const Categoria*)) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	Categoria** L = new Categoria * [n1];
	Categoria** R = new Categoria * [n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (comparador(L[i], R[j])) {
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];

	delete[] L;
	delete[] R;
}

// mergeSort recursivo
void mergeSort(Categoria** arr, int left, int right, bool (*comparador)(const Categoria*, const Categoria*)) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid, comparador);
		mergeSort(arr, mid + 1, right, comparador);
		merge(arr, left, mid, right, comparador);
	}
}

void ordenarProductosAvanzado() {
	system("cls");
	cout << "\n\t\t\t--- ORDENAR PRODUCTOS ---\n";
	cout << "\t\t\t1. Por nombre\n";
	cout << "\t\t\t2. Por precio\n";
	cout << "\t\t\t3. Por cantidad\n";
	cout << "\t\t\t0. Volver\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;
	if (opcion == 0) return;

	int n;
	Categoria** productos = convertirAArreglo(productosSeleccionados, n); // no necesitas *

	if (opcion == 1) {
		mergeSort(productos, 0, n - 1, compararPorNombre);
	}
	else if (opcion == 2) {
		mergeSort(productos, 0, n - 1, compararPorPrecio);
	}
	else if (opcion == 3) {
		mergeSort(productos, 0, n - 1, compararPorCantidad);
	}
	else {
		cout << "\n\t\t\tOpcion invalida.\n";
		delete[] productos;
		return;
	}

	// Actualizar productosSeleccionados con el nuevo orden
	for (int i = 0; i < n; ++i) {
		productosSeleccionados->setValor(i, productos[i]);
	}

	// Mostrar productos ordenados
	cout << "\n\t\t\tProductos ordenados:\n";
	for (int i = 0; i < n; ++i) {
		cout << "\t\t\t" << (i + 1) << ". " << productos[i]->getNombre()
			<< " - S/. " << productos[i]->getPrecioUnitario()
			<< " - Cantidad: " << productos[i]->getCantidad() << endl;
	}

	delete[] productos;
	system("pause");
}

//generar boleta
void generarBoleta() {
	system("cls");

	if (productosSeleccionados->esVacia()) {
		cout << "\n No hay productos en el carrito." << endl;
		system("pause>0");
		return;
	}

	//  Obtener nombre y DNI del usuario actual desde la instancia global
	string nombreCliente = sistemaUsuarios->getUsuarioActual().nombre + " " +
		sistemaUsuarios->getUsuarioActual().apellido_paterno;
	string dni = sistemaUsuarios->getUsuarioActual().DNI;

	cout << "[DEBUG] Usuario actual: " << nombreCliente << " - DNI: " << dni << endl;

	int numeroBoleta = generarNumeroBoletaUnico();
	Boleta* nuevaBoleta = new Boleta(nombreCliente, dni, numeroBoleta);

	//  Verificar productos en el carrito
	cout << "\n Productos en carrito:\n";
	for (int i = 0; i < productosSeleccionados->longitud(); ++i) {
		Categoria* p = productosSeleccionados->getValor(i);
		if (p == nullptr) {
			cout << "- ⚠ Producto nulo en posición " << i << endl;
			continue;
		}
		cout << "- " << p->getNombre() << " x" << p->getCantidad() << endl;
	}

	//  Agregar productos (copias) a la boleta
	cout << "\nAgregando productos a la boleta...\n";
	for (int i = 0; i < productosSeleccionados->longitud(); ++i) {
		Categoria* producto = productosSeleccionados->getValor(i);
		if (producto->getNombre().empty() || producto->getPrecioUnitario() == 0) {
			cout << " Producto inválido, no se agregará a la boleta" << endl;
			continue;
		}
		Categoria* copia = new Categoria();
		copia->setNombre(producto->getNombre());
		copia->setCantidad(producto->getCantidad());
		copia->setPrecioUnitario(producto->getPrecioUnitario());

		// 👇 Asegúrate de pasar el descuento real (o uno por defecto)
		double descuento = producto->getPrecioDescuento();
		if (descuento == 0.0) {
			descuento = 0.2; // 20% si no tenía descuento
		}
		copia->setPrecioDescuento(descuento);

		nuevaBoleta->agregarProducto(copia);
		cout << "[DEBUG] Producto agregado: " << copia->getNombre()
			<< " - Cantidad: " << copia->getCantidad()
			<< " - Precio Unitario: S/. " << copia->getPrecioUnitario()
			<< " - Descuento: " << static_cast<int>(descuento * 100) << "%" << endl;
	}

	// 👉 Verificar si realmente se agregaron productos a la boleta
	if (nuevaBoleta->estaVacia()) {
		cout << "\n No se pudo generar la boleta. La boleta está vacía." << endl;
		delete nuevaBoleta;
		system("pause>0");
		return;
	}

	// 👉 Mostrar boleta
	cout << "\n Mostrando boleta:\n";
	nuevaBoleta->mostrarBoleta();

	// ✅ Insertar en HashTable y guardar
	cout << "[DEBUG] Insertando boleta con DNI: " << dni << endl;
	tablaBoletas.insertar(nuevaBoleta, dni);
	nuevaBoleta->guardarBoletaEnArchivo();

	// ✅ Agregar a listaBoletas para seguimiento (si lo estás usando)
	listaBoletas.agregaFinal(nuevaBoleta);

	// --- PASO NUEVO: AÑADIR EL PEDIDO A LA COLA DE PROCESAMIENTO ---
	colaDePedidos.encolar(nuevaBoleta);
	cout << "\n>> Pedido Nro. " << nuevaBoleta->getNumeroBoleta() << " ha sido enviado a la cola de procesamiento." << endl;
	// ----------------------------------------------------------------
	productosSeleccionados->limpiar();  //  Limpiar el carrito después de generar la boleta
	system("pause>0");
}

//menuregistro
void menuRegistro() {
	int opcion;

	do {
		system("cls");
		cout << "\n\t===== MENU CLIENTE =====\n";
		cout << "1. Generar boleta de compra\n";
		cout << "2. Buscar mis boletas por DNI\n";
		cout << "3. Salir\n";
		cout << "\n\t\t0. Cerrar Sesion" << endl; // <-- NUEVA OPCIÓN
		cout << "Seleccione una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 0: // Cerrar sesión
			sistemaUsuarios->cerrarSesion();
			cout << "\n\t\t\tCerrando sesión...\n";
			system("pause");
			productosSeleccionados->limpiar();  // <-- limpia el carrito del usuario anterior
			return; // Salir del menú de registro
		case 1:
			generarBoleta(); // Usa carrito y usuarioActual
			break;
		case 2: {
			string dniBuscar = sistemaUsuarios->getUsuarioActual().DNI;
			cout << "\nBuscando boletas para DNI: " << dniBuscar << "\n";
			tablaBoletas.buscarPorDNI(dniBuscar);
			system("pause");
			break;
		}
		case 3:
			cout << "Saliendo del menu...\n";
			break;
		default:
			cout << "Opcion no valida.\n";
			system("pause");
		}

	} while (opcion != 3);
}

//aca va el menu
void menuCarrito() {
	system("cls");
	cout << "\n\n\t\t\t------ MENU CARRITO ------" << endl;
	cout << "\n\t\t\t1. Comprar\n";
	cout << "\n\t\t\t2. Ver carrito\n";
	cout << "\n\t\t\t3. Eliminar producto\n";
	cout << "\n\t\t\t4. Ver ofertas\n";
	cout << "\n\t\t\t5. Procesar compra\n";
	cout << "\n\t\t\t6. Buscar producto\n"; 
	cout << "\n\t\t\t7. Ordenar productos\n";
	cout << "\n\t\t\t0. Salir\n";
	cout << "\n\t\t\tSeleccione una opcion: ";
	int opcion;
	cin >> opcion;

	if (opcion < 0 || opcion > 7) {
		cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
		system("pause>0");
		system("cls");
		return;
	}

	switch (opcion) {
	case 0:
		cout << "\n\t\t\tSALIENDO DEL SISTEMA..." << endl;
		break;
	case 1:
		comprar();
		break;
	case 2:
		verCarrito();
		break;
	case 3:
		eliminarProducto();
		break;
	case 4:
		verOfertas();
		break;
	case 5:
		procesarCompra();
		break;
	case 6:
		buscarProducto();
		break;
	case 7:
		ordenarProductosAvanzado();
		break;
	}
}

//uso de generador database
void generarProductosDePrueba(Lista<Categoria*>& productos) {
	for (int i = 1; i <= 10; ++i) {
		string nombre = "Producto" + to_string(i);
		int cantidad = 1 + rand() % 5;
		double precio = 5.0 + rand() % 20;

		Categoria* p = new Categoria(nombre, cantidad, precio);

		// ✅ Descuento entre 10% y 30%
		double descuento = (rand() % 21 + 10) / 100.0; // entre 0.10 y 0.30
		p->setPrecioDescuento(descuento);

		productos.agregaFinal(p);
	}
}