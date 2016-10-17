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
    vector<Competencia> competencias = this->competencias();
    int cantidadDeAtletasEliminados = 0;
    int i = 0;
    while(i < competencias.size() && i != -1){
        int r = int(competencias[i].participantes().size());
        if(competencias[i].categoria() == c){
            int j = 0;
            while(j < competencias[i].participantes().size()){
                if(competencias[i].participantes()[j].nacionalidad() == p){
                    competencias[i].linfordChristie(competencias[i].participantes()[j].ciaNumber());
                    cantidadDeAtletasEliminados++;
                }
                j++;
            }
            return cantidadDeAtletasEliminados;
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
// BUSCO LAS COMPETENCIAS FINALIZADAS PORR DIA
    int j = 0;
    vector<Competencia> compDelDia;
    vector< vector<Competencia> >compXDia;
    while(j< this-> _jornadaActual){
        compDelDia.clear();
        int i = 0;
        while(i< this-> _cronograma[j].size()){
            if(_cronograma[j][i].finalizada() && _cronograma[j][i].ranking().size() > 0){
                compDelDia.push_back(this-> _cronograma[j][i]);
            }
            i++;
        }
        compXDia.push_back(compDelDia);
        j++;
    }
// PAISES SIN REPETIDOS
    int i = 0;
    vector<Pais> paises;
    while(i < _atletas.size()){
        int r = 0;
        while(j < paises.size()){
            if(_atletas[i].nacionalidad() == paises[j]){
                r++;
            }
            j++;
        }
        if(r == 0){
            paises.push_back(_atletas[i].nacionalidad());
        }
        i++;
    }
//PARES DE PAISES CON SUS CANTIDAD DE GANADORES
    pair<Pais,int> PaisYMedals;
    vector<pair<Pais,int>> PaisesYMedals;
    vector<vector <pair <Pais,int> > > PaisesYMedalsXDia;
    i = 0;
    j = 0;
    while(j < compXDia.size()){
        int k = 0;
        while(k < paises.size()){
            int r = 0;
            while(i < compXDia[j].size()){
                if(compXDia[j][i].ranking()[0].nacionalidad() == paises[k]){
                    r++;
                }
                i++;
            }
            PaisYMedals.first = paises[j];
            PaisYMedals.second = r;
            PaisesYMedals.push_back(PaisYMedals);
            k++;
        }
        PaisesYMedalsXDia.push_back(PaisesYMedals);
        j++;
    }
//Maximo de apariciones de los paises (en el i-esimo dia) para despues filtrar
    i = 0;
    vector<int> maximoXDia;
    while(i < PaisesYMedalsXDia.size()){
        j = 0;
        int cant = 0;
        while(j < PaisesYMedalsXDia[i].size()){
            //toma la lista del dia (i-esimo) y la recorre tomando el mayor
            if(cant < PaisesYMedalsXDia[i][j].second){
                cant =PaisesYMedalsXDia[i][j].second;
            }
            j++;
        }
        maximoXDia.push_back(cant);
        i++;
    }
//FILTRAR POR LOS MAXIMO EN CANTIDAD
    i = 0;
    vector<Pais> paisesCant;
    vector< vector<Pais> > PaisesCantXDia;
    while(i < PaisesYMedalsXDia.size()){
        paisesCant.clear();
        while(j < PaisesYMedalsXDia[i].size()){
            if(maximoXDia[i] == PaisesYMedalsXDia[i][j].second){
                paisesCant.push_back(PaisesYMedalsXDia[i][j].first);
            }
            j++;
        }
        PaisesCantXDia.push_back(paisesCant);
        i++;
    }
//FILTRAR COMO SI FUERAN ENTEROS
    i = 0;
    vector<Pais> paisesC;
    while(i < PaisesCantXDia.size()){
        Pais p = PaisesCantXDia[i][0];
        while(j < PaisesCantXDia[i].size()){
            if(p < PaisesCantXDia[i][j]){
                p = PaisesCantXDia[i][j];
            }
            j++;
        }
        paisesC.push_back(p);
        i++;
    }
//BUSCO LA DISTANCIA QUE HAY ENTRE REPETIDOS Y TOMO LA PRIMERA
    i = 1;
    vector <int> distRep;
    while(i < paisesC.size()){
        Pais p = paisesC[0];
        if(p == paisesC[i]){
            distRep.push_back(i);
        }
        i++;
    }


//SI LA LISTA "DISTREP" NO TIENE ELEMENTOS DEVUELVE TRUE(NO HAY REPETIDOS)
    if(distRep.size() <= 0 ){
        return true;
    }
    else{
//DEVUELVO UN BOOL QUE INDICA, SI LA LISTA ESTA ORDENADA SIEMPRE RESPETANDO LA DISTANCIA DE REPETICION Y QUE SEA CICLICA
        i = 0;
        int m = 0;
        while(m < paisesC.size()-distRep[0]){
            m = distRep[0] * (i+1);
            if(paisesC[i] != paisesC[i + distRep[0]] ){
                return false;
            }
            i++;
        }
    }
    return true;
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
            if(this->ganoMedallasEseDia(paises[i], j)){
                jornadasGanadoras.push_back(j);
            }
            j++;
        }
        jornadasGanadoras.push_back(_jornadaActual);
        diasSinGanarPorPais.push_back(pair<Pais, int> (paises[i], this->maximaDistanciaEntreJornadas(jornadasGanadoras)));
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
}

void JJOO::guardar(std::ostream &os) const {
}

void JJOO::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    j.mostrar(os);
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

bool JJOO::ganoMedallasEseDia(Pais pais, int dia) const{
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

int JJOO::maximaDistanciaEntreJornadas(vector<int> jornadas) const {
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