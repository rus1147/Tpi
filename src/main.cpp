#include <fstream>
#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"


int main() {
    ifstream entrada("entrada.txt");
    ofstream salida("salida.txt");
    int cant,i=0;
    entrada>>cant;
    while(i<cant){
        Atleta atleta;
        atleta.cargar(entrada);
        atleta.mostrar(cout);
        atleta.guardar(salida);
        i++;
    }
    while(i<cant){
        Competencia competencia;
        competencia.cargar(entrada);
        competencia.mostrar(cout);
        competencia.guardar(salida);
        i++;
    }
    while (i<cant){
        JJOO jjoo;
        jjoo.cargar(entrada);
        jjoo.mostrar(cout);
        jjoo.guardar(salida);
        i++;
    }
    entrada.close();
    salida.close();
      return 0;
}