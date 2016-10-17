#include <iostream>
#include "../include/atleta.h"
#include "../include/jjoo.h"

using namespace std;

Atleta atletaProdigio(JJOO const &j){
//E0: vale |j.competenciasFinalizadasConOroEnPodio()| > 0
    vector<Competencia> competencias;
//E1: vale competencias == []
    competencias = j.competenciasFinalizadasConOroEnPodio();
    //como el requiere de la funcion competenciasFinalizadasConOroEnPodio es true, puedo usarla
    //y tomar sus postcondiciones como ciertas y juntando con el requiere del problema
    // tengo que la lista tiene almenos una competencia
    // y que si hay mas de una, todas ellas tienen mas al menos un atleta en el ranking
//E2: vale competencias == j.competenciasFinalizadasConOroEnPodio
    int i = 0;
//E3: vale i ==0 & competencias == competencias@E2
//Implica: i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio()
    Atleta r = competencias[0].ranking()[0];
//E4: vale r == competencia[0].ranking()[0] & i == i @E3 competencia == competencia@E3
//Pc: r == competencia[0].ranking()[0] & i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio()
    while(i < competencias.size()){
    //C1 : vale B1 & I: 0 <= i <= competencias.size() &
    //(forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()

        //Pif: vale 0<= i< competencias.size() &
        // (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[i].ranking[0].anioNacimiento()
        if(r.anioNacimiento() > competencias[i].ranking()[0].anioNacimiento()){
            //Eif1: vale B
            r = competencias[i].ranking()[0];
            //Eif2: vale r == competencias[i].ranking()[0]
        }
        //Qif: (r.anioNacimiento() > competencias[i].ranking()[0].anioNacimiento() & r == competencias[i].ranking()[0])
        // || (r.anioNacimiento() <= competencias[i].ranking()[0].anioNacimiento() & r == r@C1)
    //C2: vale Qif & i == i@C1
        i++;
    //C3: vale i == i@C2+1
    }
    //Qc: i == competencias.size() &
    //(forall J in [0..(competencias.size()-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()

    return r;
}

/*

E4 => Pc: r == competencia[0].ranking()[0] & i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio()
(r == competencia[0].ranking()[0]) => r == (competencia[0].ranking()[0])
(competencia == competencia@E3 & i == i@E3) => (i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio())



Pc => I: 0 <= i <= competencias.size() & (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()
(i == 0) => (0 <= i <= competencias.size())
(i ==0 & r == competencia[0].ranking()[0] & i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio())
 => (forall J in[0..(0-1)]) r.anioNacimiento() <= competencias[0].ranking[0].anioNacimiento())


Fv(Funcion Variante):competencias.size()-i
C(cota):0
(I & Fv <= C) => ¬B
(FV <= C) <=> competencias.size()-i <= 0 <=> competencias.size() <= i (que es exactamente ¬B)



(¬B & I) => Qc: i==competencias.size() & (forall J in [0..competencias.size()-1]) r.anioNacimiento() <= competencia[i].ranking[0].anioNacimiento()
 1_(¬B & 0<=i<=competencias.size()) => i==competencias.size()
 2_(i==competencias.size() & (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento())
 => (forall J in [0..competencias.size()-1]) r.anioNacimiento() <= competencia[j].ranking[0].anioNacimiento())



 falta el cuerpo del ciclio preserva el invariante y que la Fv(Funcion Variante es decreciente)
C1 : vale B1 & I: 0 <= i <= competencias.size() & (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()


C2: vale Qif & i == i@C1


C3: vale i == i@C2+1

 */