#include<iostream>
#include<sstream>
#include "../include/auxiliares.h"

/*using namespace std;

template <class T>
inline void mostrarSecuencia(std::ostream & os, const Secuencia<T> & s)
{
  os << "[";
  for(unsigned int i=0; i<s.size(); i++)
  {
    os << s[i];

    if(i < s.size()-1)
      os << ",";
  }
  os << "]";
}

template <class T>
inline bool mismos(const Secuencia<T> & v1, const Secuencia<T> & v2)
{
  if(v1.size() != v2.size())
    return false;

  for(unsigned int i=0; i<v1.size(); i++)
    if(cuenta(v1, v1[i]) != cuenta(v2, v1[i]))
      return false;

  return true;
}

template <class T>
inline int cuenta(const Secuencia<T> & v, T elemento)
{
  int contador = 0;
  for(unsigned int i=0; i<v.size(); i++)
    if(v[i] == elemento)
      contador++;
  return contador;
}

template <class T>
inline void ordenar(Secuencia<T> & vs)
{
  for(unsigned int i=0; i<vs.size(); i++)
  {
    for(unsigned int j=0; j<vs.size()-1; j++)
    {
      if(vs[j] < vs[j+1])
        swap(vs[j], vs[j+1]);
    }
  }
}
*/
inline string trim(string& str)
{
  size_t first = str.find_first_not_of(' ');
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last-first+1));
}

inline vector<string> splitVector(string str, char delimiter)
{
  vector<string> result;
  stringstream ss(str);
  string tok;
  while(getline(ss, tok, delimiter))
  {
    result.push_back(trim(tok));
  }
  return result;
}
