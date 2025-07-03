#pragma once

template <class T>
class Nodo {
private:
	T elem;
	Nodo* sgte;
public:
	Nodo() : sgte(nullptr) {}
	Nodo(T pelem) : elem(pelem), sgte(nullptr) {}

	void set_Elem(T pelem) { elem = pelem; }

	T& get_Elem() { return elem; }         // <-- sin const y por referencia
	const T& get_Elem() const { return elem; }  // para versiones const

	void set_Sgte(Nodo* pSgte) { sgte = pSgte; }
	Nodo* get_Sgte() const { return sgte; }
};