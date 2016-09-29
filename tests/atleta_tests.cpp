#include "gtest/gtest.h"

#include "../include/atleta.h"

TEST(atleta_tests, observadores_de_atleta_sin_deportes) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    //Tests observadores del tipo Atleta
    ASSERT_EQ("Nole", atleta.nombre());
    ASSERT_EQ(Genero::Masculino, atleta.genero());
    ASSERT_EQ(1983, atleta.anioNacimiento());
    ASSERT_EQ("Serbia", atleta.nacionalidad());
    ASSERT_EQ(5, atleta.ciaNumber());
}
