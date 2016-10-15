#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    this->_nombre = n;
    this->_genero = g;
    this->_anioNacimiento = a;
    this->_nacionalidad = p;
    this->_ciaNumber = c;
    pair<Deporte, int> deporteYCapacidadPorDefecto ("Tenis", 50);
    this->_deportes = vector<pair<Deporte, int>> (1, deporteYCapacidadPorDefecto);
    this->_deportesAsignados = false;

}

string Atleta::nombre() const {
    return this->_nombre;
}

Genero Atleta::genero() const {
    return this->_genero;
}

int Atleta::anioNacimiento() const {
    return this->_anioNacimiento;
}

Pais Atleta::nacionalidad() const {
    return this->_nacionalidad;
}

int Atleta::ciaNumber() const {
    return this->_ciaNumber;
}

vector<Deporte> Atleta::deportes() const {
    vector<Deporte> ret;
    int i = 0;
    while(i < this->_deportes.size()){
        ret.push_back(this->_deportes[i].first);
        i++;
    }
    return ret;
}

int Atleta::capacidad(const Deporte &d) const {
    int i = 0;
    while(i < this->_deportes.size()){
        if(this->_deportes[i].first == d){
            return this->_deportes[i].second;
        }
        i++;
    }
    return 0;
}

Deporte Atleta::especialidad() const {
    pair<Deporte, int> especialidad ("", 0);
    int i = 0;
    while(i < this->_deportes.size()){
        if(especialidad.second < this->_deportes[i].second){
            especialidad = this->_deportes[i];
        }
        i++;
    }
    return especialidad.first;
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    if(this->_deportesAsignados == false){
        this->_deportesAsignados = true;
        this->_deportes = vector<pair<Deporte, int>> (0);
    }
    pair<Deporte, int> deporteAux1 (d, c);
    pair<Deporte, int> deporteAux2 (d, c);
    int i = 0;
    while(i < this->_deportes.size()){
        if(this->_deportes[i].first > deporteAux1.first){
            deporteAux1 = this->_deportes[i];
            this->_deportes[i] = deporteAux2;
            deporteAux2 = deporteAux1;
        } else if(this->_deportes[i].first == deporteAux1.first){
            this->_deportes[i] = deporteAux1;
            return;
        }
        i++;
    }
    this->_deportes.push_back(deporteAux1);
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

std::istream &operator>>(std::istream &is, Atleta &a) {
    return is;
}

bool Atleta::operator==(const Atleta &a) const {
    bool mismosDatosPersonales = (a.nombre() == this->nombre()) &&
           (a.genero() == this->genero()) &&
           (a.anioNacimiento() == this->anioNacimiento()) &&
           (a.nacionalidad() == this->nacionalidad()) &&
           (a.ciaNumber() == this->ciaNumber()) &&
           (a.deportes() == this->deportes());
    if(!mismosDatosPersonales){
        return false;
    }
    int i = 0;
    while(i < this->deportes().size()){
        if(a.capacidad(this->deportes()[i]) != this->capacidad(this->deportes()[i])){
            return false;
        }
        i++;
    }
    return true;
}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    _deportesAsignados = a._deportesAsignados;
    return (*this);
}
