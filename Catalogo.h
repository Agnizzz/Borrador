#pragma once
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CategoriaGeneral.h"
#include "CategoriasEstructura.h"
#include "Lista.h"
#include "IDpropio.h"

using namespace std;

class Catalogo {
private:
    // Mapa: idPrincipal -> secundaria -> terciaria -> lista enlazada de productos
    map<int, map<string, map<string, Lista<Categoria>>>> productos;

public:
    Catalogo() { cargarDesdeArchivo("producto.txt"); }

    int buscarIndice(const string* arr, int tam, const string& valor) {
        for (int i = 0; i < tam; ++i)
            if (arr[i] == valor) return i + 1;
        return 0;
    }

    void cargarDesdeArchivo(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo: " << archivo << endl;
            return;
        }

        string linea;
        // Mapas para asignar índices únicos a secundaria y terciaria por nombre
        map<int, map<string, int>> secIndex;
        map<int, map<string, map<string, int>>> terIndex;
        map<int, map<string, map<string, int>>> prodIndex;

        while (getline(file, linea)) {
            if (linea.empty() || linea[0] == '#') continue;

            stringstream ss(linea);
            string idPrincipalStr, secundaria, terciaria, nombreProducto, precioUnitarioStr, unidadMedida;

            getline(ss, idPrincipalStr, ',');
            getline(ss, secundaria, ',');
            getline(ss, terciaria, ',');
            getline(ss, nombreProducto, ',');
            getline(ss, precioUnitarioStr, ',');
            getline(ss, unidadMedida, ',');

            if (idPrincipalStr.empty() || secundaria.empty() || terciaria.empty() ||
                nombreProducto.empty() || precioUnitarioStr.empty() || unidadMedida.empty()) {
                continue;
            }

            int idPrincipal;
            double precioUnitario;
            try {
                idPrincipal = stoi(idPrincipalStr);
                precioUnitario = stod(precioUnitarioStr);
            }
            catch (const std::exception& e) {
                cerr << "Error de conversión en línea: " << linea << "\nDetalle: " << e.what() << endl;
                continue;
            }

            // Índice de secundaria
            int idxSec = 0, idxTer = 0;
            if (idPrincipal == 1) { // Abarrotes
                idxSec = buscarIndice(subcategoriasAbarrotes, sizeof(subcategoriasAbarrotes) / sizeof(string), secundaria);
                if (secundaria == "Arroz")
                    idxTer = buscarIndice(terciariasArroz, sizeof(terciariasArroz) / sizeof(string), terciaria);
                else if (secundaria == "Conservas")
                    idxTer = buscarIndice(terciariasConservas, sizeof(terciariasConservas) / sizeof(string), terciaria);
				else if (secundaria == "Aceite")
					idxTer = buscarIndice(terciariasAceite, sizeof(terciariasAceite) / sizeof(string), terciaria);
				else if (secundaria == "Pasta")
					idxTer = buscarIndice(terciariasPasta, sizeof(terciariasPasta) / sizeof(string), terciaria);
				else if (secundaria == "Menestras")
					idxTer = buscarIndice(terciariasMenestras, sizeof(terciariasMenestras) / sizeof(string), terciaria);
				else if (secundaria == "Sal")
					idxTer = buscarIndice(terciariasSal, sizeof(terciariasSal) / sizeof(string), terciaria);
				else if (secundaria == "Salsas para Pasta")
					idxTer = buscarIndice(terciariasSalsasPasta, sizeof(terciariasSalsasPasta) / sizeof(string), terciaria);
				else if (secundaria == "Salsas/Cremas")
					idxTer = buscarIndice(terciariasSalsasCremas, sizeof(terciariasSalsasCremas) / sizeof(string), terciaria);
				else if (secundaria == "Condimentos")
					idxTer = buscarIndice(terciariasCondimentos, sizeof(terciariasCondimentos) / sizeof(string), terciaria);
				else if (secundaria == "Especias")
					idxTer = buscarIndice(terciariasEspecias, sizeof(terciariasEspecias) / sizeof(string), terciaria);
				else if (secundaria == "Puré, Sopas y Bases")
					idxTer = buscarIndice(terciariasPure, sizeof(terciariasPure) / sizeof(string), terciaria);
				else if (secundaria == "Harina")
					idxTer = buscarIndice(terciariasHarina, sizeof(terciariasHarina) / sizeof(string), terciaria);
                // ...y así para las demás subcategorías
            }

            // Índice de producto dentro de la terciaria
            int& idxP = prodIndex[idPrincipal][secundaria][terciaria];
            idxP++;

            // Generar el ID único
            string id = generarCodigo(idPrincipal, idxSec, idxTer, idxP);

            // Crear el producto (objeto Categoria)
            Categoria producto;
            producto.setID(id);
            producto.setNombre(nombreProducto);
            producto.setUnidadMedida(unidadMedida);
            producto.setPrecioUnitario(precioUnitario);

            productos[idPrincipal][secundaria][terciaria].agregaFinal(producto);
        }
        file.close();
    }

    // Obtener todos los productos de una categoría principal
    const map<string, map<string, Lista<Categoria>>>& getPorIdPrincipal(int idPrincipal) const {
        return productos.at(idPrincipal);
    }

    // Obtener productos por secundaria y terciaria
    const Lista<Categoria>& getPorCategoria(int idPrincipal, const string& secundaria, const string& terciaria) const {
        return productos.at(idPrincipal).at(secundaria).at(terciaria);
    }

   //agregar nuevo producto
    void agregarProducto(const Categoria& nuevoProducto) {
        string id = nuevoProducto.getID();
		//no tengo la funcion extraer idPrincipal, secundaria y terciaria
		int idPrincipal = stoi(id.substr(0, 3)); // Extraer el ID principal
		// Extraer secundaria y terciaria del ID
		if (idPrincipal < 1 || idPrincipal > 19) {
			cerr << "ID principal inválido: " << idPrincipal << endl;
			return;
		}
		if (id.size() < 8) {
			cerr << "ID inválido: " << id << endl;
			return;
		}
		if (id.size() < 8 || id[3] != 'T' || id[6] != '0') {
			cerr << "ID inválido: " << id << endl;
			return;
		}
		// Extraer secundaria y terciaria
		// Asumiendo que extraerSecundaria y extraerTerciaria son funciones que extraen correctamente
		if (id.size() < 11) {
			cerr << "ID inválido: " << id << endl;
			return;
		}
		if (idPrincipal < 1 || idPrincipal > 19) {
			cerr << "ID principal inválido: " << idPrincipal << endl;
			return;
		}
		if (id.size() < 11 || id[3] != 'T' || id[6] != '0') {
			cerr << "ID inválido: " << id << endl;
			return;
		}

     
        string secundaria = extraerSecundaria(id);
        string terciaria = extraerTerciaria(id);
		string id2 = generarCodigo(idPrincipal, buscarIndice(subcategoriasAbarrotes, sizeof(subcategoriasAbarrotes) / sizeof(string), secundaria),
			buscarIndice(terciariasArroz, sizeof(terciariasArroz) / sizeof(string), terciaria), 1);


        if (productos.find(idPrincipal) == productos.end()) {
            productos[idPrincipal] = map<string, map<string, Lista<Categoria>>>();
        }
        if (productos[idPrincipal].find(secundaria) == productos[idPrincipal].end()) {
            productos[idPrincipal][secundaria] = map<string, Lista<Categoria>>();
        }
        if (productos[idPrincipal][secundaria].find(terciaria) == productos[idPrincipal][secundaria].end()) {
            productos[idPrincipal][secundaria][terciaria] = Lista<Categoria>();
        }

        productos[idPrincipal][secundaria][terciaria].agregaFinal(nuevoProducto);
    }
};