#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs) {
}

int JJOO::anio() const {
    return 1920;
}

vector<Atleta> JJOO::atletas() const {
    return vector<Atleta>();
}

int JJOO::cantDias() const {
    return 0;
}

int JJOO::jornadaActual() const {
    return 0;
}

vector<Competencia> JJOO::cronograma(const int &d) const {
    return vector<Competencia>();
}

vector<Competencia> JJOO::competencias() const {
    vector<Competencia> ret;
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
