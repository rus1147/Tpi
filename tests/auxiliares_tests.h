#ifndef TPI_AUXILIARES_TESTS_H
#define TPI_AUXILIARES_TESTS_H

#include <functional>
#include <algorithm>
#include "../include/competencia.h"

static std::vector<Pais> paises = {
        "Argentina",
        "Mauritius",
        "Suriname",
        "Islas Cook",
        "Barbuda y Antigua",
        "Republica de Nauru",
        "Republica Federal de Alemania",
        "Islas Marquesas",
        "Noruega",
        "Tasmania",
        "Republica Democratica de Timor Oriental",
        "Bhutan",
        "Principado de Andorra",
        "Burundi",
        "Burkina Faso"
};

static std::vector<Deporte> deportes = {
        "BMX",
        "Ciclismo",
        "Esgrima",
        "Gimnasia Acrobatica",
        "Gimnasia Artistica",
        "Gimnasia Ritmica",
        "Halterofilia",
        "Monopatin",
        "Natacion",
        "Pentatlon moderno",
        "Remo",
        "Skateboarding",
        "Tenis",
        "Tiro olimpico",
        "Triatlon",
        "Vela",
        "Voley"
};

template<class T>
void quitar(std::vector<T> &v, int index) {
    auto start = std::remove_if(v.begin(), v.end(), [index](Atleta a) { return a.ciaNumber() == index; });
    v.erase(start, v.end());
}

template<class T>
bool mismos(const vector<T> &l1, const vector<T> &l2) {
    bool todos_iguales = true;
    for (const auto &e: l1) {
        int c1 = std::count(l1.begin(), l1.end(), e);
        int c2 = std::count(l2.begin(), l2.end(), e);

        todos_iguales &= (c1 == c2);
    }

    return (l1.size() == l2.size()) && todos_iguales;
}

template<class T>
bool pertenece(const std::vector<T> &v, const T &e) {
    return std::find(v.begin(), v.end(), e) != v.end();
}

template<class T>
bool ordenado_por(const std::vector<T> &v, std::function<bool(const T &, const T &)> f) {
    return std::is_sorted(v.begin(), v.end(), f);
}

static const Atleta &porCIA(const std::vector<Atleta> &v, int cia_number) {
    long index = std::distance(v.begin(), std::find_if(v.begin(), v.end(), [cia_number](Atleta a) {
        return a.ciaNumber() == cia_number;
    }));
    return v[index];
}

inline bool
leDioPositivo_se_corresponde_con_los_controles(Competencia competencia, std::vector<std::pair<int, bool>> controles) {
    return std::all_of(controles.begin(), controles.end(), [competencia](std::pair<int, bool> pp) {
        return competencia.leDioPositivo(porCIA(competencia.participantes(), pp.first)) == pp.second;
    });
}

inline bool finaliza_correctamente(const Competencia c) {
    std::function<bool(const Atleta &, const Atleta &)> f = [c](const Atleta &a, const Atleta &b) {
        return a.capacidad(c.categoria().first) > b.capacidad(c.categoria().first);
    };
    std::vector<Atleta> rank = c.ranking();
    return ordenado_por(c.ranking(), f)
           && std::all_of(rank.begin(), rank.end(), [c](const Atleta &a) {
        return (!pertenece(c.lesTocoControlAntiDoping(), a) || !c.leDioPositivo(a));
    });

}

inline bool transcurre_correctamente(const Competencia c) {
    std::function<bool(const Atleta &, const Atleta &)> f = [c](const Atleta &a, const Atleta &b) {
        return a.capacidad(c.categoria().first) > b.capacidad(c.categoria().first);
    };
    std::vector<Atleta> rank = c.ranking();
    return ordenado_por(c.ranking(), f)
           && std::all_of(rank.begin(), rank.end(), [c](const Atleta &a) {
        return (!pertenece(c.lesTocoControlAntiDoping(), a) || !c.leDioPositivo(a));
    })
           && (c.ranking().size() < 1 || c.lesTocoControlAntiDoping().size() == 1);

}


#endif //TPI_AUXILIARES_TESTS_H
