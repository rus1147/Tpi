#include "../include/tipos.h"

ostream &operator<<(ostream &os, const Genero &g) {
    if (g == Femenino) {
        os << "Femenino";
    } else {
        os << "Masculino";
    }
    return os;
}

istream &operator>>(istream &is, Genero &g) {
    string s;
    is >> s;
    if (s == "Femenino") {
        g = Femenino;
    } else if (s == "Masculino") {
        g = Masculino;
    } else {
        assert(false);
    }
    return is;
}
