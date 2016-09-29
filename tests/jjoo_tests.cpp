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
