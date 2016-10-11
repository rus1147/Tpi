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
    int j = 0;
    int i = 0;
    while(j< this-> _cronograma.size()){
        while(i< this-> _cronograma[j].size()){
            if(_cronograma[j][i].finalizada() && _cronograma[j][i].ranking().size() >0){
                ret.push_back(this-> _cronograma[j][i]);
            }
            i++;
        }
        j++;
    }
    return ret;
}

vector<Atleta> JJOO::dePaseo() const {    vector<Atleta> ret;
    ret = _atletas;
    vector<Competencia> com;
    int j = 0;
    int i = 0;
    while(j< this-> _cronograma.size()){
        while(i< this-> _cronograma[j].size()){
            com.push_back(this-> _cronograma[j][i]);
            i++;
        }
        j++;
    }
    i = 0;
    while(i < ret.size()){
        j = 0;
        while(j < com.size()){
            int k = 0;
            while(k < com[j].participantes().size()){
                if(ret[i].ciaNumber() == com[j].participantes()[k].ciaNumber()){
                    ret.erase(ret.begin()+i);
                }
                else{
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    return ret;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    int j = 0;
    int i = 0;
    //FILTO COMPETENCIAS FINALIZADAS
    vector<Competencia> comFinalizadas;
    while(j< this-> _cronograma.size()){
        while(i< this-> _cronograma[j].size()){
            if(_cronograma[j][i].finalizada()){
                comFinalizadas.push_back(this-> _cronograma[j][i]);
            }
            i++;
        }
        j++;
    }
    //FILTRO ATLETAS QUE GANARON ALGUNA MEDALLA
    vector<pair<Pais, vector<int> > > ret;
    vector<Atleta> atletasGanadores;
    while (i < _atletas.size()){
        while(j < comFinalizadas.size()){
            if(comFinalizadas[j].ranking().size() > 0 && comFinalizadas[j].ranking()[0].ciaNumber() == _atletas[i].ciaNumber()
               || comFinalizadas[j].ranking().size() > 1 && comFinalizadas[j].ranking()[1].ciaNumber() == _atletas[i].ciaNumber()
               || comFinalizadas[j].ranking().size() > 2 && comFinalizadas[j].ranking()[2].ciaNumber() == _atletas[i].ciaNumber()  ) {
                atletasGanadores.push_back(this->_atletas[i]);
            }
            j++;
        }
        i++;
    }
    //ATLETASDEORO ATLETASDEPLATA & ATLETASDEBRONCE NO TIENEN REPETIDOS POR COMO ESTAN FILTRADOS
    //Y CONTEMPLAN EL CASO EN EL QUE UN JUGADOR GANA UNA SOLA MEDALLA Y "0" EN LAS OTRAS LISTAS
    //Variable de soporte
    pair<Atleta,int > AtletaYMedalla;
    //Vector de cantidad Oro
    vector<pair<Atleta, int >> atletasDeOro;
    while(i < _atletas.size()){
        int k = 0;
        while(j < comFinalizadas.size()){
            if(comFinalizadas[j].ranking().size() > 0 && comFinalizadas[j].ranking()[0].ciaNumber() == _atletas[i].ciaNumber() ){
                k++;
            }
            j++;
        }
        AtletaYMedalla.first = this ->_atletas[i];
        AtletaYMedalla.second = k;
        atletasDeOro.push_back(AtletaYMedalla);
    }
    //Vector de cantidad Plata
    vector<pair<Atleta, int >> atletasDePlata;
    while(i < _atletas.size()){
        int k = 0;
        while(j < comFinalizadas.size()){
            if(comFinalizadas[j].ranking().size() > 1 && comFinalizadas[j].ranking()[1].ciaNumber() == _atletas[i].ciaNumber() ){
                k++;
            }
            j++;
        }
        AtletaYMedalla.first = this ->_atletas[i];
        AtletaYMedalla.second = k;
        atletasDePlata.push_back (AtletaYMedalla);
    }
    //Vector de cantidad Bronce
    vector<pair<Atleta,int >> atletasDeBronce;
    while(i < _atletas.size()){
        int k = 0;
        while(j < comFinalizadas.size()){
            if(comFinalizadas[j].ranking().size() > 2 && comFinalizadas[j].ranking()[2].ciaNumber() == _atletas[i].ciaNumber() ){
                k++;
            }
            j++;
        }
        AtletaYMedalla.first = this ->_atletas[i];
        AtletaYMedalla.second = k;
        atletasDeBronce.push_back (AtletaYMedalla);
    }
    //TOMO LOS ATLETAS QUE GANARON ALGUNA MEDALLA Y LES AGREGO LAS MEDALLAS QUE OBTUVIERON 
    //Variable de soporte
    pair<Pais, vector <int>> PaisYMedallas;
    vector<pair<Pais, vector <int>>> atletasConSusMedallas ;
    i = 0;
    vector <int> medals;
    while(i < atletasGanadores.size()){
        int k = 0;
        while(k < atletasDeOro.size()){
            if(atletasGanadores[i].ciaNumber()== atletasDeOro[k].first.ciaNumber()){
                medals.push_back(atletasDeOro[k].second);
                atletasConSusMedallas.push_back(PaisYMedallas);
            }
            k++;
        }
        while(k < atletasDePlata.size()){
            if(atletasGanadores[i].ciaNumber()== atletasDePlata[k].first.ciaNumber()){
                medals.push_back(atletasDePlata[k].second);
            }
            k++;
        }
        while(k < atletasDeBronce.size()){
            if(atletasGanadores[i].ciaNumber()== atletasDeBronce[k].first.ciaNumber()){
                medals.push_back(atletasDeBronce[k].second);
            }
            k++;
        }
        PaisYMedallas.first = atletasGanadores[i].nacionalidad();
        PaisYMedallas.second = medals;
        atletasConSusMedallas.push_back(PaisYMedallas);
        medals.clear();
        i++;
    }
    //Falta terminar el ordenamiento segun la especificacion de medalleros

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