#include "../include/atleta.h"

Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    this->_nombre = n;
    this->_genero = g;
    this->_anioNacimiento = a;
    this->_nacionalidad = p;
    this->_ciaNumber = c;
    pair<Deporte, int> deporteYCapacidadPorDefecto ("Tenis", 50);
    this->_deportes = vector<pair<Deporte, int>> (1, deporteYCapacidadPorDefecto);

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
    guardar(os);
}
// A |Liu Song| |Masculino| 1972 |China| 123 [(|Tenis de Mesa|, 90)]
void Atleta::guardar(std::ostream &os) const {
    os << "A |" << _nombre << "|" << _genero << "|"
       << _anioNacimiento << "|" << _nacionalidad << "|" << _ciaNumber;
    os << "[";
    unsigned int i = 0;
    while (i < _deportes.size()) {
        os << "(" << "|" << _deportes[i].first << "|"
        << "," << _deportes[i].second << ")";
        i++;
        }
        if (i < _deportes.size()) {
            os << ",";
        }
    os<<"]";
    }
// A |Liu Song| |Masculino| 1972 |China| 123 [(|Tenis de Mesa|, 90)]
void Atleta::cargar(std::istream &is) {
    string at;
    getline(is,at,'|'); //Lee la A
    getline(is,_nombre,'|'); //Lee el nombre
    getline(is,at,'|'); //Lee el |
    getline(is,at,'|'); //Lee el genero
    _genero = generostring(at); //Convertir los tipos
    is>>_anioNacimiento;
    getline(is,at,'|'); //Lee el |
    getline(is,_nacionalidad,'|'); // Lee nacionalidad
    is>>_ciaNumber;
    getline(is,at,'[');
    _deportes.clear();
    while(is.peek() != ']'){
        pair<Deporte,int> d;
        getline(is,at,'('); //Lee el parentesis
        getline(is,at,'|'); //Lee el pipe
        getline(is,d.first,'|'); //Lee  deporte
        getline(is,at,','); //Lee coma
        getline(is,at,')'); //Lee  habilidad
        d.second = atoi(at.c_str());
        _deportes.push_back(d);
    }
}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {
    a.guardar(os);
    return os;
}

std::istream &operator>>(std::istream &is, Atleta &a) {
    a.cargar(is);
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
    return (*this);
}
