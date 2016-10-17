#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"
//ESTOS TEST NO TIENEN QUE IR EN EL INFORME FINAL
//borrar test antes de entregar
void mostrarDeportes(Atleta &at){
    cout << "Deportes de " << at.nombre() <<":\n";
    vector<Deporte> deportes = at.deportes();
    for(int a = 0; a<deportes.size(); a++){
        cout << "\t" << deportes[a] << " - Capacidad: "<< at.capacidad(deportes[a]) << endl;
    }
}

void mostrarEspecialidad(Atleta &at){
    cout << "Especialidad:\n\t " <<at.especialidad() << " con " << at.capacidad(at.especialidad()) << endl;
}

void mostrarParticipantesCompetencia(Competencia &c){
    cout << "Participantes:\n";
    vector<Atleta> participantes = c.participantes();
    for(int a = 0; a<participantes.size(); a++){
        cout << "\t" << participantes[a].nombre() << " - Cia number: "<< participantes[a].ciaNumber() << endl;
    }
}

void mostrarRankingCompetencia(Competencia &c){
    cout << "Ranking:\n";
    if(c.finalizada()){
        vector<Atleta> participantes = c.ranking();
        for(int a = 0; a<participantes.size(); a++){
            cout << "\t" << (a+1) << ". " << participantes[a].nombre() << " - Cia number: "<< participantes[a].ciaNumber() << endl;
        }
    }else{
        cout << "\t(La competencia no finalizó)"<<endl;
    }
}

void mostrarDopingCompetencia(Competencia &c){
    cout << "Antidoping:\n";
    if(c.finalizada()){
        vector<Atleta> participantes = c.lesTocoControlAntiDoping();
        for(int a = 0; a<participantes.size(); a++){
            cout << "\t" << participantes[a].nombre() << " - Cia number: "<< participantes[a].ciaNumber() << endl;
            string result = "No";
            if(c.leDioPositivo(participantes[a])) result = "Drogadicto";
            cout << "\t\t¿Le dio positivo?: " << result << endl;
        }
    }else{
        cout << "\t(La competencia no finalizó)"<<endl;
    }
}

int main() {
    //Testeo de atleta
    cout << "-=- Tests de atleta -=-"<<endl;
    Atleta peter("Peter", Masculino, 1996, "Argentino", 39);
    cout << "Datos básicos:"<<endl;
    cout << "\t" << peter.nombre() << endl;
    cout << "\t" << peter.genero() << endl;
    cout << "\t" << peter.anioNacimiento() << endl;
    cout << "\t" << peter.nacionalidad() << endl;
    cout << "\t" << peter.ciaNumber() << endl;
    mostrarDeportes(peter);
    mostrarEspecialidad(peter);
    cout << "Le enseño nuevos deportes."<<endl;
    peter.entrenarNuevoDeporte("Xavier es un pelado bueno", 51);
    peter.entrenarNuevoDeporte("Sadosky Free Style Ping Pong", 88);
    peter.entrenarNuevoDeporte("Samba furiosa", 7);
    mostrarDeportes(peter);
    mostrarEspecialidad(peter);
    cout << "Tests de igualdad:"<<endl;
    Atleta jordi("Jordi", Masculino, 1996, "Argentino", 12);
    Atleta peter3("Peter", Masculino, 1996, "Argentino", 39);
    peter3 = peter;
    cout << "\t" << peter.nombre() << "==" << jordi.nombre() <<": " << (peter == jordi) << endl;
    cout << "\t" << peter.nombre() << "==" << peter3.nombre() <<": " << (peter == peter3) << endl;
    cout << endl;

    //Testeo de competencia
    cout << "-=- Tests de competencia -=-"<<endl;
    Atleta ramon("Ramón", Masculino, 1970, "Argentino", 28);
    ramon.entrenarNuevoDeporte("Tenis", 80);
    Atleta carlitos("Carlitos", Masculino, 1810, "Argentino", 155);
    carlitos.entrenarNuevoDeporte("Tenis", 2);
    Competencia miComp("Tenis", Masculino, {peter, jordi, ramon, carlitos});
    cout << "Detalles básicos:"<<endl;
    cout << "\tCategoría: " << miComp.categoria().first << ", " << miComp.categoria().second << endl;
    cout << "\tFinalizada: " << miComp.finalizada() << endl;
    mostrarParticipantesCompetencia(miComp);
    mostrarRankingCompetencia(miComp);
    mostrarDopingCompetencia(miComp);
    cout << "(Linford Christie a Carlitos)" << endl;
    miComp.linfordChristie(155);
    mostrarParticipantesCompetencia(miComp);
    cout << "(Finalizo la competencia.)" << endl;
    miComp.finalizar({28,12,39}, {make_pair(28, false), make_pair(12, true), make_pair(39, false)});
    cout << "Ahora finalizada vale: " << miComp.finalizada() << endl;
    mostrarParticipantesCompetencia(miComp);
    mostrarRankingCompetencia(miComp);
    mostrarDopingCompetencia(miComp);
    cout << "¿Ganan los más capaces?: " << miComp.gananLosMasCapaces() << endl;
    cout << "(La finalizo con otro ranking.)" << endl;
    miComp.finalizar({12,28,39}, {make_pair(28, false), make_pair(12, true), make_pair(39, false)});
    mostrarRankingCompetencia(miComp);
    cout << "¿Ahora ganan los más capaces?: " << miComp.gananLosMasCapaces() << endl;
    cout << "(Sanciono a los que tenían doping positivo.)"<<endl;
    miComp.sancionarTramposos();
    mostrarRankingCompetencia(miComp);
    Competencia miComp2("Tenis", Masculino, {peter, jordi, ramon, carlitos});
    miComp2 = miComp;
    Competencia miComp3("Tenis", Masculino, {peter, jordi, ramon, carlitos});
    cout << "Tests de igualdad:"<<endl;
    cout << "\t" << "Comp 1 y Comp 2: " << (miComp == miComp2) << endl;
    cout << "\t" << "Comp 1 y Comp 3: " << (miComp == miComp3) << endl;
}