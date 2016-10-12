#include "gtest/gtest.h"

#include "auxiliares_tests.h"

TEST(atleta_tests, observadores_de_atleta_solo_tenis) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    //Tests observadores del tipo Atleta
    ASSERT_EQ("Nole", atleta.nombre());
    ASSERT_EQ(Genero::Masculino, atleta.genero());
    ASSERT_EQ(1983, atleta.anioNacimiento());
    ASSERT_EQ("Serbia", atleta.nacionalidad());
    ASSERT_EQ(5, atleta.ciaNumber());
    vector<Deporte> deportesDeNole(1, "Tenis");
    ASSERT_EQ(deportesDeNole, atleta.deportes());
}

TEST(atleta_tests, observador_deportes) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    atleta.entrenarNuevoDeporte(deportes[0], 7);
    atleta.entrenarNuevoDeporte(deportes[1], 90);
    atleta.entrenarNuevoDeporte(deportes[2], 99);

    std::vector<Deporte> los_deportes_del_atleta = {deportes[0], deportes[1], deportes[2], deportes[12]};

    ASSERT_EQ(los_deportes_del_atleta.size(), atleta.deportes().size());
    ASSERT_TRUE(atleta.deportes() == los_deportes_del_atleta);

}

TEST(atleta_tests, observador_capacidad) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    atleta.entrenarNuevoDeporte(deportes[0], 7);
    atleta.entrenarNuevoDeporte(deportes[1], 90);
    atleta.entrenarNuevoDeporte(deportes[2], 99);

    ASSERT_EQ(7, atleta.capacidad(deportes[0]));
    ASSERT_EQ(90, atleta.capacidad(deportes[1]));
    ASSERT_EQ(99, atleta.capacidad(deportes[2]));

}

TEST(atleta_tests, igualdad_de_atleta_que_solo_practica_tennis) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_atleta_igual("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_atleta_distinto("Nole", Genero::Femenino, 1983, "Serbia", 5);

    ASSERT_EQ(atleta, otro_atleta_igual);
    ASSERT_FALSE(atleta == otro_atleta_distinto);
}

TEST(atleta_tests, igualdad_de_atleta_con_deportes) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_atleta_igual("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_atleta_distinto("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_segundo_atleta_distinto("Nole", Genero::Masculino, 1983, "Serbia", 5);

    //atleta entrena deportes
    atleta.entrenarNuevoDeporte(deportes[3], 50);
    atleta.entrenarNuevoDeporte(deportes[1], 20);
    atleta.entrenarNuevoDeporte(deportes[8], 100);
    atleta.entrenarNuevoDeporte(deportes[5], 80);

    //otro_atleta_igual entrena los mismos deportes
    otro_atleta_igual.entrenarNuevoDeporte(deportes[3], 50);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[1], 20);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[8], 100);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[5], 80);

    //otro_segundo_atleta_distinto entrena los mismos deportes, pero solo dos
    otro_atleta_distinto.entrenarNuevoDeporte(deportes[3], 50);
    otro_atleta_distinto.entrenarNuevoDeporte(deportes[1], 20);

    //otro_atleta_distinto entrena los mismos deportes con distintas capacidades
    otro_segundo_atleta_distinto.entrenarNuevoDeporte(deportes[3], 51);
    otro_segundo_atleta_distinto.entrenarNuevoDeporte(deportes[1], 21);
    otro_segundo_atleta_distinto.entrenarNuevoDeporte(deportes[8], 100);
    otro_segundo_atleta_distinto.entrenarNuevoDeporte(deportes[5], 80);

    ASSERT_EQ(atleta, otro_atleta_igual);
    ASSERT_FALSE(atleta == otro_atleta_distinto);
    ASSERT_FALSE(atleta == otro_segundo_atleta_distinto);
}

TEST(atleta_tests, observador_capacidad_reentrenando_deportes) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    atleta.entrenarNuevoDeporte(deportes[0], 7);
    atleta.entrenarNuevoDeporte(deportes[1], 90);
    atleta.entrenarNuevoDeporte(deportes[2], 99);

    //Re-entrena los deportes
    atleta.entrenarNuevoDeporte(deportes[2], 55);
    atleta.entrenarNuevoDeporte(deportes[0], 11);
    atleta.entrenarNuevoDeporte(deportes[1], 9);

    ASSERT_EQ(11, atleta.capacidad(deportes[0]));
    ASSERT_EQ(9, atleta.capacidad(deportes[1]));
    ASSERT_EQ(55, atleta.capacidad(deportes[2]));
}

TEST(atleta_tests, igualdad_atleta_luego_de_agregar_y_reentrenar_deportes) {
    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);
    Atleta otro_atleta_igual("Nole", Genero::Masculino, 1983, "Serbia", 5);

    atleta.entrenarNuevoDeporte(deportes[0], 7);
    atleta.entrenarNuevoDeporte(deportes[1], 90);
    atleta.entrenarNuevoDeporte(deportes[2], 99);

    ASSERT_FALSE(atleta == otro_atleta_igual);
    ASSERT_FALSE(otro_atleta_igual == atleta);

    otro_atleta_igual.entrenarNuevoDeporte(deportes[2], 99);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[1], 90);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[0], 7);

    ASSERT_TRUE(atleta == otro_atleta_igual);

    otro_atleta_igual.entrenarNuevoDeporte(deportes[2], 99);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[1], 91);
    otro_atleta_igual.entrenarNuevoDeporte(deportes[0], 7);

    ASSERT_FALSE(atleta == otro_atleta_igual);
}
