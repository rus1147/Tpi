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
    vector<Atleta> ret;
    ret = _atletas;
    vector<Competencia> com;
    int i = 0;
    while(i< this-> _cronograma.size()){
        int j = 0;
        while(j< this-> _cronograma[j].size()){
            com.push_back(this-> _cronograma[j][i]);
            i++;
        }
        j++;
    }
    i = 0;
    while(i < ret.size()){
        int j = 0;
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
    int i = 0;
    vector<Competencia> todasLasCompetencias;
    while(i < this->_cronograma.size()){
        int j = 0;
        while(j < this->_cronograma[i].size()){
            todasLasCompetencias.push_back(this->_cronograma[i][j]);
            j++;
        }
        i++;
    }
    i = 0;
    int r = 0;
    vector<Atleta> CatSinPaisP;
    while(i < todasLasCompetencias.size() && i != -1){
        r = int(todasLasCompetencias[i].participantes().size());
        if(todasLasCompetencias[i].categoria() == c){
            int j = 0;
            while(todasLasCompetencias[i].participantes()[j].nacionalidad() != p){
                CatSinPaisP.push_back(todasLasCompetencias[i].participantes()[j]);
                j++;
            }
            todasLasCompetencias[i].participantes() = CatSinPaisP;
            i = -1;
        }
        else{
            i++;
        }
    }
    return r - int(CatSinPaisP.size());
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    int j = 0;
    int i = 0;
// BUSCO LAS COMPETENIAS FINALIZADAS
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
// BUSCO LOS ATLETAS GANADORES, LOS ATLETAS QUE NO ESTAN EN ESA LISTA VAN A SER LOS QUE NUNCA GANARON
    j = 0;
    i = 0;
    vector<Atleta> atletasGanadores;
    while (i < _atletas.size()){
        while(j < comFinalizadas.size()){
            if((comFinalizadas[j].ranking().size() > 0 && comFinalizadas[j].ranking()[0].ciaNumber() == _atletas[i].ciaNumber())
               || (comFinalizadas[j].ranking().size() > 1 && comFinalizadas[j].ranking()[1].ciaNumber() == _atletas[i].ciaNumber())
               || (comFinalizadas[j].ranking().size() > 2 && comFinalizadas[j].ranking()[2].ciaNumber() == _atletas[i].ciaNumber())  ) {
                atletasGanadores.push_back(this->_atletas[i]);
            }
            j++;
        }
        i++;
    }
//BUSCP LOS ATLETAS DEL PAIS P
    vector<Atleta> atletasDeP;
    i = 0;
    while(j< _atletas.size()){
        if(_atletas[i].nacionalidad() == p){
            atletasDeP.push_back(_atletas[i]);
        }
    }
//TOMO LOS QUE SON DEL PAIS "P" Y NUNCA GANARON
    i = 0;
    j = 0;
    vector<Atleta> PyNuncaGanaron;
    while(j < atletasDeP.size()){
        int r = 0;
        while(i < atletasGanadores.size()){
            if(atletasDeP[j] == atletasGanadores[i]){
                r++;
            }
            i++;
        }
        if(r == 0){
            PyNuncaGanaron.push_back(atletasDeP[j]);
        }
    }
    //TOMO TODAS LAS COMPETENCIAS (FINALIZADAS O NO, QUIERO CONTAR LAS VECES QUE APARECE COMO PARTICIPANTE)
    vector<Competencia> allCom;
    i = 0;
    while(i < this->_cronograma.size()){
        j = 0;
        while(j < this->_cronograma[i].size()){
            allCom.push_back(this->_cronograma[i][j]);
            j++;
        }
        i++;
    }
//TOMO UNA LISTA DE ATLETAS CON SU CANTIDAD DE APARICIONES
    i = 0;
    vector<pair<Atleta,int >> AtletasYCom;
    pair<Atleta,int > atletaYCom (this->_atletas[0], 0);
    while(i < PyNuncaGanaron.size() ){
        j = 0;
        int cant = 0;
        while(j < allCom.size()){
            int k = 0;
            while(k < allCom[j].participantes().size()){
                if(PyNuncaGanaron[i] == allCom[j].participantes()[k]){
                    cant++;
                }
            }
        }
        atletaYCom.first = PyNuncaGanaron[j];
        atletaYCom.second = cant;
        AtletasYCom.push_back(atletaYCom);
    }
    //BUSCO LA CANTIDAD MAXIMA QUE APARECEN LOS ATLETAS
    i = 0;
    int maxCant = AtletasYCom[0].second;
    while(i < AtletasYCom.size()){
        if(maxCant < AtletasYCom[i].second){
            maxCant = AtletasYCom[i].second;
        }
        i++;
    }
//FILTRO POR LOS QUE TIENEN LA MAYOR CANTIDAD DE APARICIONES (PARTICIPACIONES EN COMPETENCIAS)
    i = 0;
    vector<Atleta> ret;
    while(i < AtletasYCom.size()){
        if(AtletasYCom[i].second == maxCant){
            ret.push_back(AtletasYCom[i].first);
        }
    }
    return ret;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
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
        int k = 0;
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
    // BUSCO LAS COMPETENCIAS FINALIZADAS PORR DIA
    int j = 0;
    vector<Competencia> compDelDia;
    vector< vector<Competencia> >compXDia;
    while(j< this-> _jornadaActual){
        compDelDia.clear();
        int i = 0;
        while(i< this-> _cronograma[j].size()){
            if(_cronograma[j][i].finalizada()){
                compDelDia.push_back(this-> _cronograma[j][i]);
            }
            i++;
        }
        compXDia.push_back(compDelDia);
        j++;
    }
// PAISES GANADORES CON REPETIDOS
    int i = 0;
    vector<Pais> paisesganadorRep;
    vector<vector<Pais>> paisesXDiaRep;
    while(i < compXDia.size()){
        j = 0;
        paisesganadorRep.clear();
        while(j < compXDia[i].size()){
            if(compXDia[i][j].ranking().size() > 2){
                paisesganadorRep.push_back(compXDia[i][j].ranking()[2].nacionalidad());
                paisesganadorRep.push_back(compXDia[i][j].ranking()[1].nacionalidad());
                paisesganadorRep.push_back(compXDia[i][j].ranking()[0].nacionalidad());
            }
            else if(compXDia[i][j].ranking().size() > 1){
                paisesganadorRep.push_back(compXDia[i][j].ranking()[1].nacionalidad());
                paisesganadorRep.push_back(compXDia[i][j].ranking()[0].nacionalidad());
            }
            if(compXDia[i][j].ranking().size() > 0){
                paisesganadorRep.push_back(compXDia[i][j].ranking()[0].nacionalidad());
            }
            j++;
        }
        paisesXDiaRep.push_back(paisesganadorRep);
        i++;
    }
//PAISES SIN REPETIDOS(EN ESE DIA) Y GANARON ALGUNA MEDALLA
    i = 0;
    vector<Pais> paisesDelDia;
    vector< vector<Pais> > paisesXDia;
    while(i < paisesXDiaRep.size()){
        j = 0;
        paisesDelDia.clear();
        while(j < paisesXDiaRep[i].size()){
            int r = 0;
            int k = 0;
            while(k < paisesXDia[i].size()){
                if(paisesXDiaRep[i][j] == paisesXDia[i][k]){
                    r++;
                }
                k++;
            }
            if(r == 0){
                paisesDelDia.push_back(paisesXDiaRep[i][j]);
            }
            j++;
        }
        paisesXDia.push_back(paisesDelDia);
        i++;
    }
//armo una lista de todos los paises que ganaron(ConRepetidos)
    i = 0;
    j = 0;
    vector<Pais> todosLosPCOnRep;
    while(i < paisesXDia.size()){
        while(j < paisesXDia.size()){
            todosLosPCOnRep.push_back(paisesXDia[i][j]);
            j++;
        }
        i++;
    }
//armo una lista con todos los paises que ganaron(SinRepetidos), asi despues filtrar es mas facil(de ver)
    i = 0;
    vector<Pais> todosLosP;
    while(i < todosLosPCOnRep.size()){
        j = 0;
        int r = 0;
        while(j < todosLosP.size()){
            if(todosLosPCOnRep[i] == todosLosP[j]){
                r++;
            }
            j++;
        }
        if(r == 0){
            todosLosP.push_back(todosLosPCOnRep[i]);
        }
        i++;
    }
//armo una lista de los paises con sus apariciones
    i = 0;
    vector<int> apariciones;
    pair<Pais,vector<int>> PYsusApariciones;
    vector< pair<Pais, vector<int>> > paisesYSusApariciones;
    while(i < todosLosP.size()){
        j = 0;
        while(j < paisesXDia.size()){
            int r = 0;
            apariciones.clear();
            while(r < paisesXDia[j].size()){
                if(todosLosP[i] == paisesXDia[i][j]){
                    apariciones.push_back(i);
                }
                r++;
            }
            j++;
        }
        PYsusApariciones.first = todosLosP[i];
        PYsusApariciones.second = apariciones;
        paisesYSusApariciones.push_back(PYsusApariciones);
        i++;
    }
//saco las distancias (entre apariciones )y tomo las primeras apariciones
    i = 0;
    pair<Pais,vector<int>> pConDiferencias;
    vector<pair<Pais,vector<int>>> paisesConDiferencias;
    vector<int > diferencias;
    while(i < paisesYSusApariciones.size()){
        j = 0;
        diferencias.clear();
        diferencias.push_back(paisesYSusApariciones[i].second[0]);
        while(j< paisesYSusApariciones[i].second.size()-1){
            int r = paisesYSusApariciones[i].second[j+1]-paisesYSusApariciones[i].second[j];
            diferencias.push_back(r);
            j++;
        }
        pConDiferencias.first = paisesYSusApariciones[i].first;
        pConDiferencias.second = diferencias;
        paisesConDiferencias.push_back(pConDiferencias);
        i++;
    }
//busco el maximo de las diferencias
    i = 0;
    int max = 0;
    while(i < paisesConDiferencias.size()){
        int r = paisesConDiferencias[i].second[0];
        while(j < paisesConDiferencias[i].second.size()){
            if(r < paisesConDiferencias[i].second[j]){
                r = paisesConDiferencias[i].second[j];
            }
            j++;
        }
        if(max < r){
            max = r;
        }
        i++;
    }
//filtro con max(el mayor tiempo que paso algun pais esperando ganar)
    i = 0;
    vector<Pais> paisesSequia;
    while(i < paisesConDiferencias.size()){
        int r = 0;
        while(j < paisesConDiferencias[i].second.size()){
            if(paisesConDiferencias[i].second[j] == max){
                r++;
            }
            j++;
        }
        if(r > 0){
            paisesSequia.push_back(paisesConDiferencias[i].first);
        }
        i++;
    }
    return paisesSequia;
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