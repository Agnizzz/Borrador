#pragma once
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

class Categoria {
private:
    string id;
    string nombre;
    string unidadMedida;
    double precioUnitario;
    double precioDescuento=0.0;
    double precioFinal;
    int cantidad;

   

public:
    Categoria()
        : id(""), nombre(""), unidadMedida(""), precioUnitario(0.0), precioDescuento(0.0), precioFinal(0.0), cantidad(1) {
    }

    Categoria(const string& pId, const string& pNombre, const string& punidadMedida, int pCantidad = 1)
        : id(pId), nombre(pNombre), unidadMedida(punidadMedida), precioUnitario(0.0), precioDescuento(0.0), precioFinal(0.0), cantidad(pCantidad) {
    }
    Categoria(string _nombre, int _cantidad, double _precio) {
        nombre = _nombre;
        cantidad = _cantidad;
        precioUnitario = _precio;
    }
    double calcularPrecioFinal() const {
        double precioUnit = precioUnitario * (1.0 - precioDescuento); // precio con descuento
        return precioUnit * cantidad;
    }
    // Constructor copia explícito
    Categoria(const Categoria& otra)
        : id(otra.id),
        nombre(otra.nombre),
        unidadMedida(otra.unidadMedida),
        precioUnitario(otra.precioUnitario),
        precioDescuento(otra.precioDescuento),
        cantidad(otra.cantidad) {
        calcularPrecioFinal(); // Esto lo garantiza en cada copia
    }
 
    // Setters y getters (igual que antes)
    void setID(const string& pId) { id = pId; }
    const string& getID() const { return id; }
    void setNombre(const string& pNombre) { nombre = pNombre; }
    const string& getNombre() const { return nombre; }
    void setUnidadMedida(const string& punidadMedida) { unidadMedida = punidadMedida; }
    const string& getUnidadMedida() const { return unidadMedida; }
    void setPrecioUnitario(double pPrecio) { precioUnitario = pPrecio; calcularPrecioFinal(); }
    double getPrecioUnitario() const { return precioUnitario; }
    void setPrecioDescuento(double descuento) {precioDescuento = descuento;}// esto es porcentaje: 0.2 = 20%calcularPrecioFinal();
    double getPrecioDescuento() const { return precioDescuento; }
    void setCantidad(int pCantidad) { cantidad = pCantidad; calcularPrecioFinal(); }
    int getCantidad() const { return cantidad; }
    void setPrecioFinal(double) { calcularPrecioFinal(); }
    double getPrecioFinal() const { return precioFinal; }

    //para el descuento
    double getPrecioConDescuento() const {
        return precioUnitario * (1.0 - precioDescuento); //  correcto
    }

    // Fila para la boleta (dos líneas)
    string toTicketRow(int width = 40) const {
        ostringstream oss;
        double precioAplicado = (precioDescuento > 0.0) ? precioDescuento : precioUnitario;
        // Línea 1: ID a la izquierda, precio a la derecha
        oss << left << setw(width - 10) << id
            << "S/. " << right << setw(6) << fixed << setprecision(2) << precioAplicado << "\n";
        // Línea 2: Nombre - unidad xCantidad
        oss << nombre << " - " << unidadMedida << " x" << cantidad;
        return oss.str();
    }

    //mostrar
    void mostrarResumen() const {
        double precioAplicado = (precioDescuento > 0.0) ? precioDescuento : precioUnitario;
        cout << left << setw(15) << id
            << setw(30) << nombre
            << setw(10) << unidadMedida
            << "x" << setw(3) << cantidad
            << " -> S/." << fixed << setprecision(2) << precioFinal << endl;
    }
};
