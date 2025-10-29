#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

using namespace std;


class Red {
private:
    unordered_map<string, Enrutador> enrutadores;  // Mapa nombre -> enrutador

public:
    Red() = default;

    // --- Gestión de enrutadores ---
    bool existe(const string& nombre) const;
    void agregarEnrutador(const string& nombre);
    void eliminarEnrutador(const string& nombre);

    // --- Gestión de enlaces ---
    void actualizarEnlace(const string& a, const string& b, int costo);
    void borrarEnlace(const string& a, const string& b);

    // --- Archivos y topología ---
    void cargarDesdeArchivo(const string& nombreArchivo);
    void guardarEnArchivo(const string& nombreArchivo) const;
    void generarAleatoria(int n, int costoMax, double probEnlace = 0.5);

    // --- Consultas ---
    void imprimirRed() const;
    pair<int, vector<string>> rutaMasCorta(const string& origen, const string& destino) const;
    void preguntarRuta() const;

    vector<string> listaEnrutadores() const;
};

#endif
