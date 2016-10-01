#include "gtest/gtest.h"
#include <algorithm>

#include "../include/atleta.h"
#include "../include/competencia.h"
#include "auxiliares_tests.h"


TEST(competencia_tests, observadores_de_competencia_sin_atletas) {
    Competencia comp = Competencia(deportes[5], Genero::Femenino, std::vector<Atleta>());

    ASSERT_EQ(deportes[5], comp.categoria().first);
    ASSERT_EQ(std::vector<Atleta>(), comp.participantes());
    ASSERT_EQ(Genero::Femenino, comp.categoria().second);
    ASSERT_FALSE(comp.finalizada());
}

TEST(competencia_tests, observador_participantes) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 10; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte(deportes[11], (i % 11) * 10);
    }

    Competencia comp = Competencia(deportes[11], Genero::Masculino, atletas);

    ASSERT_EQ(deportes[11], comp.categoria().first);
    ASSERT_EQ(Genero::Masculino, comp.categoria().second);
    ASSERT_FALSE(comp.finalizada());

    ASSERT_TRUE(mismos<Atleta>(atletas, comp.participantes()));
}

TEST(competencia_tests, igualdad_de_competencia) {
    Competencia comp = Competencia(deportes[7], Genero::Masculino, std::vector<Atleta>());
    Competencia otra_comp = Competencia(deportes[7], Genero::Masculino, std::vector<Atleta>());
    Competencia otra_comp_distinta_por_genero = Competencia(deportes[7], Genero::Femenino, std::vector<Atleta>());
    Competencia otra_comp_distinta_por_disciplina = Competencia(deportes[6], Genero::Masculino, std::vector<Atleta>());

    ASSERT_TRUE(comp == otra_comp);
    ASSERT_FALSE(comp == otra_comp_distinta_por_genero);
    ASSERT_FALSE(comp == otra_comp_distinta_por_disciplina);

    std::vector<Atleta> atletas;
    for (int i = 0; i < 8; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte(deportes[7], (i % 11) * 10);
    }

    Competencia otra_comp_distinta_con_atletas = Competencia(deportes[7], Genero::Masculino, atletas);
    ASSERT_FALSE(comp == otra_comp_distinta_con_atletas);
}


TEST(competencia_tests, igualdad_de_competencias_con_atletas) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 10; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte(deportes[8], (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte(deportes[9], (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte(deportes[10], (i % 10) * 9);
    }
    std::vector<Atleta> otros_atletas;
    for (int i = 0; i < 10; i++) {
        otros_atletas.emplace_back(std::to_string(i), Genero::Femenino, 1900 + i, paises[i % paises.size()], i);
        otros_atletas[i].entrenarNuevoDeporte(deportes[8], (i % 11) * 10);
        otros_atletas[i].entrenarNuevoDeporte(deportes[9], ((i + 1) % 10) * 10);
        otros_atletas[i].entrenarNuevoDeporte(deportes[10], (i % 10) * 9);
    }
    std::vector<Atleta> otros_menos_atletas;
    for (int i = 0; i < 9; i++) {
        otros_menos_atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        otros_menos_atletas[i].entrenarNuevoDeporte(deportes[8], (i % 11) * 10);
        otros_menos_atletas[i].entrenarNuevoDeporte(deportes[9], (i % 10) * 10);
        otros_menos_atletas[i].entrenarNuevoDeporte(deportes[10], (i % 10) * 9);
    }

    std::vector<Atleta> no_atletas;

    std::vector<Atleta> otros_mas_atletas;
    for (int i = 0; i < 11; i++) {
        otros_mas_atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        otros_mas_atletas[i].entrenarNuevoDeporte(deportes[8], (i % 11) * 10);
        otros_mas_atletas[i].entrenarNuevoDeporte(deportes[9], (i % 10) * 10);
        otros_mas_atletas[i].entrenarNuevoDeporte(deportes[10], (i % 10) * 9);
    }

    Competencia comp = Competencia(deportes[8], Genero::Masculino, atletas);
    Competencia otra_comp = Competencia(deportes[8], Genero::Masculino, atletas);


    ASSERT_EQ(deportes[8], comp.categoria().first);
    ASSERT_EQ(Genero::Masculino, comp.categoria().second);
    ASSERT_FALSE(comp.finalizada());

    ASSERT_TRUE(mismos<Atleta>(atletas, comp.participantes()));
    ASSERT_TRUE(comp ==
                otra_comp); //comp y otra comp son iguales. Un error aca significa que el operator== no esta comparando bien los atletas posiblemente
    otra_comp = Competencia(deportes[8], Genero::Masculino, otros_atletas);
    ASSERT_FALSE(comp == otra_comp);//Si esto falla posiblemente no estan comparando el genero de los atletas
    otra_comp = Competencia(deportes[8], Genero::Masculino, otros_menos_atletas);
    ASSERT_FALSE(comp ==
                 otra_comp);//Si esto falla posiblemente estan comparando que los atletas de comp esten en otra_comp pero no revisan que las longitudes sean iguales
    otra_comp = Competencia(deportes[8], Genero::Masculino, otros_mas_atletas);
    ASSERT_FALSE(comp ==
                 otra_comp);//Si esto falla posiblemente estan comparando que los atletas de otra_comp esten en comp pero no revisan que las longitudes sean iguales
    otra_comp = Competencia(deportes[8], Genero::Masculino, no_atletas);
    ASSERT_FALSE(comp == otra_comp);//Si esto falla hay algun problema cuando la lista de atletas esta vacia
}

TEST(competencia_tests, finalizar_comp_sin_atletas) {
    Competencia comp = Competencia(deportes[13], Genero::Femenino, std::vector<Atleta>());

    ASSERT_FALSE(comp.finalizada());

    comp.finalizar({}, {});

    ASSERT_TRUE(comp.finalizada());
}

TEST(competencia_tests, finalizar_comp_con_atletas) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte(deportes[4], (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte(deportes[0], (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte(deportes[14], (i % 10) * 9);
    }

    Competencia competencia = Competencia(deportes[4], Genero::Femenino, atletas);

    competencia.finalizar({10, 21, 20}, {{10, true},
                                         {21, true},
                                         {20, false}});

    ASSERT_TRUE(competencia.finalizada());
}

TEST(competencia_tests, ranking_comp_sin_atletas) {
    Competencia competencia = Competencia(deportes[11], Genero::Femenino, std::vector<Atleta>());
    competencia.finalizar({}, {});

    ASSERT_EQ(competencia.ranking(), std::vector<Atleta>());
}

TEST(competencia_tests, ranking_comp_con_atletas) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte("Voleibol de playa", (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte("Badminton", (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte("Balonmano", (i % 10) * 9);
    }

    Competencia competencia = Competencia("Voleibol de playa", Genero::Femenino, atletas);

    auto posiciones = std::vector<int>({10, 21, 20});


    competencia.finalizar({10, 21, 20}, {{10, true},
                                         {21, true},
                                         {20, false}});
    std::vector<int> cias;

    for (auto &a : competencia.ranking()) cias.push_back(a.ciaNumber());

    ASSERT_EQ(posiciones, cias);
}

TEST(competencia_tests, control_y_dopping_en_comp_con_atletas) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte("Voleibol de playa", (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte("Badminton", (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte("Balonmano", (i % 10) * 9);
    }

    Competencia competencia = Competencia("Voleibol de playa", Genero::Femenino, atletas);

    auto posiciones = std::vector<int>({10, 21, 20});

    std::vector<std::pair<int, bool>> controles = {{10, true},
                                                   {21, true},
                                                   {20, false}};

    competencia.finalizar(posiciones, controles);
    std::vector<int> cias;
    for (auto &a: competencia.lesTocoControlAntiDoping()) cias.push_back(a.ciaNumber());

    ASSERT_TRUE(mismos(posiciones, cias));
    //ASSERT_TRUE();
}

TEST(competencia_tests, ganan_los_mas_capaces) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte("Voleibol de playa", (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte("Badminton", (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte("Balonmano", (i % 10) * 9);
    }

    Competencia competencia = Competencia("Voleibol de playa", Genero::Femenino, atletas);
    Competencia competencia_donde_no = competencia;

    std::vector<std::pair<int, bool>> controles = {{10, false},
                                                   {21, false},
                                                   {18, true}};

    competencia.finalizar({10, 21, 20}, controles);
    competencia_donde_no.finalizar({5, 19, 21}, controles);
    ASSERT_TRUE(competencia.gananLosMasCapaces());
    ASSERT_FALSE(competencia_donde_no.gananLosMasCapaces());
}

TEST(competencia_tests, sancionar_tramposo) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Masculino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte("Voleibol de playa", (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte("Badminton", (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte("Balonmano", (i % 10) * 9);
    }

    Competencia competencia = Competencia("Voleibol de playa", Genero::Femenino, atletas);

    auto posiciones = std::vector<int>({10, 21, 20});

    std::vector<std::pair<int, bool>> controles = {{21, true},
                                                   {10, true},
                                                   {20, false}};

    competencia.finalizar(posiciones, controles);

    competencia.sancionarTramposos();

    std::vector<int> cias;
    for (auto &a: competencia.ranking()) cias.push_back(a.ciaNumber());

    ASSERT_FALSE(mismos(posiciones, cias));
    ASSERT_TRUE(mismos({20}, cias));
    ASSERT_TRUE(leDioPositivo_se_corresponde_con_los_controles(competencia, controles));
}

TEST(competencia_tests, linford_christie) {
    std::vector<Atleta> atletas;
    for (int i = 0; i < 22; i++) {
        atletas.emplace_back(std::to_string(i), Genero::Femenino, 1900 + i, paises[i % paises.size()], i);
        atletas[i].entrenarNuevoDeporte("Voleibol de playa", (i % 11) * 10);
        atletas[i].entrenarNuevoDeporte("Badminton", (i % 10) * 10);
        atletas[i].entrenarNuevoDeporte("Balonmano", (i % 10) * 9);
    }

    Competencia competencia = Competencia("Voleibol de playa", Genero::Femenino, atletas);

    ASSERT_TRUE(mismos(competencia.participantes(), atletas));

    int linford = 4;

    quitar(atletas, linford);
    competencia.linfordChristie(linford);

    ASSERT_TRUE(mismos(competencia.participantes(), atletas));
}
