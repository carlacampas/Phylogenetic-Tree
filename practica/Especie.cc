/** @file Especie.cc
    @brief Codí de la clase Especie
*/

#include "Especie.hh"

int Especie::k = 0;

Especie::Especie (){}

Especie::~Especie(){}

void Especie::produir_kmer (){
  //Basat en una k predefinida, es crea els kmers de llongitud k
  int n = gen.size()-k+1;
  for (int i=0; i<n;i++) kmer[gen.substr(i, k)]++;
}

double Especie::distancia (Especie e1){
  int num = 0, den = 0;
  //Començem dos iteradors apuntan a les especies corresponents (la del parametre implicit i "e1")
  map <string, int>::const_iterator it = kmer.begin();
  map <string, int>::const_iterator it2 = e1.kmer.begin();

  while (it != kmer.end() and it2 != e1.kmer.end()){
    //Si els kmers a una certa posicio son iguals sumem el numero corresponent al numerador i denominador
    if (it -> first == it2 -> first){
      num += min (it->second, it2 -> second);
      den += max (it->second, it2->second);
      ++it;
      ++it2;
    }
    //Si son differents mirem quin es més gran lexicograficament, sumem el kmer al denominador i avançem el iterador
    else if (it -> first > it2 -> first){
        den += it2 -> second;
        ++it2;
    }
    else{
        den += it -> second;
        ++it;
    }
  }

  //Com hi ha la possibilitat de que un dels iteradors no haigi arribat al final, sumem els kmers restants al denominador
  while (it != kmer.end()){
      den += it -> second;
      ++it;
  }
  while (it2 != e1.kmer.end()){
      den += it2 -> second;
      ++it2;
  }

  double dist = (double)num/den;
  return (1-dist)*100;
}

void Especie::set_k(int k_set){
  Especie::k = k_set;
}

//consultoras
string Especie::consultar_gen () const{
  return gen;
}

string Especie::consultar_idn () const{
  return idn;
}

void Especie::llegir(){
  cin >> idn >> gen;
  produir_kmer();
}

void Especie::escriure() const{
  cout << idn << ' ' << gen << endl;
}
