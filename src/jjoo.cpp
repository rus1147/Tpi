#include "../include/jjoo.h"
#include "../tests/auxiliares_tests.h"

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
    return int(this->_cronograma.size());
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
    while(j< this-> _cronograma.size()){
        int i = 0;
        while(i< this-> _cronograma[j].size()){
            if(_cronograma[j][i].finalizada() && _cronograma[j][i].ranking().size() >0){
                ret.push_back(this->_cronograma[j][i]);
            }
            i++;
        }
        j++;
    }
    return ret;
}

vector<Atleta> JJOO::dePaseo() const {
    vector<Atleta> atletasDePaseo = this->atletas();
    vector<Competencia> competencias = this->competencias();
    int i = 0;
    while(i < atletasDePaseo.size()){
        int j = 0;
        while(j < competencias.size()){
            int k = 0;
            while(k < competencias[j].participantes().size()){
                if(atletasDePaseo[i].ciaNumber() == competencias[j].participantes()[k].ciaNumber()){
                    atletasDePaseo = this->_atletasSinPosicion(atletasDePaseo, i);
                }
                k++;
            }
            j++;
        }
        i++;
    }
    return atletasDePaseo;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Atleta, int>> atletasConMedallas = this->_atletasQueGanaronAlgo();
    vector<pair<Pais, vector<int>>> medallero;
    int i = 0;
    while(i < atletasConMedallas.size()){
        int j = 0;
        bool paisRepetido = false;
        while(j < medallero.size()){
            if(atletasConMedallas[i].first.nacionalidad() == medallero[j].first){
                paisRepetido = true;
                break;
            }
            j++;
        }
        if(!paisRepetido){
            medallero.push_back(pair<Pais, vector<int>> (atletasConMedallas[i].first.nacionalidad(), vector<int> (3, 0)));
        }
        i++;
    }
    //medallero = vector<pair<paisesNoRepetidosQueGanaronMedallas, vector<0,0,0>>>
    i = 0;
    while(i < medallero.size()){
        int j = 0;
        while(j < atletasConMedallas.size()){
            if(atletasConMedallas[j].first.nacionalidad() == medallero[i].first){
                medallero[i].second[atletasConMedallas[j].second]++;
            }
            j++;
        }
        i++;
    }
    //medallero = vector<pair<paisesNoRepetidosQueGanaronMedallas, vector<Oro,Plata,Bronce>>>
    bool ordenada = false;
    while(!ordenada){
        ordenada = true;
        i = 0;
        while(i < medallero.size() - 1){
            bool hayQueSwappear = (medallero[i].second[0] < medallero[i+1].second[0]) ||
                    (medallero[i].second[0] == medallero[i+1].second[0] && medallero[i].second[1] < medallero[i+1].second[1]) ||
                    (medallero[i].second[0] == medallero[i+1].second[0] && medallero[i].second[1] == medallero[i+1].second[1] &&
                            medallero[i].second[2] < medallero[i+1].second[2]);
            if(hayQueSwappear){
                swap(medallero[i], medallero[i+1]);
                ordenada = false;
            }
            i++;
        }
    }
    //medallero = vector<pairOrdenadoSegunEspecificacion<paisesNoRepetidosQueGanaronMedallas, vector<Oro,Plata,Bronce>>>

    return medallero;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    int cantidadDeAtletasEliminados = 0;
    int i = 0;
    while(i < _cronograma.size()){
        int j = 0;
        while(j < _cronograma[i].size()){
            if(_cronograma[i][j].categoria() == c){
                Competencia comp = _cronograma[i][j];
                vector<Atleta> participantes = comp.participantes();
                int k = 0;
                while(k < comp.participantes().size()){
                    if(comp.participantes()[k].nacionalidad() == p){
                        participantes = this->_atletasSinPosicion(participantes, k);
                        cantidadDeAtletasEliminados++;
                    }
                    k++;
                }
                Competencia nuevaCompetencia(comp.categoria().first, comp.categoria().second, participantes);
                if(comp.finalizada()){
                    vector<int> ranking;
                    k = 0;
                    while(k < comp.ranking().size()){
                        if(comp.ranking()[k].nacionalidad() != p){
                            ranking.push_back(comp.ranking()[k].ciaNumber());
                        }
                        k++;
                    }
                    vector<pair<int, bool>> control;
                    k = 0;
                    while(k < comp.lesTocoControlAntiDoping().size()){
                        if(comp.lesTocoControlAntiDoping()[k].nacionalidad() != p){
                            Atleta a = comp.lesTocoControlAntiDoping()[k];
                            control.push_back(pair<int, bool> (a.ciaNumber(), comp.leDioPositivo(a)));
                        }
                        k++;
                    }
                    nuevaCompetencia.finalizar(ranking, control);
                }
                _cronograma[i][j] = nuevaCompetencia;
                return cantidadDeAtletasEliminados;
            }
            j++;
        }
        i++;
    }
    return 0;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> atletas = this->atletas();
    vector<pair<Atleta, int>> fracasados;
    int i = 0;
    while(i < atletas.size()){
        fracasados[i] = pair<Atleta, int> (atletas[i], 0);
    }
    i = 0;
    while(i < fracasados.size()){
        if(fracasados[i].first.nacionalidad() != p){
            fracasados = this->_paresSinPosicion(fracasados, i);
        } else {
            int j = 0;
            while(j < this->competencias().size()){
                if(this->competencias()[j].finalizada()){
                    int r = 0;
                    while(r < this->competencias()[j].ranking().size()){
                        if(fracasados[i].first.ciaNumber() == this->competencias()[j].ranking()[r].ciaNumber() && r < 3){
                            fracasados = this->_paresSinPosicion(fracasados, i);
                        } else if (fracasados[i].first.ciaNumber() == this->competencias()[j].ranking()[r].ciaNumber() && r >= 3){
                            fracasados[i].second++;
                        }
                        r++;
                    }
                }
                j++;
            }
        }
        i++;
    }

    bool ordenado = false;
    while(!ordenado){
        ordenado = true;
        i = 0;
        while(i < fracasados.size() - 1){
            if(fracasados[i].second < fracasados[i+1].second){
                swap(fracasados[i], fracasados[i+1]);
                ordenado = false;
            }
        }
    }

    vector<Atleta> losMasFracasados;
    int scoreDeFracaso = fracasados[0].second;
    i = 0;
    while(i < fracasados.size()){
        if(fracasados[i].second == scoreDeFracaso){
            losMasFracasados.push_back(fracasados[i].first);
        } else if (fracasados[i].second < scoreDeFracaso){
            return losMasFracasados;
        }
        i++;
    }
    return losMasFracasados;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    Atleta atletaNacionalizado(a.nombre(), a.genero(), a.anioNacimiento(), p, a.ciaNumber());
    int i = 0;
    while(i < a.deportes().size()){
        atletaNacionalizado.entrenarNuevoDeporte(a.deportes()[i], a.capacidad(a.deportes()[i]));
        i++;
    }

    i = 0;
    while(i < this->_atletas.size()){
        if(this->_atletas[i].ciaNumber() == a.ciaNumber()){
            this->_atletas = this->_atletasSinPosicion(this->_atletas, i);
            this->_atletas.push_back(atletaNacionalizado);
        }
        i++;
    }

    vector<vector<Competencia>> nuevoCronograma;
    i = 0;
    while (i < this->_cronograma.size()){
        vector<Competencia> nuevasCompetencias;
        int j = 0;
        while(j < this->_cronograma[i].size()){
            Competencia comp = this->_cronograma[i][j];
            vector<Atleta> participantes = comp.participantes();
            int k = 0;
            bool hayQueModificar = false;
            while(k < participantes.size()){
                if(participantes[k].ciaNumber() == a.ciaNumber()){
                    participantes = _atletasSinPosicion(participantes, k);
                    hayQueModificar = true;
                }
                k++;
            }
            if(hayQueModificar){
                participantes.push_back(atletaNacionalizado);
                Categoria categoria = comp.categoria();
                Competencia nuevaComp(categoria.first, categoria.second, participantes);
                if(comp.finalizada()){
                    k = 0;
                    vector<int> ranking;
                    vector<pair<int,bool>> control;
                    while(k < comp.ranking().size()){
                        ranking.push_back(comp.ranking()[k].ciaNumber());
                        k++;
                    }
                    k = 0;
                    while(k < comp.lesTocoControlAntiDoping().size()){
                        bool leToco = comp.leDioPositivo(comp.lesTocoControlAntiDoping()[k]);
                        int ciaNumber = comp.lesTocoControlAntiDoping()[k].ciaNumber();
                        pair<int,bool> entry (ciaNumber, leToco);
                        control.push_back(entry);
                        k++;
                    }
                    nuevaComp.finalizar(ranking, control);
                }
                nuevasCompetencias.push_back(nuevaComp);
            } else {
                nuevasCompetencias.push_back(comp);
            }
            j++;
        }
        i++;
        nuevoCronograma.push_back(nuevasCompetencias);
    }
    this->_cronograma = nuevoCronograma;
    return;
}

Atleta JJOO::stevenBradbury() const {
// BUSCO LAS COMPETENCIAS FINALIZADAS
    int j = 0;
    int i = 0;
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
//ARMO UNA LISTA DE PARES DE ATLETAS GANADORES Y CAPACIDAD QUE TIENEN EN LA COMPETENCIA QUE GANARON
    i = 0;
    pair<Atleta,int> ganadorYCapacidad (this->_atletas[0], 0);
    vector<pair<Atleta,int>> ganadoresYCapacidad;
    while(i < comFinalizadas.size()){
        if(comFinalizadas[i].ranking().size() > 0){
            ganadorYCapacidad.first = comFinalizadas[i].ranking()[0];
            ganadorYCapacidad.second = comFinalizadas[i].ranking()[0].capacidad(comFinalizadas[i].categoria().first);
        }
        ganadoresYCapacidad.push_back(ganadorYCapacidad);
        i++;
    }
//BUSCO LA CAPACIDAD MINIMA DE LOS ATLETAS (EN LAS COMPETENCIAS QUE GANARON)
    i =0;
    int minCap = ganadoresYCapacidad[0].second;
    while(i < ganadoresYCapacidad.size()){
        if(minCap > ganadoresYCapacidad[i].second){
            minCap = ganadoresYCapacidad[i].second;
        }
        i++;
    }
//DEVUELVO AL PRIMERO QUE ENCUENTRE CON LA MINIMA CAPACIDAD (CASO CONTRARIO DEVUELVE AL PRIMERO)
    i = 0;
    while(i < ganadoresYCapacidad.size()){
        if(ganadoresYCapacidad[i].second == minCap){
            return ganadoresYCapacidad[i].first;
        }
    }
    return ganadoresYCapacidad[0].first;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {

    vector<Pais> mejoresPaises;
    int dia = 1;
    while(dia <= cantDias()) {
        vector<pair<Pais, int> > oros;
        int i = 0;
        while(i < cronograma(dia).size()) {
            Competencia actual = cronograma(dia)[i];
            if(actual.finalizada() && actual.ranking().size() > 0) {
                Pais pais = actual.ranking()[0].nacionalidad();
                bool encontrado = false;
                int j = 0;
                while(j < oros.size() && !encontrado) {
                    if(oros[j].first == pais) {
                        pair<Pais, int> nuevaTupla = make_pair(oros[j].first, oros[j].second + 1);
                        oros = this->_paresPaisesSinPosicion(oros, j);
                        oros.push_back(nuevaTupla);
                        encontrado = true;
                    }
                    j++;
                }
                if(!encontrado) {
                    oros.push_back(make_pair(pais, 1));
                }
            }
            i++;
        }

        if(oros.size() > 0) {
            pair<Pais, int> mejorPais;
            i = 0;
            while(i < oros.size()) {
                if( i == 0 ||
                    oros[i].second > mejorPais.second ||
                    (oros[i].second == mejorPais.second && oros[i].first < mejorPais.first)) {
                    mejorPais = oros[i];
                }
                i++;
            }
            mejoresPaises.push_back(mejorPais.first);
        }
        dia++;
    }

    bool hayPatron = true;
    if(mejoresPaises.size() >= 3) {
        int i = 0;
        while(i < mejoresPaises.size() - 1) {
            int j = i + 1;
            while(j < mejoresPaises.size() - 1) {
                if(mejoresPaises[j] == mejoresPaises[i]) {
                    hayPatron = hayPatron && (mejoresPaises[j + 1] == mejoresPaises[i + 1]);
                }
                j++;
            }
            i++;
        }
    }

    return hayPatron;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> paises = this->_paises();
    vector<pair<Pais, int>> diasSinGanarPorPais;

    int i = 0;
    while(i < paises.size()){
        vector<int> jornadasGanadoras;
        jornadasGanadoras.push_back(0);
        int j = 0;
        while(j < this->_jornadaActual){
            if(this->_ganoMedallasEseDia(paises[i], j)){
                jornadasGanadoras.push_back(j);
            }
            j++;
        }
        jornadasGanadoras.push_back(_jornadaActual);
        diasSinGanarPorPais.push_back(pair<Pais, int> (paises[i], this->_maximaDistanciaEntreJornadas(jornadasGanadoras)));
        i++;
    }

    int maximosDiasSinGanar = 0;
    i = 0;
    while(i < diasSinGanarPorPais.size()) {
        if(i == 0 || diasSinGanarPorPais[i].second > maximosDiasSinGanar) {
            maximosDiasSinGanar = diasSinGanarPorPais[i].second;
        }
        i++;
    }

    vector<Pais> secos;
    i = 0;
    while(i < diasSinGanarPorPais.size()){
        if(diasSinGanarPorPais[i].second == maximosDiasSinGanar){
            secos.push_back(diasSinGanarPorPais[i].first);
        }
        i++;
    }

    return secos;
}

void JJOO::transcurrirDia() {
    int i = 0;
    vector<Competencia> competenciasDeHoy = this->cronograma(this->jornadaActual());
    while(i < competenciasDeHoy.size()) {
        if(!competenciasDeHoy[i].finalizada()) {
            Deporte dep = competenciasDeHoy[i].categoria().first;
            vector<Atleta> participantes = competenciasDeHoy[i].participantes();
            int j = 0;
            bool ordenado = false;
            while (!ordenado) {
                ordenado = true;
                while (j < participantes.size() - 1) {
                    if (participantes[j].capacidad(dep) < participantes[j + 1].capacidad(dep)) {
                        swap(participantes[j], participantes[j + 1]);
                        ordenado = false;
                    }
                    j++;
                }
            }
            vector<int> ranking;
            j = 0;
            while (j < participantes.size()) {
                ranking.push_back(participantes[j].ciaNumber());
                j++;
            }
            vector<pair<int, bool>> control(0);
            if (ranking.size() > 0) {
                pair<int, bool> testeado(ranking[0], false);
                control.push_back(testeado);
            }
            competenciasDeHoy[i].finalizar(ranking, control);
        }
        i++;
    }
    _cronograma[_jornadaActual - 1] = competenciasDeHoy;
    _jornadaActual++;
    return;
}
/*J 2016 3
[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
(A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
(A |Juliana| |Femenino| 1932 |Bosnia| 3 [(|Handball|, 50)]),
(A |Jenny| |Femenino| 1922 |USA| 4 [(|Softball|, 20)]),
(A |Jordan| |Masculino| 1930 |USA| 5 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)]),
(A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
[[(C (|Rugby|, |Masculino|) |True|
[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
(A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
(A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
[2, 1, 6] [(2, |True|)]),
(C (|Football|, |Masculino|) |True|
[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
(A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)])]
[1, 2] [(1, |True|)])],
[],
[(C (|Handball|, |Femenino|) |False|
[(A |Juliana| |Femenino| 1932 |Bosnia| 3 [(|Handball|, 50)])] [] []),
(C (|Softball|, |Femenino|) |False| [] [] [])],
[]]*/
void JJOO::mostrar(std::ostream &os) const {
    guardar(os);
}

void JJOO::guardar(std::ostream &os) const {
    os<<"J "<<_anio<<" "<<_jornadaActual<<"[";
    unsigned int i = 0;
    while(i < _atletas.size()){
        os<<"("<<_atletas[i]<<")";
        i++;
        if(i < _atletas.size()){
            os<<", ";
        }
    }
    os<<"]";
    unsigned int j;
    i = 0;
    os<<"[";
    while(i < _cronograma.size()){
        j = 0;
        os<<"[";
        while(j < _cronograma[i].size()){
            os<<"("<<_cronograma[i][j]<<")";
            j++;
            if(j < _cronograma[i].size()){
                os<<", ";
            }
        }
        os<<"]";
        i++;
        if(i < _cronograma.size()){
            os<<", ";
        }
    }
    os<<"]";
}

void JJOO::cargar(std::istream &is) {
    string at;
    is>>at>>_anio>>_jornadaActual;
    _atletas.clear();
    getline(is,at,'[');
    while(is.peek()!=']'){
        Atleta a("a",Genero::Masculino,1,"a",2); //Atleta con basura
        getline(is,at,'(');
        a.cargar(is);
        getline(is,at,')');
        _atletas.push_back(a);
    }
    _cronograma.clear();
    getline(is,at,'[');
    while(is.peek()!=']'){
        vector<Competencia> vc;
        getline(is,at,'[');
        while(is.peek()!=']'){
            Competencia c = Competencia(deportes[5], Genero::Femenino, std::vector<Atleta>());//competencia con basura
            getline(is,at,'(');
            c.cargar(is);
            getline(is,at,')');
            vc.push_back(c);
        }
        is.get();
        _cronograma.push_back(vc);
        if(is.peek()!=']'){
            vc.clear();
        }
    }
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    j.guardar(os);
    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {
    j.cargar(is);
    return is;
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

vector<Atleta> JJOO::_atletasSinPosicion(const vector<Atleta> &vec, int &i) const{
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

vector<pair<Atleta, int>> JJOO::_paresSinPosicion(const vector<pair<Atleta, int>> &vec, int &i) const{
    pair<Atleta, int> par (Atleta("Jorge",Genero::Masculino,1990,"Argentina",1), 0);
    std::vector<pair<Atleta, int>> newVec (vec.size() - 1, par);
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
};

vector<pair<Pais, int>> JJOO::_paresPaisesSinPosicion(const vector<pair<Pais, int>> &vec, int &i) const{
    std::vector<pair<Pais, int>> newVec (vec.size() - 1, pair<Pais, int> ("", 0));
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
};

//Esta funcion devuelve todos los atletas que ganaron medallas y el int de la
//posicion de la medalla, es decir, 0 para oro, 1 para plata y 2 para bronce
vector<pair<Atleta, int>> JJOO::_atletasQueGanaronAlgo() const {
    vector<pair<Atleta, int>> atletasConMedallas;
    int i = 0;
    while(i < this->competencias().size()){
        if(this->competencias()[i].ranking().size() > 0){
            atletasConMedallas.push_back(pair<Atleta, int> (this->competencias()[i].ranking()[0], 0));
        }
        if(this->competencias()[i].ranking().size() > 1){
            atletasConMedallas.push_back(pair<Atleta, int> (this->competencias()[i].ranking()[1], 1));
        }
        if(this->competencias()[i].ranking().size() > 2){
            atletasConMedallas.push_back(pair<Atleta, int> (this->competencias()[i].ranking()[2], 2));
        }
        i++;
    }
    return atletasConMedallas;
}

vector<Pais> JJOO::_paises() const {
    vector<Pais> paises;
    int i = 0;
    while(i < this->_atletas.size()){
        int j = 0;
        bool estaRepetido = false;
        while(j < paises.size()){
            if(paises[j] == this->_atletas[i].nacionalidad()){
                estaRepetido = true;
            }
            j++;
        }
        if(!estaRepetido){
            paises.push_back(this->_atletas[i].nacionalidad());
        }
        i++;
    }
    return paises;
}

bool JJOO::_ganoMedallasEseDia(Pais pais, int dia) const{
    bool gano = false;
    int i = 0;
    while(i < cronograma(dia).size()) {
        Competencia competencia = cronograma(dia)[i];
        int j = 0;
        while(j < competencia.ranking().size() && j < 3) {
            gano = gano || competencia.ranking()[j].nacionalidad() == pais;
            j++;
        }
        i++;
    }
    return gano;
}

int JJOO::_maximaDistanciaEntreJornadas(vector<int> jornadas) const {
    vector<int> distancias;
    int i = 1;
    while (i < jornadas.size()){
        distancias.push_back(jornadas[i] - jornadas[i - 1]);
        i++;
    }

    int maximaDistancia;
    i = 0;
    while(i < distancias.size()) {
        if(i == 0 || distancias[i] > maximaDistancia) {
            maximaDistancia = distancias[i];
        }
        i++;
    }

    return maximaDistancia;
}