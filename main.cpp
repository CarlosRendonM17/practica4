#include <iostream>
#include <fstream>
#include <string>
#include "red.h"
using namespace std;

void limpiarEntrada() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void mostrarArchivoEnConsola(const string &ruta) {
    ifstream in(ruta);
    if (!in.is_open()) {
        cout << "❌ No se pudo abrir el archivo para mostrar su contenido: " << ruta << "\n";
        return;
    }
    cout << "\n--- Contenido de " << ruta << " ---\n";
    string linea;
    int lineaNum = 1;
    while (getline(in, linea)) {
        cout << lineaNum++ << ": " << linea << "\n";
    }
    cout << "--- Fin de " << ruta << " ---\n\n";
    in.close();
}

string asegurarExtensionTxt(const string &nombre) {
    // Si ya tiene punto con extensión, la dejamos; si no, agregamos .txt
    if (nombre.find('.') == string::npos) return nombre + ".txt";
    return nombre;
}

int main() {
    Red* red = new Red();
    int opcion = -1;

    while (true) {
        cout << "\n========= MENU =========\n";
        cout << "1. Generar red aleatoria\n";
        cout << "2. Mostrar matriz de costos\n";
        cout << "3. Mostrar tablas de enrutamiento\n";
        cout << "4. Agregar enrutador\n";
        cout << "5. Eliminar enrutador\n";
        cout << "6. Agregar enlace\n";
        cout << "7. Eliminar enlace\n";
        cout << "8. Cargar red desde archivo\n";
        cout << "9. Guardar red en archivo\n";
        cout << "10. Calcular ruta mas corta\n";
        cout << "0. Salir\n";
        cout << "Elige: ";

        cin >> opcion;
        if (!cin) {
            limpiarEntrada();
            cout << "❌ Entrada inválida.\n";
            continue;
        }
        if (opcion == 0) {
            cout << "Saliendo...\n";
            break;
        }

        switch (opcion) {
        case 1: {
            int n;
            cout << "Cantidad de enrutadores: ";
            cin >> n;
            if (!cin || n <= 0) {
                limpiarEntrada();
                cout << "❌ Número inválido.\n";
                break;
            }
            delete red;
            red = new Red(n);
            red->generarRedAleatoria();
            red->actualizarTodasLasTablas();
            cout << "✔ Red aleatoria generada.\n";
            break;
        }

        case 2:
            red->mostrarRed();
            break;

        case 3:
            red->mostrarTablasDeEnrutamiento();
            break;

        case 4:
            red->agregarEnrutador();
            red->actualizarTodasLasTablas();
            break;

        case 5: {
            int id;
            cout << "ID a eliminar: ";
            cin >> id;
            if (!cin) {
                limpiarEntrada();
                cout << "❌ Entrada inválida.\n";
                break;
            }
            red->eliminarEnrutador(id);
            red->actualizarTodasLasTablas();
            break;
        }

        case 6: {
            int id1, id2, costo;
            cout << "Ingresa id1 id2 costo: ";
            if (!(cin >> id1 >> id2 >> costo)) {
                limpiarEntrada();
                cout << "❌ Entrada inválida. Se requieren 3 números.\n";
                break;
            }
            red->agregarEnlaceSeguro(id1, id2, costo);
            red->actualizarTodasLasTablas();
            break;
        }

        case 7: {
            int id1, id2;
            cout << "Ingresa id1 id2: ";
            if (!(cin >> id1 >> id2)) {
                limpiarEntrada();
                cout << "❌ Entrada inválida. Se requieren 2 números.\n";
                break;
            }
            red->eliminarEnlaceSeguro(id1, id2);
            red->actualizarTodasLasTablas();
            break;
        }

        case 8: {
            string archivo;
            cout << "Archivo: ";
            cin >> archivo;
            archivo = asegurarExtensionTxt(archivo);
            if (red->cargarDesdeArchivo(archivo)) {
                red->actualizarTodasLasTablas();
                cout << "✔ Archivo cargado correctamente.\n";
            } else {
                cout << "❌ No se pudo cargar la red.\n";
            }
            break;
        }

        case 9: {
            string archivo;
            cout << "Archivo: ";
            cin >> archivo;
            archivo = asegurarExtensionTxt(archivo);

            if (red->guardarEnArchivo(archivo)) {
                cout << "✔ Archivo guardado correctamente: " << archivo << "\n";
                mostrarArchivoEnConsola(archivo);
            } else {
                cout << "❌ No se pudo guardar.\n";
            }
            break;
        }

        case 10: {
            int o, d;
            cout << "Origen y destino: ";
            if (!(cin >> o >> d)) {
                limpiarEntrada();
                cout << "❌ Entrada inválida.\n";
                break;
            }
            red->calcularRutaMasCorta(o, d);
            break;
        }

        default:
            cout << "❌ Opción inválida.\n";
        }
    }

    delete red;
    return 0;
}
