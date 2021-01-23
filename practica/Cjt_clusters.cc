/** @file Cjt_clusters.cc
    @brief Codí de la clase Cjt_clusters (conjunt del clusters)
*/

#include "Cjt_clusters.hh"

//private
double Cjt_clusters::recalcular_min (map <string, Cluster>::iterator& cit, map <string, Cluster>::iterator& cit1, map<string, map <string, double> >::iterator& dit, map <string, map <string, double> >::iterator& dit1){
  //Començem dos iteradors per recorre el mapa de distancies i clusters simultaneament
  map <string, map <string, double> >::iterator it_d = distancies.begin();
  map <string, Cluster>::iterator it_m = mclu.begin();
  double min = 0;
  //Iniciem in a false, d'aquesta manera a la primera iteracio ens entrara a la condicio, i iniciarem els valors al primer valor de la distancia
  bool in = false;
  while (it_m != mclu.end()){
    //Creem dos mapes mes per recorre les distancies posteriors als mapes it_m i it_d
    map <string, Cluster>::iterator it1_m = it_m; it1_m++;
    map <string, map <string, double> >::iterator it1_d = it_d; it1_d++;
    while (it1_m != mclu.end()){
      /*si la distancia es menor canviem el iteradors, en el cas que siguin iguals no ho canviem ja que
      els mapes sempre estan ordenats lexicograficament, aixi no ens fa falta comprovar les igualtats*/
      if (not in or (it_d -> second)[it1_m -> first] < min){
        if (not in) in = true;
        cit = it_m; cit1 = it1_m;
        dit = it_d; dit1 = it1_d;
        min = (it_d -> second)[it1_m -> first];
      }
      ++it1_m; ++it1_d;
    }
    ++it_m; ++it_d;
  }
  return min;
}

//public
Cjt_clusters::Cjt_clusters (){}

Cjt_clusters::Cjt_clusters (Cjt_especies c){
  //Borrem el parametre implicit per poder començar un nou conjunt de clusteres
  mclu.clear();
  distancies.clear();
  //Iniciem el iterador de la clase de clusters al inici del mapa
  c.principi();
  while (not c.final()){
    string id = c.proper();
    //Creem un nou mapa per les distancies del nou cluster
    map <string, Cluster>:: const_iterator it = mclu.begin();
    while (it != mclu.end()){
      //Afegim les distancies on calguin, mantenin la taula a la meitat de les dades ja que es simetrica
      distancies[it -> first][id] = c.consultar_distancia (id, it -> first);
      ++it;
    }
    distancies[id];
    mclu[id] = Cluster (pair <string, double> (id, 0));
  }
}

Cjt_clusters::~Cjt_clusters(){}

void Cjt_clusters::pas_wpgma(){
  map <string, Cluster>::iterator cit, cit1;
  map <string, map <string, double> >::iterator dit, dit1;
  //it, it1 apunten als clusters amb distancia minima, it_d i it1_d apunten als mapes de distancies menors
  double min = recalcular_min(cit, cit1, dit, dit1);

  string nou_id = cit -> first + cit1 -> first;
  Cluster c = Cluster(pair <string, double>(nou_id, min/2), cit -> second, cit1 -> second);
  //Començem un mapa per les distancies al nou cluster
  map <string, double> dists;

  //Iniciem un iterador de la taula de distancies per fer el recorregut de wpgma
  map <string, map <string, double> >::iterator it = distancies.begin();

  /*Per la primera part buscarem a cada iteracio fins el primer identificador les distancies,
  treurem les distancies als clusters revisats corresponents amb els identificadors minims */
  while (it != dit){
    map <string, double>::iterator it1 = (it -> second).begin();
    double d1 = 0;
    while (it1 -> first != dit1 -> first){
      if (it1 -> first == dit -> first){
        d1 = it1 -> second;
        it1 = (it -> second).erase(it1);
      }
      else ++it1;
    }
    //Afegim la nova distancia a la taula de distancies corresponent
    if (it -> first > nou_id) dists[it -> first] = (d1 + it1 -> second)/2;
    else (it -> second)[nou_id] = (d1 + it1 -> second)/2;
    (it -> second).erase(it1);
    ++it;
  }

  /*Començem un iterador al mapa de distancies del primer mapa de distancies
  per aixi simplificar trobar les distancies corresponents ja que tindrem les distancies a ma*/
  map <string, double>::iterator fit = (dit -> second).begin();
  ++it;

  /* Començem un segon loop per totes aquelles distancies entre dit < it < dit1
  i busquem les distancies al nou cluster, aprofitem per borrar les distancies dels clusters de distancia minima */
  while (it != dit1){
    assert (it -> first == fit -> first);
    map <string, double>::iterator it1 = (it -> second).begin();
    while (it1 -> first != dit1 -> first) ++it1;

    //Afegim la nova distancia a la taula de distancies corresponent
    if (it -> first > nou_id) dists[it -> first] = (it1 -> second + fit -> second)/2;
    else (it -> second)[nou_id] = (it1 -> second + fit -> second)/2;
    (it -> second).erase(it1);

    ++it;
    ++fit;
  }

  // Començem un iterador de les distancies de clusters al segon cluster, per tindre les distancies del segon cluster a ma
  map <string, double>::iterator fit1 = (dit1 -> second).begin();
  ++it;
  ++fit;

  while (it != distancies.end()){
    assert (it -> first == fit -> first);
    assert (it -> first == fit1 -> first);

    //Afegim la nova distancia a la taula de distancies corresponent
    if (it -> first > nou_id) dists[it -> first] = (fit1 -> second + fit -> second)/2;
    else (it -> second)[nou_id] = (fit1 -> second + fit -> second)/2;

    ++it;
    ++fit;
    ++fit1;
  }

  //Borrem del mapa de distancies i clusters els iteradors inicialitzats a els clusters de menor distancia
  mclu.erase(cit);
  mclu.erase(cit1);
  distancies.erase(dit);
  distancies.erase(dit1);

  //Afegim novament el cluster al mapa de clusters i les distancies trobades a "dists" al mapa de distancies
  mclu[nou_id] = c;
  distancies[nou_id] = dists;
}

int Cjt_clusters::tamany() const{
  return mclu.size();
}

bool Cjt_clusters::buscar_cluster (const string& idn) const {
  map <string, Cluster>::const_iterator it = mclu.find(idn);
  return it != mclu.end();
}

Cluster Cjt_clusters::consultar_cluster(const string& idn) const{
  map <string, Cluster>::const_iterator it = mclu.find(idn);
  return it -> second;
}

void Cjt_clusters::imprimir_taula_distancies() const {
  //Imprimim la taula de distancies de la mateixa manera que
  map <string, map <string, double> >::const_iterator it = distancies.begin();
  while (it != distancies.end()){
    cout << it -> first << ":";
    map <string, double>::const_iterator it1 = (it->second).begin();
    while (it1 != (it -> second).end()){
      cout << " " << it1 -> first << " (" << it1 -> second << ")";
      it1++;
    }
    cout << endl;
    ++it;
  }
}

void Cjt_clusters::imprimir_arbre_filogenetic(){
  while (mclu.size() > 1){
    pas_wpgma();
  }
  escriure_cluster (mclu.begin() -> second);
}

void Cjt_clusters::escriure_cluster(const Cluster& c) const{
  if (c.empty()) return;
  cout << "[";
  if (c.left().empty() and c.right().empty()) cout << c.value().first;
  else cout << '(' << c.value().first << ", " << c.value().second << ") ";
  escriure_cluster(c.left());
  escriure_cluster(c.right());
  cout << ']';
}
