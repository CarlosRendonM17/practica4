#ifndef RED_H
#define RED_H

#include <vector>
#include <string>
#include "enrutador.h"
using namespace std;

class Red {
public:
    vector<Router*> enrutadores;

    Red();
    Red(int n);
    ~Red();

    int cantidadEnrutadores() const;

    void generarRedAleatoria();
    void mostrarRed() const;
    void mostrarTablasDeEnrutamiento() const;

    void agregarEnrutador();
    void eliminarEnrutador(int id);

    void agregarEnlaceSeguro(int id1, int id2, int costo);
    void eliminarEnlaceSeguro(int id1, int id2);

    bool guardarEnArchivo(const string& filename) const;
    bool cargarDesdeArchivo(const string& filename);

    void calcularRutaMasCorta(int o, int d);

   
    void actualizarTodasLasTablas();

private:
    void dijkstra(Router* origen, Router* destino, int& costo, vector<Router*>& ruta) const;
};

#endif
