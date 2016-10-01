#ifndef __ATLETA__
#define __ATLETA__

#include "tipos.h"


class Atleta {

private:

    int _anioNacimiento;
    int _ciaNumber;
    Pais _nacionalidad;
    string _nombre;
    Genero _genero;
    vector<pair<Deporte, int> > _deportes;

public:
    Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c);

    string nombre() const;

    Genero genero() const;

    int anioNacimiento() const;

    Pais nacionalidad() const;

    int ciaNumber() const;

    vector<Deporte> deportes() const;

    int capacidad(const Deporte &d) const;

    Deporte especialidad() const;

    void entrenarNuevoDeporte(const Deporte &d, const int &c);

    bool operator==(const Atleta &a) const;

    Atleta operator=(const Atleta &a);

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const Atleta &a);

std::ostream &operator>>(std::ostream &os, const Atleta &a);

#endif /*__ATLETA__*/