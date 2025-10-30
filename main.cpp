#include <iostream>
#include "Red.h"
using namespace std;

int main() {
    Red red;

    cout << "Probando creación de red...\n";
    red.agregarEnrutador("A");
    red.agregarEnrutador("B");
    red.actualizarEnlace("A", "B", 5);
    red.imprimirRed();

    return 0;
}
