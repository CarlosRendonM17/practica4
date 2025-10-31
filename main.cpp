#include "Red.h"
#include <iostream>
using namespace std;

void menu() {
    cout << "\n=== Práctica 4: Simulación de Red ===\n";
    cout << "1. Cargar desde archivo\n";
    cout << "2. Generar red aleatoria\n";
    cout << "3. Agregar enrutador\n";
    cout << "4. Eliminar enrutador\n";
    cout << "5. Actualizar o crear enlace\n";
    cout << "6. Eliminar enlace\n";
    cout << "7. Mostrar red\n";
    cout << "8. Consultar ruta más corta\n";
    cout << "9. Guardar red\n";
    cout << "0. Salir\n";
    cout << "Opción: ";
}

int main() {
    srand(time(nullptr));
    Red red;
    int opcion;

    do {
        menu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            cout << "Nombre del archivo: ";
            string nombre;
            cin >> nombre;
            red.cargarDesdeArchivo(nombre);
            break;
        }
        case 2: {
            int n, c;
            double d;
            cout << "Cantidad de enrutadores: "; cin >> n;
            cout << "Costo máximo: "; cin >> c;
            cout << "Densidad (0-1): "; cin >> d;
            red.generarAleatoria(n, c, d);
            break;
        }
        case 3: {
            cout << "Nombre: ";
            string n;
            cin >> n;
            red.agregarEnrutador(n);
            break;
        }
        case 4: {
            cout << "Nombre: ";
            string n;
            cin >> n;
            red.eliminarEnrutador(n);
            break;
        }
        case 5: {
            string a, b; int c;
            cout << "Origen: "; cin >> a;
            cout << "Destino: "; cin >> b;
            cout << "Costo: "; cin >> c;
            red.actualizarEnlace(a, b, c);
            break;
        }
        case 6: {
            string a, b;
            cout << "Origen: "; cin >> a;
            cout << "Destino: "; cin >> b;
            red.borrarEnlace(a, b);
            break;
        }
        case 7:
            red.imprimirRed();
            break;
        case 8:
            red.preguntarRuta();
            break;
        case 9: {
            cout << "Archivo destino: ";
            string n;
            cin >> n;
            red.guardarEnArchivo(n);
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}
