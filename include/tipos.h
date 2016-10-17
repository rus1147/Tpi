#ifndef __TIPOS__
#define __TIPOS__

#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

typedef string Deporte;
typedef string Pais;
enum Genero {
    Femenino,
    Masculino
};
typedef pair<Deporte, Genero> Categoria;

std::ostream &operator<<(std::ostream &os, const Genero &g);
Genero generostring(const string &s);
#endif /*__TIPOS__*/
