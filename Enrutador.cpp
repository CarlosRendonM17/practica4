#include "enrutador.h"
#include <iostream>
#include <iomanip>
using namespace std;

Router::Router(int id) : id(id) {}

void Router::nuevoVecino(Router* vecino, int costo) {
    if (!vecino || vecino == this) return;
    vecinos[vecino] = costo;
}

void Router::eliminarVecino(Router* vecino) {
    if (!vecino) return;
    vecinos.erase(vecino);
}

string Router::getNombre() const {
    return "R" + to_string(id);
}

map<string, int> Router::getTabla() const {
    map<string, int> tabla;
    for (auto& [v, c] : vecinos)
        if (v) tabla[v->getNombre()] = c;
    return tabla;
}

void Router::mostrarConexiones() const {
    cout << getNombre() << " -> ";
    if (vecinos.empty()) cout << "sin conexiones";
    else {
        bool first = true;
        for (auto& [v, c] : vecinos) {
            if (!first) cout << ", ";
            cout << v->getNombre() << "(" << c << ")";
            first = false;
        }
    }
    cout << endl;
}

void Router::actualizarTabla(const map<string, pair<int, string>>& nueva) {
    tablaEnrutamiento = nueva;
}

void Router::agregarConexion(const string& nombreVecino, int costo) {
   
    (void)nombreVecino;
    (void)costo;
}

void Router::eliminarConexion(const string& nombreVecino) {
    for (auto it = vecinos.begin(); it != vecinos.end();) {
        if (it->first && it->first->getNombre() == nombreVecino)
            it = vecinos.erase(it);
        else
            ++it;
    }
}

void Router::mostrarTablaEnrutamiento(const map<string, pair<int, string>>& tabla) const {
    cout << "\nTabla de enrutamiento de " << getNombre() << ":\n";
    cout << setw(12) << "Destino" << setw(12) << "Costo" << " Siguiente\n";
    cout << string(40, '-') << "\n";
    for (auto& [dest, info] : tabla) {
        string costoStr = (info.first >= 100000000) ? "-" : to_string(info.first);
        cout << setw(12) << dest << setw(12) << costoStr << " " << info.second << "\n";
    }
}

void Router::mostrarTablaEnrutamiento() const {
    mostrarTablaEnrutamiento(tablaEnrutamiento);
}
