#include <iostream>
#include "../include/atleta.h"
#include "../include/jjoo.h"

using namespace std;
vector<Competencia> Competenciaconoroenpodio(JJOO const &j) {
    vector<Atleta> Ganadores;
    int i = 0;
    while (i < Competenciaconoroenpodio(j).size()) {
        Ganadores.push_back(Competenciaconoroenpodio.ranking()[0]);
        i++;
    }
    int k = 0;
    while (k < Ganadores.size(j)) {
        int t = Ganadores[0].anioNacimiento();
        if (t < Ganadores[j].anioNacimiento()) {
            t = Ganadores;
        }
        k++;
    }

    return t;
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
