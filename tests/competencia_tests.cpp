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
