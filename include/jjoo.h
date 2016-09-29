#ifndef __JJOO__
#define __JJOO__

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"


class JJOO {

private:
    int _anio;
    vector<Atleta> _atletas;
    vector<vector<Competencia> > _cronograma;
    int _jornadaActual;

public:
    JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs);

    int anio() const;

    vector<Atleta> atletas() const;

    int cantDias() const;

    int jornadaActual() const;

    vector<Competencia> cronograma(const int &d) const;

    vector<Competencia> competencias() const;

    vector<Competencia> competenciasFinalizadasConOroEnPodio() const;

    vector<Atleta> dePaseo() const;

    vector<pair<Pais, vector<int> > > medallero() const;

    int boicotPorDisciplina(const Categoria &c, const Pais &p);

    vector<Atleta> losMasFracasados(const Pais &p) const;

    void liuSong(const Atleta &a, const Pais &p);

    Atleta stevenBradbury() const;

    bool uyOrdenadoAsiHayUnPatron() const;

    vector<Pais> sequiaOlimpica() const;

    void transcurrirDia();

    bool operator==(const JJOO &j) const;

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const JJOO &j);

std::ostream &operator>>(std::ostream &os, const JJOO &j);

#endif /*__JJOO__*/