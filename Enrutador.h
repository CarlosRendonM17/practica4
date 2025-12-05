#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <string>
using namespace std;

class Router {
public:
    int id;
    map<Router*, int> vecinos;

    
    map<string, pair<int, string>> tablaEnrutamiento;

    Router(int id);
    void nuevoVecino(Router* vecino, int costo);
    void eliminarVecino(Router* vecino);

    string getNombre() const;
    map<string, int> getTabla() const;
    void mostrarConexiones() const;


    void actualizarTabla(const map<string, pair<int, string>>& nueva);

   
    void agregarConexion(const string& nombreVecino, int costo);
    void eliminarConexion(const string& nombreVecino);

    
    void mostrarTablaEnrutamiento(const map<string, pair<int, string>>& tabla) const;
    void mostrarTablaEnrutamiento() const;
};

#endif