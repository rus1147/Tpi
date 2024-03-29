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
//E4: vale r == competencias[0].ranking()[0] & i == i @E3 competencias == competencias@E3
//Pc: r == competencias[0].ranking()[0] & i== 0 &
// competencias == j.competenciasFinalizadasConOroEnPodio() &

    while(i < competencias.size()){
    //C1 : vale B1 & I: 0 <= i <= competencias.size() &
    //(forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento() &
    //(exist c in competencias) r ==c.ranking()[0]

        //Pif: vale 0<= i< competencias.size() &
        // (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[i].ranking[0].anioNacimiento() &
        // (exist c in competencias) r ==c.ranking()[0]

        if(r.anioNacimiento() > competencias[i].ranking()[0].anioNacimiento()){
            //Eif1: vale B

            r = competencias[i].ranking()[0];
            //Eif2: vale r == competencias[i].ranking()[0]

        }
        //Qif: ((r.anioNacimiento() > competencias[i].ranking()[0].anioNacimiento() & r == competencias[i].ranking()[0])
        // || (r.anioNacimiento() <= competencias[i].ranking()[0].anioNacimiento() & r == r@C1)) & i == i@C1 &
        // (forall J in [0..(i)]) r.anioNacimiento() <= competencias[i].ranking()[0].anioNacimiento() &
        // (exist c in competencias) r ==c.ranking()[0]

        //C2: vale Qif

        i++;
    //C3: vale i == i@C2+1

    }
    //Qc: i == competencias.size() & (exist c in competencias) r ==c.ranking()[0] &
    //(forall J in [0..(competencias.size()-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento() &

//E5: vale Qc

    return r;
//E6: vale res == r@E5 & i@E5==competencias.size()
// (forall J in [0..i@5-1]) r.anioNacimiento() <= competencias[j].ranking()[0].anioNacimiento() &
// (exist c in competencias) r ==c.ranking()[0]


//Implica: (forall J in [0..competencias.size()-1]) res.anioNacimiento() <= competencias[j].ranking()[0].anioNacimiento()
// (exist c in competencias) r ==c.ranking()[0]
}

/*
EL ULTIMO ESTADO ANTES DE ENTRAR AL CICLO IMPLICA "Pc":
E4 => Pc: r == competencias[0].ranking()[0] & i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio()
(r == competencias[0].ranking()[0]) => r == (competencias[0].ranking()[0])
(competencias == competencias@E3 & i == i@E3) => (i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio())


"Pc" IMPLICA EL "Invariante":
Pc => I: 0 <= i <= competencias.size() & (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()
(i == 0) => (0 <= i <= competencias.size())
(i ==0 & r == competencias[0].ranking()[0] & i== 0 & competencias == j.competenciasFinalizadasConOroEnPodio())
 => (forall J in[0..(0-1)]) r.anioNacimiento() <= competencias[0].ranking[0].anioNacimiento())
(i == 0 & r == competencias[0].ranking()[0]) => (exist c in competencias) r ==c.ranking()[0]


EL "Invariante" Y "¬B" IMPLICAN LA SALIDA DEL CICLO
Fv(Funcion Variante):competencias.size()-i
C(cota):0
(I & Fv <= C) => ¬B
(FV <= C) <=> competencias.size()-i <= 0 <=> competencias.size() <= i (que es exactamente ¬B)


LA "¬B" Y "Invariante" IMPLICAN "Qc"
(¬B & I) => Qc: i==competencias.size() &
 (forall J in [0..competencias.size()-1]) r.anioNacimiento() <= competencias[i].ranking[0].anioNacimiento() &
 (exist c in competencias) r ==c.ranking()[0]


 1_(¬B & 0<=i<=competencias.size()) => i==competencias.size()
 2_(i==competencias.size() & (forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento())
 => (forall J in [0..competencias.size()-1]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento())


EL CUERPO DEL CICLO PRESERVA EL "Invariante" & LA "Funcion Variante" DECRECE:

C1 : vale B1 & I: 0 <= i <= competencias.size() &
(forall J in[0..(i-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento() &
(exist c in competencias) r ==c.ranking()[0]

(B1 & 0<= i <= competencias.size()) (IMPLICAN)=> (0 <= i < competencias.size())


C2: vale Qif



C3: vale i@C3 == i@C2+1 r.anioNacimiento() <= competencias[i@C2].ranking()[0].anioNacimiento() &
(forall J in [0..i@C2]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento() &
(exist c in competencias) r ==c.ranking()[0]



Implica i@C3-1 == i@C2 &
(forall J in [0..(i@C3-1)]) r.anioNacimiento() <= competencias[j].ranking[0].anioNacimiento()

(0<=i@C2< comptencias.size()) => (0<=i@C2+1<=competencias.size())
(0<=i@C2+1<=competencias.size()) => (0<=i@C3<=competencias.size())

LA "Funcion Variante" DECRECE EN CADA ITERACION DEL CICLO
i@C3 == i@C1+1  => competencias.size()-i@C3 < competencias.size()-i@C1



*/