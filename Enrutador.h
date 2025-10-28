#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
using namespace std;

class Enrutador {
private:
    string nombre;

public:
    Enrutador() = default;
    explicit Enrutador(const string& n);
};

#endif
