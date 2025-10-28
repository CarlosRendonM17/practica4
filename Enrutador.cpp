#include "Enrutador.h"


Enrutador::Enrutador(const string& n) : nombre(n) {}


string Enrutador::getNombre() const {
    return nombre;
}


void Enrutador::setNombre(const string& n) {
    nombre = n;
}


void Enrutador::actualizarVecino(const string& destino, int costo) {
    if (costo > 0) {
        vecinos[destino] = costo;
    }
}


void Enrutador::eliminarVecino(const string& destino) {
    vecinos.erase(destino);
}


const unordered_map<string, int>& Enrutador::obtenerVecinos() const {
    return vecinos;
}


bool Enrutador::tieneVecino(const string& destino) const {
    return vecinos.find(destino) != vecinos.end();
}


int Enrutador::costoA(const string& destino) const {
    auto it = vecinos.find(destino);
    return (it != vecinos.end()) ? it->second : INF;
}
