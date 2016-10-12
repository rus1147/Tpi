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
    //vector con los paises de los atletas ganadores
    vector <Pais> paisesDeGanadores;
    paisesDeGanadores.push_back(atletasGanadores[0].nacionalidad());
    //le estoy agregando el primer elemento y despues me fijo que los que voy a agregar no esten
    i = 0;
    while(i+1 < atletasGanadores.size()){
        int k = 0;
        int l = 0;
        while(k < paisesDeGanadores.size()){
            if(paisesDeGanadores[k] == atletasGanadores[i+1].nacionalidad()){
                l++;
                }
            k++;
        }
        if(l == 0){
            paisesDeGanadores.push_back(atletasGanadores[i+1].nacionalidad());
        }
        i++;
    }

    //ATLETASDEORO ATLETASDEPLATA & ATLETASDEBRONCE NO TIENEN REPETIDOS POR COMO ESTAN FILTRADOS
    //Y CONTEMPLAN EL CASO EN EL QUE UN JUGADOR GANA UNA SOLA MEDALLA Y "0" EN LAS OTRAS LISTAS
    //Variable de soporte
    pair<Atleta,int > AtletaYMedalla;
    //Vector de cantidad Oro
    vector<pair<Atleta, int >> atletasDeOro;
    i = 0;
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
        i++;
    }
    //Vector de cantidad Plata
    vector<pair<Atleta, int >> atletasDePlata;
    i = 0;
    j = 0;
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
        i++;
    }
    //Vector de cantidad Bronce
    vector<pair<Atleta,int >> atletasDeBronce;
    i = 0;
    j = 0;
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
        i++;
    }
    //TOMO LOS ATLETAS QUE GANARON ALGUNA MEDALLA Y LES AGREGO LAS MEDALLAS QUE OBTUVIERON 
    //Variable de soporte
    pair<Pais, vector <int>> PaisYMedallas;
    vector<pair<Pais, vector <int>>> atletasConSusMedallas ;
    vector <int> medals;
    i = 0;
    while(i < paisesDeGanadores.size()) {
        int k = 0;
        int cant = 0;
        while (k < atletasDeOro.size()) {
            if (paisesDeGanadores[i] == atletasDeOro[k].first.nacionalidad()) {
                cant = cant + atletasDeOro[k].second;
            }
            k++;
        }
        //UNA VEZ TERMINADO EL CICLO, MEDALS RECIVE SU PRIMER ELEMENTO PARA EL PAIS "I-ESIMO"
        //Y LAS VARIABLES SE REESTABLECEN, MENOS I PORQUE RECORRE LOS PASISES
        medals.push_back(cant);
        k = 0;
        cant = 0;
        while(k < atletasDePlata.size()){
            if(paisesDeGanadores[i] == atletasDePlata[k].first.nacionalidad()){
                cant = cant + atletasDePlata[k].second;
            }
            k++;
        }
        //UNA VEZ TERMINADO EL CICLO, MEDALS RECIVE SU SEGUNDO ELEMENTO PARA EL PAIS "I-ESIMO"
        medals.push_back(cant);
        k = 0;
        cant = 0;
        while(k < atletasDeBronce.size()){
            if(paisesDeGanadores[i] == atletasDeBronce[k].first.nacionalidad()){
                cant = cant + atletasDeBronce[k].second);
            }
            k++;
        }
        //UNA VEZ TERMINADO EL CICLO, MEDALS RECIVE SU TERCER ELEMENTO PARA EL PAIS "I-ESIMO"
        medals.push_back(cant);
        //EN LA VARIABLE AUXILIAR (PaisYMedallas)DEFINO LOS ELEMENTOS QUE VOY A METER EN "atletasConSusMedallas"
        //PasisYMedallas por ser "Pair", en cada vuelta se pisan los valores (no hace falta limpiarlo para que entre al ciclo)
        PaisYMedallas.first = paisesDeGanadores[i];
        PaisYMedallas.second = medals;
        atletasConSusMedallas.push_back(PaisYMedallas);
        //LIMPIO AUXILIAR(medals), PARA PODER USARLO CUANDO ENTRE AL CICLIO CON EL PAIS "(i+1)-IESIMO"
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