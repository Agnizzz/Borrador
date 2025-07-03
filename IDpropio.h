#pragma once
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

inline string generarCodigo(int idPr, int idxSec, int idxTer, int idxP) {
    string pref;
    switch (idPr) {
    case  1: pref = "ABA"; break;
    case  2: pref = "DES"; break;
    case  3: pref = "LAQ"; break;
    case  4: pref = "HUF"; break;
    case  5: pref = "FRU"; break;
    case  6: pref = "CAR"; break;
    case  7: pref = "PES"; break;
    case  8: pref = "CON"; break;
    case  9: pref = "PAN"; break;
    case 10: pref = "DUL"; break;
    case 11: pref = "SNA"; break;
    case 12: pref = "CER"; break;
    case 13: pref = "BAL"; break;
    case 14: pref = "GAJ"; break;
    case 15: pref = "LIM"; break;
    case 16: pref = "CUP"; break;
    case 17: pref = "BEA"; break;
    case 18: pref = "BBN"; break;
    case 19: pref = "MMA"; break;
    default:
        pref = to_string(idPr);
        while (pref.size() < 3) pref = "0" + pref;
    }
    ostringstream oss;
    oss << pref
        << setw(2) << setfill('0') << idxSec
        << 'T'
        << setw(2) << setfill('0') << idxTer << '0'
        << setw(2) << setfill('0') << idxP;
    return oss.str();

}
inline string extraerSecundaria(const string& id) {
    return id.substr(3, 2);
}

inline string extraerTerciaria(const string& id) {
    return id.substr(6, 2);
}



//funcion de ingresar un id principal, secundaria y terciaria para agregar un nuevo producto







	



