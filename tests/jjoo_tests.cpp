#include "gtest/gtest.h"
#include <algorithm>

#include "../include/atleta.h"
#include "../include/jjoo.h"

#include "auxiliares_tests.h"


TEST(jjoo_tests, observadores_muestran_lo_construido) {
    std::vector<Atleta> atletas;
    JJOO jo = JJOO(2016, {}, {{}});

    ASSERT_EQ(2016, jo.anio());
    ASSERT_EQ(atletas, jo.atletas());
    ASSERT_EQ(1, jo.cantDias());
    ASSERT_EQ(1, jo.jornadaActual());
    ASSERT_TRUE(jo.cronograma(1).empty());
    ASSERT_TRUE(jo.competencias().empty());
}

TEST(jjoo_tests, observador_competencias) {
    std::vector<Atleta> atletas;
    atletas.emplace_back(paises[0] + std::to_string(0), Genero::Femenino, 1620, paises[0], atletas.size());
    std::vector<std::vector<Competencia>> cronograma(3);
    std::vector<Competencia> competencias;
    for (int i = 0; i < 6; i++) {
        atletas[0].entrenarNuevoDeporte(deportes[1], 50);
    }
    for (int i = 0; i < 6; i++) {
        if (i % 2)
            cronograma[i / 2] = {Competencia(deportes[i - 1], Genero::Femenino, atletas),
                                 Competencia(deportes[i], Genero::Femenino, atletas)};
        competencias.emplace_back(deportes[i], Genero::Femenino, atletas);
    }
    JJOO jo = JJOO(2016, atletas, cronograma);

    ASSERT_EQ(2016, jo.anio());
    ASSERT_EQ(atletas, jo.atletas());
    ASSERT_EQ(3, jo.cantDias());
    ASSERT_EQ(1, jo.jornadaActual());
    ASSERT_TRUE(mismos(jo.cronograma(1), cronograma[0]));
    ASSERT_TRUE(mismos(jo.cronograma(2), cronograma[1]));
    ASSERT_TRUE(mismos(jo.cronograma(3), cronograma[2]));
    ASSERT_TRUE(mismos(jo.competencias(), competencias));
}

TEST(jjoo_tests, competencias_al_transcurrir_un_dia) {
    //Test dos paises y una competencia
    std::vector<Atleta> atletas;

    atletas.emplace_back(paises[0] + std::to_string(0), Genero::Masculino, 1620, paises[0], atletas.size());
    atletas.emplace_back(paises[0] + std::to_string(1), Genero::Masculino, 1620, paises[0], atletas.size());

    atletas.emplace_back(paises[1] + std::to_string(0), Genero::Masculino, 1620, paises[1], atletas.size());
    atletas.emplace_back(paises[1] + std::to_string(1), Genero::Masculino, 1620, paises[1], atletas.size());

    atletas[0].entrenarNuevoDeporte(deportes[0], 100);
    atletas[0].entrenarNuevoDeporte(deportes[1], 50);
    atletas[0].entrenarNuevoDeporte(deportes[2], 0);

    atletas[1].entrenarNuevoDeporte(deportes[0], 0);
    atletas[1].entrenarNuevoDeporte(deportes[1], 100);
    atletas[1].entrenarNuevoDeporte(deportes[2], 50);

    atletas[2].entrenarNuevoDeporte(deportes[0], 100);
    atletas[2].entrenarNuevoDeporte(deportes[1], 50);
    atletas[2].entrenarNuevoDeporte(deportes[2], 0);

    atletas[3].entrenarNuevoDeporte(deportes[0], 0);
    atletas[3].entrenarNuevoDeporte(deportes[1], 100);
    atletas[3].entrenarNuevoDeporte(deportes[2], 50);

    std::vector<Atleta> participantes = {atletas[0], atletas[1], atletas[2]};

    Competencia comp = Competencia(deportes[0], Genero::Masculino, participantes);

    JJOO jo = JJOO(2016, atletas, {{comp}});
    JJOO otro_jo = jo;

    ASSERT_TRUE(mismos(jo.competencias(), {comp}));
    ASSERT_TRUE(mismos(jo.atletas(), atletas));

    jo.transcurrirDia();

    ASSERT_TRUE(mismos(jo.atletas(), atletas));
    ASSERT_EQ(2, jo.jornadaActual());
    //ASSERT_TRUE(test::mismos(jo.competenciasFinalizadasConOroEnPodio(), {comp}));
    ASSERT_TRUE(transcurre_correctamente(jo.competencias()[0]));
    ASSERT_TRUE(mismos(jo.dePaseo(), {atletas[3]}));

    //Lo mismo pero finalizando la competencia por fuera

    ASSERT_TRUE(mismos(otro_jo.competencias(), {comp}));
    ASSERT_TRUE(mismos(otro_jo.atletas(), atletas));

    otro_jo._cronograma[0][0].finalizar({0, 2, 1}, {});
    otro_jo.transcurrirDia();
    comp.finalizar({0, 2, 1}, {});

    ASSERT_TRUE(mismos(otro_jo.competencias(), {comp}));
    ASSERT_TRUE(mismos(otro_jo.atletas(), atletas));
    ASSERT_EQ(otro_jo.jornadaActual(), 2);
    ASSERT_TRUE(mismos(otro_jo.competenciasFinalizadasConOroEnPodio(), {comp}));
    if (otro_jo.competenciasFinalizadasConOroEnPodio().size() == 1)
        ASSERT_TRUE(finaliza_correctamente(otro_jo.competenciasFinalizadasConOroEnPodio()[0]));
    ASSERT_TRUE(mismos(otro_jo.dePaseo(), {atletas[3]}));
}

TEST(jjoo_tests, competencias_al_transcurrir_dos_dias) {
    //Test dos paises, cuatro competencias, dos dias
    std::vector<Atleta> atletas;

    atletas.emplace_back(paises[0] + std::to_string(0), Genero::Masculino, 1620, paises[0], atletas.size());
    atletas.emplace_back(paises[0] + std::to_string(1), Genero::Masculino, 1620, paises[0], atletas.size());

    atletas.emplace_back(paises[1] + std::to_string(0), Genero::Masculino, 1620, paises[1], atletas.size());
    atletas.emplace_back(paises[1] + std::to_string(1), Genero::Masculino, 1620, paises[1], atletas.size());

    atletas[0].entrenarNuevoDeporte(deportes[0], 100);
    atletas[0].entrenarNuevoDeporte(deportes[1], 50);
    atletas[0].entrenarNuevoDeporte(deportes[2], 0);
    atletas[0].entrenarNuevoDeporte(deportes[3], 100);

    atletas[1].entrenarNuevoDeporte(deportes[0], 0);
    atletas[1].entrenarNuevoDeporte(deportes[1], 100);
    atletas[1].entrenarNuevoDeporte(deportes[2], 50);
    atletas[1].entrenarNuevoDeporte(deportes[3], 20);

    atletas[2].entrenarNuevoDeporte(deportes[0], 100);
    atletas[2].entrenarNuevoDeporte(deportes[1], 50);
    atletas[2].entrenarNuevoDeporte(deportes[2], 0);

    atletas[3].entrenarNuevoDeporte(deportes[0], 0);
    atletas[3].entrenarNuevoDeporte(deportes[1], 100);
    atletas[3].entrenarNuevoDeporte(deportes[2], 50);
    atletas[3].entrenarNuevoDeporte(deportes[3], 100);

    std::vector<Atleta> participantes_primera = {atletas[0], atletas[1], atletas[2]};
    std::vector<Atleta> participantes_segunda = {atletas[3], atletas[0], atletas[1]};
    std::vector<Atleta> participantes_tercera = {atletas[0], atletas[1], atletas[2], atletas[3]};
    std::vector<Atleta> participantes_cuarta = {atletas[0], atletas[1]};

    Competencia comp_uno_primer_dia = Competencia(deportes[0], Genero::Masculino, participantes_primera);
    Competencia comp_dos_primer_dia = Competencia(deportes[1], Genero::Masculino, participantes_segunda);
    Competencia comp_uno_segundo_dia = Competencia(deportes[2], Genero::Masculino, participantes_tercera);
    Competencia comp_dos_segundo_dia = Competencia(deportes[3], Genero::Masculino, participantes_cuarta);


    JJOO jo = JJOO(2016, atletas, {{comp_uno_primer_dia,  comp_dos_primer_dia},
                                   {comp_uno_segundo_dia, comp_dos_segundo_dia}});

    ASSERT_TRUE(mismos(jo.competencias(),
                       {comp_uno_primer_dia, comp_dos_primer_dia, comp_uno_segundo_dia, comp_dos_segundo_dia}));
    ASSERT_TRUE(mismos(jo.atletas(), atletas));

    comp_uno_primer_dia.finalizar({0, 2, 1}, {{0, true},
                                              {2, true}}); //Como los atletas 0 y 2 tienen dopping positivo, el ganador de la medalla de oro es el atleta 1 con capacidad 0 -> steven!
    comp_dos_primer_dia.finalizar({3, 1, 0}, {{0, false}});

    jo._cronograma[0][0].finalizar({0, 2, 1}, {{0, true},
                                               {2, true}});
    jo._cronograma[0][1].finalizar({3, 1, 0}, {{0, false}});

    //ASSERT_EQ(comp_uno_primer_dia.ranking(), {0,2,1});
    comp_uno_primer_dia.sancionarTramposos();
    //ASSERT_EQ(comp_uno_primer_dia.ranking(), {1});

    jo.transcurrirDia();

    ASSERT_EQ(2, jo.jornadaActual());


    comp_uno_segundo_dia.finalizar({}, {});
    comp_dos_segundo_dia.finalizar({0, 1}, {});
    jo._cronograma[1][0].finalizar({}, {});
    jo._cronograma[1][1].finalizar({0, 1}, {});


    jo.transcurrirDia();


    //ASSERT_EQ(jo.stevenBradbury(), atletas[1]);
    ASSERT_EQ(jo.jornadaActual(), 3);
    ASSERT_TRUE(mismos(jo.competenciasFinalizadasConOroEnPodio(),
                       {comp_uno_primer_dia, comp_dos_primer_dia, comp_dos_segundo_dia}));

    if (jo.competenciasFinalizadasConOroEnPodio().size() == 3) {
        ASSERT_TRUE(finaliza_correctamente(jo.competenciasFinalizadasConOroEnPodio()[2]));
        ASSERT_TRUE(finaliza_correctamente(jo.competenciasFinalizadasConOroEnPodio()[0]));
        ASSERT_TRUE(finaliza_correctamente(jo.competenciasFinalizadasConOroEnPodio()[1]));

    }

    std::vector<int> a = {2, 2, 2};
    std::vector<int> b = {1, 1, 0};
    vector<pair<Pais, vector<int> > > medallero = {std::make_pair(paises[0], a), std::make_pair(paises[1], b)};
    ASSERT_EQ(jo.medallero(), medallero);
}

TEST(jjoo_tests, sequias_olimpicas_y_los_mas_fracasados) {
    //Nota util: Los indices de los paises se corresponden con el indice de los atletas, si el atleta 0 gano una medalla es porque el pais 0 gano una medalla (de nada)
    std::vector<Atleta> atletas;

    atletas.emplace_back(paises[0] + std::to_string(0), Genero::Femenino, 1620, paises[0], atletas.size());
    atletas.emplace_back(paises[1] + std::to_string(0), Genero::Femenino, 1620, paises[1], atletas.size());
    atletas.emplace_back(paises[2] + std::to_string(0), Genero::Femenino, 1620, paises[2], atletas.size());

    auto atletas_para_el_juego = atletas;
    atletas_para_el_juego.emplace_back(paises[0] + std::to_string(0), Genero::Femenino, 1620, paises[2],
                                       atletas.size()); //Este atleta deberia estar de paseo

    std::vector<Competencia> competencias;
    std::vector<std::vector<Competencia>> cronograma;

    for (size_t i = 0; i < 10; i++) {
        atletas[0].entrenarNuevoDeporte(deportes[i], 100);
        atletas[1].entrenarNuevoDeporte(deportes[i], 100);
        atletas[2].entrenarNuevoDeporte(deportes[i], 100);
    }
    for (size_t i = 0; i < 10; i++) {
        competencias.emplace_back(deportes[i], Genero::Femenino, atletas);
        cronograma.push_back({competencias.back()});
    }

    JJOO jo = JJOO(1920, atletas_para_el_juego, cronograma);

    //Sequia: 0 - 0 - 0
    jo._cronograma[0][0].finalizar({0}, {});
    jo.transcurrirDia();//Sequia: 1 - 2 - 2
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[1], paises[2]}));

    jo._cronograma[1][0].finalizar({0}, {});
    jo.transcurrirDia();//Sequia: 1 - 3 - 3
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[1], paises[2]}));

    jo._cronograma[2][0].finalizar({1}, {});
    jo.transcurrirDia();//Sequia: 2 - 1 - 4
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[2]}));
    jo._cronograma[3][0].finalizar({1}, {});
    jo.transcurrirDia();//Sequia: 3 - 1 - 5
    jo._cronograma[4][0].finalizar({1}, {});
    jo.transcurrirDia();//Sequia: 4 - 1 - 6
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[2]}));

    jo._cronograma[5][0].finalizar({2}, {});
    jo.transcurrirDia();//Sequia: 5 - 2 - 1
    jo._cronograma[6][0].finalizar({1}, {});
    jo.transcurrirDia();//Sequia: 6 - 1 - 2
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[0], paises[2]}));

    jo._cronograma[7][0].finalizar({0}, {});
    jo.transcurrirDia();//Sequia: 1 - 2 - 3
    jo._cronograma[8][0].finalizar({1}, {});
    jo.transcurrirDia();//Sequia: 2 - 1 - 4
    jo._cronograma[9][0].finalizar({0}, {});
    jo.transcurrirDia();//Sequia: 1 - 2 - 5
    ASSERT_TRUE(mismos(jo.sequiaOlimpica(), {paises[0], paises[2]}));

    ASSERT_TRUE(mismos(jo.dePaseo(), {atletas[3]}));
}

TEST(jjoo_tests, hay_un_patron) {
    //Nota util:    Los indices de los paises se corresponden con el indice de los atletas, si el atleta 0 gano una medalla es porque el pais 0 gano una medalla (de nada)
    //              Por otro lado los indices de los deportes se corresponden con los indices de las fechas

    std::vector<Atleta> atletas;

    atletas.emplace_back(paises[0] + std::to_string(0), Genero::Femenino, 1620, paises[0], atletas.size());
    atletas.emplace_back(paises[1] + std::to_string(0), Genero::Femenino, 1620, paises[1], atletas.size());
    atletas.emplace_back(paises[2] + std::to_string(0), Genero::Femenino, 1620, paises[2], atletas.size());

    std::vector<Competencia> competencias;
    std::vector<std::vector<Competencia>> cronograma;

    for (size_t i = 0; i < deportes.size(); i++) {
        atletas[0].entrenarNuevoDeporte(deportes[i], 100);
        atletas[1].entrenarNuevoDeporte(deportes[i], 100);
        atletas[2].entrenarNuevoDeporte(deportes[i], 100);

        competencias.emplace_back(deportes[i], Genero::Femenino, atletas);
        cronograma.push_back({competencias.back()});
    }

    JJOO jo = JJOO(1920, atletas, cronograma);

    jo._cronograma[0][0].finalizar({0}, {});
    jo.transcurrirDia();
    jo._cronograma[1][0].finalizar({1}, {});
    jo.transcurrirDia();
    jo._cronograma[2][0].finalizar({2}, {});
    jo.transcurrirDia();
    ASSERT_TRUE(jo.uyOrdenadoAsiHayUnPatron());
    jo._cronograma[3][0].finalizar({0}, {});
    jo.transcurrirDia();
    jo._cronograma[4][0].finalizar({1}, {});
    jo.transcurrirDia();
    ASSERT_TRUE(jo.uyOrdenadoAsiHayUnPatron());
    jo._cronograma[5][0].finalizar({2}, {});
    jo.transcurrirDia();
    jo._cronograma[6][0].finalizar({0}, {});
    jo.transcurrirDia();
    jo._cronograma[7][0].finalizar({1}, {});
    jo.transcurrirDia();
    jo._cronograma[8][0].finalizar({2}, {});
    jo.transcurrirDia();
    jo._cronograma[9][0].finalizar({0}, {});
    jo.transcurrirDia();
    ASSERT_TRUE(jo.uyOrdenadoAsiHayUnPatron());
    vector<pair<Pais, vector<int> > > medallero = {std::make_pair(paises[0], (std::vector<int>) {5, 0, 0}),
                                                   std::make_pair(paises[1], (std::vector<int>) {3, 0, 0}),
                                                   std::make_pair(paises[2], (std::vector<int>) {3, 0, 0})};
    ASSERT_TRUE(jo.medallero() == medallero);

    //Boicot a Argentina en el oro que gano en la cuarta fecha de los juegos
    jo.boicotPorDisciplina(std::make_pair(deportes[3], Genero::Masculino), paises[0]);

    medallero = {std::make_pair(paises[0], (std::vector<int>) {3, 0, 0}),
                 std::make_pair(paises[1], (std::vector<int>) {3, 0, 0}),
                 std::make_pair(paises[2], (std::vector<int>) {3, 0, 0})};


    ASSERT_TRUE(jo.medallero() == medallero);
    ASSERT_TRUE(
            jo.uyOrdenadoAsiHayUnPatron()); //En la cuarta fecha nadie gano nada y lexicograficamente Argentina deberia quedar primera
}

TEST(jjoo_tests, liu_song) {
    std::vector<Atleta> atletas;
    atletas.emplace_back("liu song", Genero::Masculino, 1620, paises[0], atletas.size());
    atletas[0].entrenarNuevoDeporte(deportes[0], 50);
    Competencia comp = Competencia(deportes[0], Genero::Masculino, atletas);

    JJOO jo = JJOO(2016, atletas, {{comp}});

    jo.cronograma(1)[0].finalizar({0}, {});

    ASSERT_TRUE(mismos(jo.medallero(), {{paises[0], {1, 0, 0}}}));

    jo.liuSong(atletas[0], paises[1]);

    ASSERT_TRUE(mismos(jo.medallero(), {{paises[1], {1, 0, 0}}}));
}
