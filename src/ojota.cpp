#include <iostream>
#include "../include/atleta.h"
#include "../include/jjoo.h"

using namespace std;
/*vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {
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
*/

Atleta atletaProdigio(JJOO const &j){
    vector<Competencia> competencias;
    competencias = j.competenciasFinalizadasConOroEnPodio();
    int i = 0;
    Atleta r = competencias[0].ranking()[0];
    while(i < competencias.size()){
        if(r.anioNacimiento() > competencias[i].ranking()[0].anioNacimiento()){
            r = competencias[i].ranking()[0];
        }
        i++;
    }
    return r;
}
//ese es la de willy
//sino
/*
Atleta atletaProdigio(const JJOO &j){
    Competencia CompetenciaFin;
    Atleta a;
    bool esCampeon=false;
    int i=0;
    while(i<CompetenciaFin.size()){
        if(!CompetenciaFin.finalizada()){
            i++;
        }
        else
    }
}*/
