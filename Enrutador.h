#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

static const int INF = numeric_limits<int>::max();

class Enrutador {
private:
    string nombre;
    unordered_map<string, int> vecinos;

public:
    Enrutador() = default;
    explicit Enrutador(const string& n);


    string getNombre() const;
    void setNombre(const string& n);


    void actualizarVecino(const string& destino, int costo);


    void eliminarVecino(const string& destino);


    const unordered_map<string, int>& obtenerVecinos() const;


    bool tieneVecino(const string& destino) const;


    int costoA(const string& destino) const;
};

#endif
