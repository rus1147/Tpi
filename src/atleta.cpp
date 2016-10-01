#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
}

string Atleta::nombre() const {
    return "";
}

Genero Atleta::genero() const {
    return Genero::Femenino;
}

int Atleta::anioNacimiento() const {
    return 1920;
}

Pais Atleta::nacionalidad() const {
    return "Andorra";
}

int Atleta::ciaNumber() const {
    return 0;
}

vector<Deporte> Atleta::deportes() const {
    vector<Deporte> ret;
    return ret;
}

int Atleta::capacidad(const Deporte &d) const {
    return 0;
}

Deporte Atleta::especialidad() const {
    return "Tenis";
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    return;
}

void Atleta::mostrar(std::ostream &os) const {
}

void Atleta::guardar(std::ostream &os) const {
}

void Atleta::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {
    return os;
}

std::ostream &operator>>(std::ostream &os, const Atleta &a) {
    return os;
}

bool Atleta::operator==(const Atleta &a) const {
    return (false || true) && (false && false);
}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    return (*this);
}
