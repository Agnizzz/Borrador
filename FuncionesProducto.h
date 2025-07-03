#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "CategoriasEstructura.h"

//SE HIZO CAMBIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOS
using namespace std;

struct ProductoArchivo {
    string idPrincipal;
    string secundaria;
    string terciaria;
    string nombreProducto;
    string precioUnitario;
    string unidadMedida;

    string toCSV() const {
        return idPrincipal + "," + secundaria + "," + terciaria + "," +
            nombreProducto + "," + precioUnitario + "," + unidadMedida;
    }
};

// Mostrar opciones y devolver índice seleccionado
int mostrarOpciones(const string* opciones, int cantidad, const string& mensaje) {
    cout << mensaje << endl;
    for (int i = 0; i < cantidad; ++i) {
        cout << i + 1 << ". " << opciones[i] << endl;
    }
    int opcion;
    do {
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > cantidad);
    cin.ignore();
    return opcion - 1;
}

// Agrega un producto al archivo producto.txt
void agregarProducto(const ProductoArchivo& producto) {
    ofstream file("producto.txt", ios::app);
    if (!file.is_open()) {
        cerr << "No se pudo abrir producto.txt para agregar." << endl;
        return;
    }
    file << producto.toCSV() << endl;
    file.close();
}

// Agregar producto
void agregarProductoInteractivo() {
    // 1. Categoría principal
	system("cls");
    int idxCat = mostrarOpciones(categoriasPrincipales, numCategoriasPrincipales, "Categorias:");
    string idPrincipal = to_string(idxCat + 1);

    // 2. Subcategoría
    const string* subcats = subcategoriasPorCategoria[idxCat];
    int numSubcats = numSubcategoriasPorCategoria[idxCat];
	system("cls");
    int idxSub = mostrarOpciones(subcats, numSubcats, "Subcategorias:");
    string secundaria = subcats[idxSub];

    // 3. Terciaria
    const string* tercs = terciariasPorSubcategoria[idxCat][idxSub];
    int numTercs = numTerciariasPorSubcategoria[idxCat][idxSub];
	system("cls");
    int idxTer = mostrarOpciones(tercs, numTercs, "Opciones:");
    string terciaria = tercs[idxTer];

    // 4. Datos del producto
    ProductoArchivo prod;
    prod.idPrincipal = idPrincipal;
    prod.secundaria = secundaria;
    prod.terciaria = terciaria;
    cout << "Nombre del producto: ";
    getline(cin, prod.nombreProducto);
    cout << "Precio unitario: ";
    getline(cin, prod.precioUnitario);
    cout << "Unidad de medida: ";
    getline(cin, prod.unidadMedida);

    agregarProducto(prod);
    cout << "Producto agregado correctamente." << endl;
}

// Editar producto por ID
void editarProductoPorID() {
    cout << "Ingrese el ID del producto a editar: ";
    string id;
    cin >> id;
    cin.ignore();

    ifstream file("producto.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir producto.txt para editar." << endl;
        return;
    }

    // Contar líneas
    int n = 0;
    string linea;
    while (getline(file, linea)) n++;
    file.clear();
    file.seekg(0);

    string* lineas = new string[n];
    int i = 0;
    bool encontrado = false;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string idArchivo;
        getline(ss, idArchivo, ',');
        if (idArchivo == id && !encontrado) {
            ProductoArchivo prodEditado;
            prodEditado.idPrincipal = idArchivo;
            getline(ss, prodEditado.secundaria, ',');
            getline(ss, prodEditado.terciaria, ',');
            cout << "Nuevo nombre: ";
            getline(cin, prodEditado.nombreProducto);
            cout << "Nuevo precio unitario: ";
            getline(cin, prodEditado.precioUnitario);
            cout << "Nueva unidad de medida: ";
            getline(cin, prodEditado.unidadMedida);
            lineas[i++] = prodEditado.toCSV();
            encontrado = true;
        }
        else {
            lineas[i++] = linea;
        }
    }
    file.close();

    if (encontrado) {
        ofstream outFile("producto.txt");
        for (int j = 0; j < n; ++j) outFile << lineas[j] << endl;
        outFile.close();
        cout << "Producto editado correctamente." << endl;
    }
    else {
        cerr << "No existe un producto con ese ID." << endl;
    }
    delete[] lineas;
}

// Eliminar producto por ID
void eliminarProductoPorID() {
    cout << "Ingrese el ID del producto a eliminar: ";
    string id;
    cin >> id;
    cin.ignore();

    ifstream file("producto.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir producto.txt para eliminar." << endl;
        return;
    }

    int n = 0;
    string linea;
    while (getline(file, linea)) n++;
    file.clear();
    file.seekg(0);

    string* lineas = new string[n];
    int i = 0, m = 0;
    bool eliminado = false;
    ProductoArchivo prod;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string idArchivo;
        getline(ss, idArchivo, ',');
        if (idArchivo == id && !eliminado) {
            // Mostrar datos del producto
            prod.idPrincipal = idArchivo;
            getline(ss, prod.secundaria, ',');
            getline(ss, prod.terciaria, ',');
            getline(ss, prod.nombreProducto, ',');
            getline(ss, prod.precioUnitario, ',');
            getline(ss, prod.unidadMedida, ',');
            cout << "ID: " << prod.idPrincipal << endl;
            cout << "Nombre: " << prod.nombreProducto << endl;
            cout << "Precio unitario: " << prod.precioUnitario << endl;
            cout << "Unidad de medida: " << prod.unidadMedida << endl;
            eliminado = true;
            continue;
        }
        lineas[m++] = linea;
    }
    file.close();

    if (eliminado) {
        ofstream outFile("producto.txt");
        for (int j = 0; j < m; ++j) outFile << lineas[j] << endl;
        outFile.close();
        cout << "Producto eliminado correctamente." << endl;
    }
    else {
        cerr << "No existe un producto con ese ID." << endl;
    }
    delete[] lineas;
}