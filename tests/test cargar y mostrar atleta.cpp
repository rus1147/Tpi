#include <fstream>
#include <algorithm>
//#include <atleta.h>
#include "gtest/gtest.h"
#include "auxiliares_tests.h"

/*
TEST(atleta_nuevo_deporte, guardar_y_cargar_funcionan_ok) {
//|Liu Song| |Masculino| 1972 |China| 123 [(|Tenis de Mesa|, 90)]

Atleta a1("Nole", Genero::Masculino, 1983, "Serbia", 5);
atleta.entrenarNuevoDeporte(deportes[0], 7);

char fname[] = "test_atleta.txt";
std::ofstream out;
out.open(fname);
a1.guardar(out);
Atleta a2;
out.close();
std::ifstream in(fname);
a2.cargar(in);
in.close();

EXPECT_EQ(a2, a1);
}

TEST(test_drone_lo_basico, guardar_y_cargar_trayectoria_funciona_ok) {
Drone d1(1, algunos_productos());

char fname[] = "test_drone.txt";
std::ofstream out;
out.open(fname);
d1.moverA({1, 3});
d1.moverA({2, 3});
d1.moverA({3, 3});
d1.guardar(out);
Drone d2;
out.close();
std::ifstream in(fname);
d2.cargar(in);
in.close();

EXPECT_EQ(d2, d1);
}

 * /