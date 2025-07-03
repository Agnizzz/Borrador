#include <iostream>
#include "Utilidades.h"
#include "Matrices.h"


using namespace std;


int main() {
	SetConsoleSize(160, 41);
	SetCursorVisible(false);

	Logo_UPC();
	Pantalla_carga();

	while (Menu()) {}

	return 0;
}
