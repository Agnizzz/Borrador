#pragma once
#include <iostream>
#include <conio.h>
#include <chrono> 
#include <functional>
#include "GestionCategorias.h"
#include "ArbolBB.h"

//SE HIZO CAMBIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOS

using namespace std;



// Árboles para indexar productos por diferentes atributos.
ArbolBinarioBusqueda<Categoria*> arbolPorId;
ArbolBinarioBusqueda<Categoria*> arbolPorNombre;
ArbolBinarioBusqueda<Categoria*> arbolPorPrecio;

// Para evitar fugas de memoria, usaremos tu clase Lista para guardar los punteros a las copias.
Lista<Categoria*> copiasDeProductos; 



// Bandera para asegurar que los árboles se construyan una sola vez.
bool arbolesDeBusquedaInicializados = false;

// Funciones de comparación (lambdas), no cambian.
auto comparadorPorId = [](const Categoria* a, const Categoria* b) {
    if (a->getID() < b->getID()) return -1;
    if (a->getID() > b->getID()) return 1;
    return 0;
    };

auto comparadorPorNombre = [](const Categoria* a, const Categoria* b) {
    if (a->getNombre() < b->getNombre()) return -1;
    if (a->getNombre() > b->getNombre()) return 1;
    return 0;
    };

auto comparadorPorPrecio = [](const Categoria* a, const Categoria* b) {
    if (a->getPrecioUnitario() < b->getPrecioUnitario()) return -1;
    if (a->getPrecioUnitario() > b->getPrecioUnitario()) return 1;
    return 0;
    };


// Función para poblar los árboles de búsqueda desde el catálogo principal.
void inicializarArbolesDeBusqueda() {
    if (arbolesDeBusquedaInicializados) {
        return;
    }

    for (int i = 1; i <= numCategoriasPrincipales; ++i) {
        try {
            const auto& subcategoriasMap = catalogo.getPorIdPrincipal(i);
            for (const auto& parSub : subcategoriasMap) {
                for (const auto& parTer : parSub.second) {
                    const Lista<Categoria>& listaProds = parTer.second;
                    for (int j = 0; j < listaProds.getTam(); ++j) {
                        const Categoria& productoOriginal = listaProds.getValor(j);

                        Categoria* copiaProducto = new Categoria(productoOriginal);

                        // CAMBIO: Usamos el método de tu lista (ej. agregaFinal) en lugar de push_back.
                        copiasDeProductos.agregaFinal(copiaProducto);

                        arbolPorId.insertar(copiaProducto, comparadorPorId);
                        arbolPorNombre.insertar(copiaProducto, comparadorPorNombre);
                        arbolPorPrecio.insertar(copiaProducto, comparadorPorPrecio);
                    }
                }
            }
        }
        catch (const std::out_of_range&) {
            continue;
        }
    }
    arbolesDeBusquedaInicializados = true;
    cout << "\nArboles de busqueda han sido inicializados." << endl;
}

// Función para limpiar las copias de productos creadas dinámicamente.
void limpiarRecursosDeBusqueda() {
    // CAMBIO: Iteramos sobre la Lista en lugar del vector.
    for (int i = 0; i < copiasDeProductos.longitud(); i++) {
        // Usamos el método para obtener el elemento (ej. obtenerPos o getValor).
        // Nota: Asegúrate de que el método devuelva un Categoria*.
        Categoria* ptr = copiasDeProductos.obtenerPos(i);
        delete ptr;
    }
    // Opcional: Si tu lista tiene un método para limpiarse, llámalo aquí.
    // ej. copiasDeProductos.limpiar();
	copiasDeProductos.limpiar(); // Asegúrate de que este método exista en tu clase Lista.
}


// Función principal para la búsqueda de productos del administrador (sin cambios en su lógica interna).
void buscarProductoAdmin() {
    system("cls");

    inicializarArbolesDeBusqueda();

    cout << "\n\n\t\t\t------ BUSCAR PRODUCTO EN CATALOGO ------" << endl;
    int opcion;
    cout << "\n\t\t\t1. Buscar por ID\n";
    cout << "\n\t\t\t2. Buscar por Nombre\n";
    cout << "\n\t\t\t3. Buscar por Precio\n";
    cout << "\n\t\t\t0. Volver al menu anterior\n";
    cout << "\n\t\t\tSeleccione una opcion: ";
    cin >> opcion;

    NodoArbol<Categoria*>* resultado = nullptr;
    Categoria claveBusqueda;

    switch (opcion) {
    case 1: {
        cout << "\n\t\t\tIngrese el ID del producto a buscar: ";
        string id;
        cin >> id;
        claveBusqueda.setID(id);
        resultado = arbolPorId.buscar(&claveBusqueda, comparadorPorId);
        break;
    }
    case 2: {
        cout << "\n\t\t\tIngrese el Nombre del producto a buscar: ";
        string nombre;
        cin.ignore();
        getline(cin, nombre);
        claveBusqueda.setNombre(nombre);
        resultado = arbolPorNombre.buscar(&claveBusqueda, comparadorPorNombre);
        break;
    }
    case 3: {
        cout << "\n\t\t\tIngrese el Precio a buscar: ";
        double precio;
        cin >> precio;
        claveBusqueda.setPrecioUnitario(precio);
        resultado = arbolPorPrecio.buscar(&claveBusqueda, comparadorPorPrecio);
        break;
    }
    case 0:
        return;
    default:
        cout << "\t\t\tOpcion invalida." << endl;
        break;
    }

    if (resultado != nullptr) {
        cout << "\n\t\t\t--- Producto Encontrado ---" << endl;
        resultado->dato->mostrarResumen();
        cout << "\n\t\t\tNota: Para editar o eliminar, use la funcion correspondiente con el ID del producto." << endl;
    }
    else {
        cout << "\n\t\t\tProducto no encontrado." << endl;
    }

    system("pause>0");
}

//FUNCION PARA REVISAR LA VENTAS DEL DÍA
void revisarVentasDelDia() {
    system("cls");
    cout << "\n\n\t\t\t------ REPORTE DE VENTAS DEL DIA ------" << endl;

    // --- 1. OBTENER LA FECHA DE HOY ---
    // Replicamos la lógica de tu clase Boleta para obtener la fecha en el formato correcto "d/m/aaaa"
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    string fechaHoy = to_string(timeinfo.tm_mday) + "/" +
        to_string(timeinfo.tm_mon + 1) + "/" +
        to_string(timeinfo.tm_year + 1900);

    cout << "\n\t\tFecha del reporte: " << fechaHoy << endl;
    cout << "\t\t-------------------------------------------" << endl;

    // --- 2. RECORRER LAS BOLETAS Y CALCULAR EL TOTAL ---
    double totalVentasDia = 0.0;
    int cantidadVentasDia = 0;

    // Suponemos que tu clase Lista tiene los métodos longitud() y obtenerPos()
    if (listaBoletas.esVacia()) {
        cout << "\n\t\tNo hay ventas registradas en el sistema." << endl;
    }
    else {
        // Primero, mostramos las boletas que coinciden con la fecha de hoy
        cout << "\n\t\tBoletas generadas hoy:" << endl;
        cout << left << setw(15) << "\t\tN. Boleta" << setw(30) << "Cliente" << setw(15) << "Total (S/.)" << endl;
        cout << "\t\t------------------------------------------------------------" << endl;

        for (int i = 0; i < listaBoletas.longitud(); i++) {
            Boleta* boletaActual = listaBoletas.obtenerPos(i);

            // Usamos el nuevo método getFecha() que acabamos de añadir
            if (boletaActual != nullptr && boletaActual->getFecha() == fechaHoy) {
                double totalBoleta = boletaActual->getTotal();
                cout << left << setw(15) << "\t\t" + to_string(boletaActual->getNumeroBoleta())
                    << setw(30) << boletaActual->getCliente()
                    << fixed << setprecision(2) << setw(15) << totalBoleta
                    << endl;

                totalVentasDia += totalBoleta;
                cantidadVentasDia++;
            }
        }

        if (cantidadVentasDia == 0) {
            cout << "\n\t\tNo se encontraron ventas para la fecha de hoy." << endl;
        }
    }

    // --- 3. MOSTRAR EL RESULTADO FINAL ---
    cout << "\n\t\t-------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "\n\t\t>> TOTAL DE VENTAS DEL DIA: S/. " << totalVentasDia << endl;
    cout << "\t\t>> Cantidad de transacciones: " << cantidadVentasDia << endl;

    cout << "\n\n";
    system("pause>0");
}

//funcion de procesar pedidos con el uso de COLAS
void procesarPedidos() {
    int opcion;
    do {
        system("cls");
        cout << "\n\n\t\t\t------ GESTION DE PEDIDOS PENDIENTES ------" << endl;

        if (colaDePedidos.esVacia()) {
            cout << "\n\t\t>> No hay pedidos pendientes en la cola." << endl;
            opcion = 0;
            system("pause>0");
        }
        else {
            // MOSTRAR TODOS LOS PEDIDOS PENDIENTES
            cout << "\n\t\tTotal de pedidos en cola: " << colaDePedidos.size() << endl;
            colaDePedidos.mostrarTodos();

            // MOSTRAR EL PRÓXIMO A PROCESAR
            Boleta* proximoPedido = colaDePedidos.frente();
            cout << "\n\t\t>>> PRÓXIMO PEDIDO A PROCESAR <<<" << endl;
            cout << "\t\t---------------------------------" << endl;
            cout << "\t\tBoleta Nro: " << proximoPedido->getNumeroBoleta() << endl;
            cout << "\t\tCliente: " << proximoPedido->getCliente() << endl;
            cout << fixed << setprecision(2);
            cout << "\t\tTotal: S/. " << proximoPedido->getTotal() << endl;
            cout << "\t\t---------------------------------" << endl;

            cout << "\n\t\t1. Procesar y Despachar Pedido (Desencolar)";
            cout << "\n\t\t2. Ver detalles del próximo pedido";
            cout << "\n\t\t0. Volver al Menu Principal";
            cout << "\n\n\t\tSeleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1: {
                Boleta* pedidoProcesado = colaDePedidos.desencolar();
                cout << "\n\t\t>> Pedido Nro. " << pedidoProcesado->getNumeroBoleta()
                    << " procesado y eliminado de la cola." << endl;
                cout << "\t\t>> Pedidos restantes en cola: " << colaDePedidos.size() << endl;
                system("pause>0");
                break;
            }
            case 2: {
                cout << "\n\t\t=== DETALLES DEL PEDIDO ===" << endl;
                proximoPedido->mostrarBoleta();
                system("pause>0");
                break;
            }
            case 0:
                break;
            default:
                cout << "\n\t\t>> Opción inválida." << endl;
                system("pause>0");
            }
        }
    } while (opcion != 0);
}

//funcion para gestionar las categorias
void gestionarCategoriasAdmin() {
    system("cls");
    cout << "\n\n\t\t\t------ GESTION CATEGORIAS ------" << endl;
    int opcion;
    cout << "\n\t\t\t1. Ver categorias\n";
    cout << "\n\t\t\t2. Agregar producto\n";
    cout << "\n\t\t\t3. Editar producto\n";
    cout << "\n\t\t\t4. Eliminar producto\n";
    cout << "\n\t\t\t5. Buscar Producto (Nuevo)\n"; // <-- NUEVA OPCIÓN
    cout << "\n\t\t\t6. Revisar Ventas del Dia (Nuevo)\n"; //Nuevo
    cout << "\n\t\t\t7. Procesar Pedidos Pendientes (Nuevo)\n"; // <-- NUEVA OPCIÓN
    cout << "\n\t\t\t0. Salir\n";
    cout << "\n\t\t\tSeleccione una opcion: ";
    cin >> opcion;
    switch (opcion) {
    case 1:
        gestionarCategorias();
        break;
    case 2:
		agregarProductoInteractivo(); // <-- MODIFICADO PARA AGREGAR PRODUCTO
        break;
    case 3:
        // Lógica para editar categoría
		editarProductoPorID(); // <-- MODIFICADO PARA EDITAR PRODUCTO
        break;
    case 4:
        // Lógica para eliminar categoría
		eliminarProductoPorID(); // <-- MODIFICADO PARA ELIMINAR PRODUCTO
        break;
    case 5: // <-- NUEVO CASE
        buscarProductoAdmin();
        break;
	case 6: // <-- NUEVO CASE
		revisarVentasDelDia(); // Nuevo
		break;
	case 7: // <-- NUEVO CASE
		procesarPedidos(); // Nuevo
		break;
    case 0:
        system("cls");
        break;
    default:
        cout << "\t\t\tOpcion invalida. Presione una tecla para continuar...";
        system("pause>0");
        system("cls");
    }
}



