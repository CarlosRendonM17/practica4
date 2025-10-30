#include "Red.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ---------- MÉTODOS DE ENRUTADOR ----------

Enrutador::Enrutador(const string& n) : nombre(n) {}

string Enrutador::getNombre() const { return nombre; }

void Enrutador::setNombre(const string& n) { nombre = n; }

void Enrutador::actualizarVecino(const string& destino, int costo) {
    if (costo > 0)
        vecinos[destino] = costo;
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

// ---------- MÉTODOS DE RED ----------

bool Red::existe(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

void Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty()) {
        cout << "Nombre vacío no permitido.\n";
        return;
    }
    if (existe(nombre)) {
        cout << "Ya existe el enrutador " << nombre << "\n";
        return;
    }
    enrutadores.emplace(nombre, Enrutador(nombre));
    cout << "Enrutador " << nombre << " agregado.\n";
}

void Red::eliminarEnrutador(const string& nombre) {
    if (!existe(nombre)) {
        cout << "No existe " << nombre << "\n";
        return;
    }
    enrutadores.erase(nombre);
    for (auto& p : enrutadores) {
        p.second.eliminarVecino(nombre);
    }
    cout << "Enrutador " << nombre << " eliminado.\n";
}

void Red::actualizarEnlace(const string& a, const string& b, int costo) {
    if (a == b || !existe(a) || !existe(b) || costo <= 0) {
        cout << "Datos inválidos para enlace.\n";
        return;
    }
    enrutadores.at(a).actualizarVecino(b, costo);
    enrutadores.at(b).actualizarVecino(a, costo);
    cout << "Enlace " << a << " <-> " << b << " actualizado con costo " << costo << "\n";
}

void Red::borrarEnlace(const string& a, const string& b) {
    if (!existe(a) || !existe(b)) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    enrutadores.at(a).eliminarVecino(b);
    enrutadores.at(b).eliminarVecino(a);
    cout << "Enlace " << a << " - " << b << " eliminado.\n";
}

void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream f(nombreArchivo);
    if (!f) {
        cout << "No se pudo abrir archivo.\n";
        return;
    }
    enrutadores.clear();
    string linea;
    while (getline(f, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        stringstream ss(linea);
        string a, b;
        int costo;
        if (ss >> a >> b >> costo) {
            if (!existe(a)) agregarEnrutador(a);
            if (!existe(b)) agregarEnrutador(b);
            actualizarEnlace(a, b, costo);
        }
    }
    cout << "Topología cargada desde " << nombreArchivo << "\n";
}

void Red::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream f(nombreArchivo);
    if (!f) {
        cout << "No se pudo guardar archivo.\n";
        return;
    }
    for (const auto& [a, enr] : enrutadores) {
        for (const auto& [b, costo] : enr.obtenerVecinos()) {
            if (a < b)
                f << a << " " << b << " " << costo << "\n";
        }
    }
    cout << "Red guardada en " << nombreArchivo << "\n";
}

void Red::generarAleatoria(int n, int costoMax, double probEnlace) {
    if (n <= 0 || costoMax <= 0) {
        cout << "Parámetros inválidos.\n";
        return;
    }
    enrutadores.clear();
    for (int i = 0; i < n; ++i)
        agregarEnrutador("E" + to_string(i));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (((double)rand() / RAND_MAX) < probEnlace) {
                int costo = (rand() % costoMax) + 1;
                actualizarEnlace("E" + to_string(i), "E" + to_string(j), costo);
            }
    cout << "Red aleatoria generada.\n";
}

void Red::imprimirRed() const {
    cout << "=== Red Actual ===\n";
    if (enrutadores.empty()) {
        cout << "(vacía)\n";
        return;
    }
    for (const auto& [nombre, enr] : enrutadores) {
        cout << nombre << " -> ";
        const auto& vec = enr.obtenerVecinos();
        if (vec.empty()) {
            cout << "sin vecinos\n";
            continue;
        }
        bool primero = true;
        for (const auto& [dest, cost] : vec) {
            if (!primero) cout << ", ";
            cout << dest << "(" << cost << ")";
            primero = false;
        }
        cout << "\n";
    }
}

pair<int, vector<string>> Red::rutaMasCorta(const string& origen, const string& destino) const {
    if (!existe(origen) || !existe(destino)) return {-1, {}};

    using P = pair<int, string>;
    priority_queue<P, vector<P>, greater<P>> pq;
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;

    for (const auto& p : enrutadores) dist[p.first] = INF;
    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        if (u == destino) break;

        for (const auto& [v, costo] : enrutadores.at(u).obtenerVecinos()) {
            int nuevo = d + costo;
            if (nuevo < dist[v]) {
                dist[v] = nuevo;
                prev[v] = u;
                pq.push({nuevo, v});
            }
        }
    }

    if (dist[destino] == INF) return {-1, {}};

    vector<string> ruta;
    string actual = destino;
    while (actual != origen) {
        ruta.push_back(actual);
        actual = prev[actual];
    }
    ruta.push_back(origen);
    reverse(ruta.begin(), ruta.end());
    return {dist[destino], ruta};
}

void Red::preguntarRuta() const {
    cout << "Origen: ";
    string a; cin >> a;
    cout << "Destino: ";
    string b; cin >> b;
    auto [costo, ruta] = rutaMasCorta(a, b);
    if (costo == -1) {
        cout << "No hay ruta disponible.\n";
        return;
    }
    cout << "Costo total: " << costo << "\nRuta: ";
    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << ruta[i];
        if (i + 1 < ruta.size()) cout << " -> ";
    }
    cout << "\n";
}

vector<string> Red::listaEnrutadores() const {
    vector<string> nombres;
    for (const auto& p : enrutadores) nombres.push_back(p.first);
    sort(nombres.begin(), nombres.end());
    return nombres;
}
