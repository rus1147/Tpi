#include "../include/competencia.h"
#include "../tests/auxiliares_tests.h"



Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {
    vector<Atleta> atletas = as;
    int i=0;
    while(i< as.size()){
        int j= 0;
        while(j<as.size()){
            if(as[i].ciaNumber() == as[j].ciaNumber() && i != j){
                atletas = this->_atletasSinPosicion(atletas, j);
            }
            j++;
        }
        i++;
    }
    pair<Deporte,Genero> Categoria(d,g);
    this->_categoria = Categoria;
    this->_finalizada=false;
    this->_participantes=atletas;
}

Categoria Competencia::categoria() const {

    return this->_categoria;
}

vector<Atleta> Competencia::participantes() const {

    return this->_participantes;
}

bool Competencia::finalizada() const {
    return this->_finalizada;
}

vector<Atleta> Competencia::ranking() const {
    return this->_ranking;
}

vector<Atleta> Competencia::lesTocoControlAntiDoping() const {
    vector<Atleta> ret;
    int i=0;
    while(i<this->_lesTocoControlAntiDoping.size()){
        ret.push_back(this->_lesTocoControlAntiDoping[i].first);
        i++;
    }
    return ret;
}

bool Competencia::leDioPositivo(const Atleta &a) const {
    int i=0;
    while(i<this->_lesTocoControlAntiDoping.size()){
        if(a.ciaNumber()==this->_lesTocoControlAntiDoping[i].first.ciaNumber()){
            return this->_lesTocoControlAntiDoping[i].second;
        }
        i++;
    }
    return false;
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control) {
    this->_finalizada=true;
    int i=0;
    while (i<posiciones.size()){
        int j=0;
        while (j<this->_participantes.size()){
            if(this->_participantes[j].ciaNumber()==posiciones[i]){
                if(this->_ranking.size() == 0){
                    this->_ranking = vector<Atleta> (1, this->_participantes[j]);
                } else {
                    this->_ranking.push_back(this->_participantes[j]);
                }
            }
            j++;
        }
        i++;
    }
    i=0;
    while(i<this->_participantes.size()){
        int j=0;
        while(j<control.size()){
            if(this->_participantes[i].ciaNumber()==control[j].first){
                pair<Atleta,bool> antiDopingDeAtleta (this->_participantes[i],control[j].second);
                if(this->_lesTocoControlAntiDoping.size() == 0){
                    this->_lesTocoControlAntiDoping = vector<pair<Atleta,bool>>(1,antiDopingDeAtleta);
                } else {
                    this->_lesTocoControlAntiDoping.push_back(antiDopingDeAtleta);
                }
            }
            j++;
        }
        i++;
    }
    return;
}

void Competencia::linfordChristie(const int &n) {
    this->_finalizada=false;
    int i=0;
    while(i<this->_participantes.size()){
        if(this->_participantes[i].ciaNumber()==n){
            this->_participantes = this->_atletasSinPosicion(this->_participantes, i);
        }
        i++;
    }
    return;
}

bool Competencia::gananLosMasCapaces() const {
    int i=0;
    while(i<this->_ranking.size() - 1){
        if(this->_ranking[i].capacidad(this->_categoria.first) < this->_ranking[i+1].capacidad(this->_categoria.first)){
            return false;
        }
        i++;
    }
    return true;
}

void Competencia::sancionarTramposos() {
    int i=0;
    while(i<this->_lesTocoControlAntiDoping.size()){
        if(this->_lesTocoControlAntiDoping[i].second){
            int j=0;
            while(j<this->_ranking.size()){
                if(this->_ranking[j].ciaNumber() == this->_lesTocoControlAntiDoping[i].first.ciaNumber()){
                    this->_ranking = this->_atletasSinPosicion(this->_ranking, j);
                }
                j++;
            }
        }
        i++;
    }
    return;
}

void Competencia::mostrar(std::ostream &os) const {
    guardar(os);
}
/*C (|Rugby|, |Masculino|) |True|
  [(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
  (A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
  (A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
  [1, 6] [(1, |True|), (6, |True|)]
   En el caso de que la competencia no est ́e finalizada, las listas de ranking y antidoping deben ser vac ́ıas. Por ejemplo:
C (|Rugby|, |Masculino|) |False|
[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
(A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
(A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
[] []*/
void Competencia::guardar(std::ostream &os) const {
  /*  os << "{ A |" << << "|" << _genero << "|" << _anioNacimiento << "|" << _nacionalidad << "|" << _ciaNumber;

    os << "[";
    int i = 0;
    while (i < _deportes.size()) {
        os << "(" << "|" << _deportes[i].first << "|";
        i++;

        int j = 1;
        while (j < _deportes.size()) {
            os << "," << _deportes[j].second << ")";
        }
        if (i < _deportes.size() - 1) {
            os << "],";
        }
    }*/
}

void Competencia::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {
    c.mostrar(os);
    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
    c.cargar(is);
    return is;
}

bool Competencia::operator==(const Competencia &c) const {
    if(this->_participantes.size() != c.participantes().size()){
        return false;
    }
    bool hayIguales = false;
    int i=0;
    while(i<this->_participantes.size()){
        int j=0;
        while(j<c.participantes().size()){
            if(this->_participantes[i] == c.participantes()[j]){
                hayIguales = true;
            }
            j++;
        }
        if(!hayIguales){
            return false;
        } else {
            hayIguales = false;
        }
        i++;
    }
    if(this->_categoria != c.categoria() || this->_finalizada != c.finalizada()){
        return false;
    }
    if(this->_finalizada){
        if(this->_ranking != c.ranking()){
            return false;
        }
        if(this->_lesTocoControlAntiDoping.size() != c.lesTocoControlAntiDoping().size()){
            return false;
        }
        hayIguales = false;
        i = 0;
        while(i<this->_lesTocoControlAntiDoping.size()){
            int j=0;
            while(j<c.lesTocoControlAntiDoping().size()){
                if(this->_lesTocoControlAntiDoping[i].first == c.lesTocoControlAntiDoping()[j] &&
                        this->_lesTocoControlAntiDoping[i].second == c.leDioPositivo(c.lesTocoControlAntiDoping()[j])){
                    hayIguales = true;
                }
                j++;
            }
            if(!hayIguales){
                return false;
            } else {
                hayIguales = false;
            }
            i++;
        }
    }
    return true;
}

Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}


vector<Atleta> Competencia::_atletasSinPosicion(const vector<Atleta> &vec, int &i){
    Atleta atleta("Jorge",Genero::Masculino,1990,"Argentina",1);
    std::vector<Atleta> newVec (vec.size() - 1, atleta);
    int j=0;
    while (j < vec.size() - 1){
        if(j < i){
            newVec[j] = vec[j];
        } else if(j >= i) {
            newVec[j] = vec[j+1];
        }
        j++;
    }
    return newVec;
}