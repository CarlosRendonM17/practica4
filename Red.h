#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <unordered_map>
using namespace std;

class Red {
private:
    unordered_map<string, Enrutador> enrutadores;

public:
    Red() = default;
};

#endif
