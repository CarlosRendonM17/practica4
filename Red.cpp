#include "red.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

const int INF = numeric_limits<int>::max() / 4; 

Red::Red() {}

Red::Red(int n) {
    for (int i = 1; i <= n; i++)
        enrutadores.push_back(new Router(i));
}

Red::~Red() {
    for (auto r : enrutadores) delete r;
}

int Red::cantidadEnrutadores() const {
    return enrutadores.size();
}

void Red::generarRedAleatoria() {
    for (auto r : enrutadores)
        r->vecinos.clear();

    int n = enrutadores.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int c = rand() % 20 + 1;
            enrutadores[i]->nuevoVecino(enrutadores[j], c);
            enrutadores[j]->nuevoVecino(enrutadores[i], c);
        }
}

void Red::mostrarRed() const {
    if (enrutadores.empty()) {
        cout << "Red vacia.\n";
        return;
    }

    cout << "\n========= MATRIZ DE COSTOS =========\n";
    // ancho de columna
    const int w = 6;
    cout << setw(6) << " ";
    for (auto r : enrutadores) cout << setw(w) << r->getNombre();
    cout << "\n";

    for (auto a : enrutadores) {
        cout << setw(6) << a->getNombre();
        for (auto b : enrutadores) {
            if (a == b) {
                cout << setw(w) << 0;
            } else {
                int c = INF;
                auto it = a->vecinos.find(b);
                if (it != a->vecinos.end()) c = it->second;
                if (c == INF) cout << setw(w) << "-";
                else cout << setw(w) << c;
            }
        }
        cout << "\n";
    }
    cout << "====================================\n";
}

void Red::mostrarTablasDeEnrutamiento() const {
    if (enrutadores.empty()) {
        cout << "Red vacia.\n";
        return;
    }

    for (auto origen : enrutadores) {
        origen->mostrarTablaEnrutamiento();
    }
}

void Red::agregarEnrutador() {
    int nuevoID = enrutadores.size() + 1;
    Router* r = new Router(nuevoID);
    enrutadores.push_back(r);
    cout << "✔ Enrutador " << r->getNombre() << " agregado.\n";
}

void Red::eliminarEnrutador(int id) {
    if (id <= 0 || id > enrutadores.size()) {
        cout << "❌ ID inválido.\n";
        return;
    }

    Router* borrar = enrutadores[id - 1];

    for (auto r : enrutadores)
        r->eliminarVecino(borrar);

    delete borrar;
    enrutadores.erase(enrutadores.begin() + (id - 1));

    for (int i = 0; i < enrutadores.size(); i++)
        enrutadores[i]->id = i + 1;

    cout << "✔ Router eliminado.\n";
}

void Red::agregarEnlaceSeguro(int id1, int id2, int costo) {
    if (id1 <= 0 || id2 <= 0 || id1 > enrutadores.size() || id2 > enrutadores.size()) {
        cout << "❌ IDs fuera de rango.\n";
        return;
    }
    if (id1 == id2) {
        cout << "❌ No se puede enlazar el mismo enrutador.\n";
        return;
    }

    Router* a = enrutadores[id1 - 1];
    Router* b = enrutadores[id2 - 1];

    a->nuevoVecino(b, costo);
    b->nuevoVecino(a, costo);

    cout << "✔ Enlace agregado.\n";
}

void Red::eliminarEnlaceSeguro(int id1, int id2) {
    if (id1 <= 0 || id2 <= 0 || id1 > enrutadores.size() || id2 > enrutadores.size()) {
        cout << "❌ IDs fuera de rango.\n";
        return;
    }

    Router* a = enrutadores[id1 - 1];
    Router* b = enrutadores[id2 - 1];

    a->eliminarVecino(b);
    b->eliminarVecino(a);

    cout << "✔ Enlace eliminado.\n";
}

void Red::dijkstra(Router* origen, Router* destino, int& costo, vector<Router*>& ruta) const {
    costo = INF;
    ruta.clear();

    map<Router*, int> dist;
    map<Router*, Router*> prev;
    for (auto r : enrutadores) dist[r] = INF;

    dist[origen] = 0;

    using P = pair<int, Router*>;
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, origen});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int d = top.first;
        Router* u = top.second;

        if (d > dist[u]) continue;
        if (u == destino) break;

        for (auto& [v, c] : u->vecinos) {
            int nd = dist[u] + c;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[destino] == INF) return;

    costo = dist[destino];

    Router* cur = destino;
    while (cur != origen) {
        ruta.push_back(cur);
        cur = prev[cur];
    }
    ruta.push_back(origen);
    reverse(ruta.begin(), ruta.end());
}

bool Red::guardarEnArchivo(const string& filename) const {
    ofstream out(filename); 
    if (!out.is_open()) return false;

    out << enrutadores.size() << "\n";

    for (auto r : enrutadores) {
        out << r->getNombre();
        for (auto& [v, c] : r->vecinos)
            out << " " << v->getNombre() << ":" << c;
        out << "\n";
    }
    return true;
}

bool Red::cargarDesdeArchivo(const string& filename) {
    ifstream in(filename); 
    if (!in.is_open()) return false;

    for (auto r : enrutadores) delete r;
    enrutadores.clear();

    int n;
    in >> n;
    if (!in) return false;

    for (int i = 1; i <= n; i++)
        enrutadores.push_back(new Router(i));

    string line;
    getline(in, line); // consumir salto de linea

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name;
        ss >> name;

        if (name.size() < 2 || name[0] != 'R') continue;
        int idx = stoi(name.substr(1));
        if (idx < 1 || idx > enrutadores.size()) continue;

        Router* r = enrutadores[idx - 1];

        string token;
        while (ss >> token) {
            size_t pos = token.find(":");
            if (pos == string::npos) continue;
            string vecName = token.substr(0, pos);
            int costo = 0;
            try {
                costo = stoi(token.substr(pos + 1));
            } catch (...) {
                continue;
            }

            if (vecName.size() < 2 || vecName[0] != 'R') continue;
            int vidx = stoi(vecName.substr(1));
            if (vidx < 1 || vidx > enrutadores.size()) continue;

            Router* vecino = enrutadores[vidx - 1];
            r->nuevoVecino(vecino, costo);
        }
    }

    return true;
}

void Red::calcularRutaMasCorta(int o, int d) {
    if (o <= 0 || d <= 0 || o > enrutadores.size() || d > enrutadores.size()) {
        cout << "❌ IDs inválidos.\n";
        return;
    }

    Router* origen = enrutadores[o - 1];
    Router* destino = enrutadores[d - 1];

    vector<Router*> ruta;
    int costo;

    dijkstra(origen, destino, costo, ruta);

    if (costo == INF) {
        cout << "❌ No hay ruta disponible.\n";
        return;
    }

    cout << "\nRuta más corta de " << origen->getNombre()
         << " a " << destino->getNombre() << ":\n";

    for (int i = 0; i < ruta.size(); i++) {
        cout << ruta[i]->getNombre();
        if (i < ruta.size() - 1) cout << " -> ";
    }
    cout << "\nCosto total: " << costo << "\n";
}

void Red::actualizarTodasLasTablas() {

    for (auto origen : enrutadores) {
        map<string, pair<int, string>> tabla;

        for (auto destino : enrutadores) {
            if (origen == destino) {
                tabla[destino->getNombre()] = {0, "-"};
                continue;
            }

            vector<Router*> ruta;
            int costo = INF;
            dijkstra(origen, destino, costo, ruta);

            if (costo == INF) {
                tabla[destino->getNombre()] = {INF, "-"};
            } else {
                string siguiente = (ruta.size() > 1) ? ruta[1]->getNombre() : destino->getNombre();
                tabla[destino->getNombre()] = {costo, siguiente};
            }
        }

        origen->actualizarTabla(tabla);
    }
}


