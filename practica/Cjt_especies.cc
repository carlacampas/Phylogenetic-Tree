/** @file Cjt_especies.cc
    @brief Codí de la clase Cjt_especies (conjunt d'especies)
*/

#include "Cjt_especies.hh"

//public
//constructora
Cjt_especies::Cjt_especies(){}

//destructora
Cjt_especies::~Cjt_especies(){}

//modificadoras
void Cjt_especies::elimina_especie (const string& idn){
  //Borrem l'especie del mapa de especies, i borrem el mapa associat amb l'especie del mapa de distancies
  distancies.erase(idn);
  mesp.erase(idn);
  map <string, Especie>::const_iterator it = mesp.begin();
  //Borrem la distancia de tots els identtificadors més petits que "idn", ja que nomes guardem meitat de la taula
  while (it != mesp.end() and it -> first < idn){
    distancies[it -> first].erase(idn);
    ++it;
  }
}

void Cjt_especies::afegir_especie (Especie e){
  string idn = e.consultar_idn();
  //Creem un mapa de distancies per la nova especie, ens estalviem la busqueda repetitiva
  map <string, double> dists;
  for (map <string, Especie>::const_iterator it = mesp.begin(); it != mesp.end();++it){
    //basat en el seu index mirem dins de quin submapa de distancies anira, nomes guardem meitat de la taula
    double distn = e.distancia(it->second);
    if ((it -> first) < idn) distancies[it->first][idn] = distn;
    else if ((it -> first) > idn) dists[it->first] = distn;
  }
  //afegim la nova especie a distancies i al mapa de clusters
  distancies[idn] = dists;
  mesp[e.consultar_idn()] = e;
}

//consultoras
bool Cjt_especies::search (const string& idn) const{
  map <string, Especie>::const_iterator it = mesp.find (idn);
  return it != mesp.end();
}

Especie Cjt_especies::consultar_especie (const string& idn) const{
  map <string, Especie>::const_iterator it = mesp.find (idn);
  return (it -> second);
}

double Cjt_especies::consultar_distancia (string idn, string idn1){
  /*Ja que només guardem meitat de la taula mirem per els identificadors quin sera mes petit,
  i per tant qui quardara les dades, si els dos identificadors son iguals retornara 0 ja que sera
  la mateixa especie*/
  if (idn < idn1) return distancies[idn][idn1];
  else if (idn > idn1) return distancies[idn1][idn];
  return 0;
}

void Cjt_especies::principi(){
  it_clust = mesp.begin();
}

string Cjt_especies::proper(){
  string id = it_clust -> first;
  ++it_clust;
  return id;
}

bool Cjt_especies::final() const{
  return it_clust == mesp.end();
}

//lectura i escriputra
void Cjt_especies::llegir(){
  int n;
  cin >> n;
  //Borrem l'informacio previament guardada al parametre implicit
  mesp.clear();
  distancies.clear();
  for (int i=1; i<=n;i++){
    Especie e;
    e.llegir();
    //llegim una especie i l'afegim utilitzan el metode afegir_especie
    afegir_especie(e);
  }
}

void Cjt_especies::escriure() const{
  for (map <string, Especie>::const_iterator it = mesp.begin(); it != mesp.end();it++){
    (it -> second).escriure();
  }
}

void Cjt_especies::imprimir_taula_distancies() const{
  //Començem un iterador al principi del mapa de distancies, i anem iteran els seus submapes i imprimin la informacio
  for (map <string, map <string, double> >::const_iterator it = distancies.begin(); it != distancies.end(); it++){
    cout << it -> first << ":";
    for (map <string, double>::const_iterator it1 = (it->second).begin(); it1 != (it -> second).end(); it1++){
      cout << " " << it1 -> first << " (" << it1 -> second << ")";
    }
    cout << endl;
  }
}
