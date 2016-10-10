#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs) {
    this->_anio = a;
    this->_atletas = as;
    this->_jornadaActual = 1;
    this->_cronograma = cs;
}

int JJOO::anio() const {
    return this->_anio;
}

vector<Atleta> JJOO::atletas() const {
    return this->_atletas;
}

int JJOO::cantDias() const {
    return this->_cronograma.size();
}

int JJOO::jornadaActual() const {
    return this->_jornadaActual;
}

vector<Competencia> JJOO::cronograma(const int &d) const {
    return this->_cronograma[d-1];
}

vector<Competencia> JJOO::competencias() const {
    vector<Competencia> ret;
    int i = 0;
    while(i < this->_cronograma.size()){
        int j = 0;
        while(j < this->_cronograma[i].size()){
            ret.push_back(this->_cronograma[i][j]);
            j++;
        }
        i++;
    }
    return ret;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {
    vector<Competencia> ret;
    return ret;
}

vector<Atleta> JJOO::dePaseo() const {
    vector<Atleta> ret;
    return ret;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Pais, vector<int> > > ret;
    return ret;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    return 0;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> ret;
    return ret;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    return;
}

Atleta JJOO::stevenBradbury() const {
    Atleta ret("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    return ret;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {
    return true;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    return ret;
}

void JJOO::transcurrirDia() {
    return;
}

void JJOO::mostrar(std::ostream &os) const {
}

void JJOO::guardar(std::ostream &os) const {
}

void JJOO::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    return os;
}

std::ostream &operator>>(std::ostream &os, const JJOO &j) {
    return os;
}

bool JJOO::operator==(const JJOO &j) const {
    return true;
}

JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}