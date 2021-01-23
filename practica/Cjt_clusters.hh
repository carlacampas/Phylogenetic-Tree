/** @file Cjt_clusters.hh
    @brief Conte l'especifiacio de la classe Cjt_clusters
*/
#ifndef CJT_CLUST_HH
#define CJT_CLUST_HH

#include "Cjt_especies.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <map>
#include "BinTree.hh"
#include <iostream>
#endif

/** @brief Crea l'especificació del clúster com un BinTree amb distancies entre les especies d'un mateix clúster*/
typedef BinTree < pair <string, double> > Cluster;

/** @class Cjt_clusters
    @brief Representa l'informació i les operacions associades a un conjunt d'clùsters.

    Aquesta classe controla totes les operacions del conjunt de clústers. Veiem que les "grans" operacions dins d'aquest programa són inicialitza clúster i pas WPGMA, que són els únics mètodes que modifiquen el conjunt.
    Annexament, imprimir_arbre_filogenetic utilitza el pas WPGMA per crear l'arbre mencionat al programa principal.
*/
class Cjt_clusters {

  //Descripció: Conté el conjunt de clusters i les seves distancies associades

private:
  /** @brief Clusters del conjunt */
  map <string, Cluster> mclu;
  /** @brief Distancies entre els clusters, trobat amb els dos identificador corresponents */
  map <string, map <string, double> > distancies;

  /** @brief Calcula la distancia minima entre els clusters del mapa
      \pre Els iteradors estan iniciats on al valor inicial del mapa i el següen valor a it_m, it1_m i it_d, it1_d corresponenment
      \post retorna la distancia minima i  it_m, it1_m, it_d, it1_d queden inicialitzats als clusters de menor distancia
  */
  double recalcular_min (map <string, Cluster>::iterator& it_m, map <string, Cluster>::iterator& it1_m, map<string, map <string, double> >::iterator& it_d, map <string, map <string, double> >::iterator& it1_d);

public:
  //constructoras
  /** @brief Consturctora del conjunt d'especies, crea un conjunt buit
      \pre <em> Cert </em>
      \post S'ha inicialitzat el paràmetre implícit amb clusters basat en les espècies de c
  */
  Cjt_clusters ();

  /** @brief Constructora del conjunt d'especies crea un conjunt basat en un conjunt d'espècies
      \pre "c" conjunt d'espècies no buit
      \post S'ha inicialitzat el paràmetre implícit amb clusters basat en les espècies de c
  */
  Cjt_clusters (Cjt_especies c);

  //destructora
  /** @brief Destructora de la clase Cjt_clusters
      \pre <em> Cert </em>
      \post El paràmetre implícit ja no existeix
  */
  ~Cjt_clusters();

  //modificadora
  /** @brief S'executa un pas WPGMA (Weighted Pair Group Arithmetic Mean), s'ajunten els dos clusters del paràmetre implícit amb menor distancia (més "similars")
      \pre El paràmetre implícit no esta vuit
      \post S'ha implementat un pas WPGMA i s'han unit dos clusters basat en les seves distancies
  */
  void pas_wpgma ();

  /** @brief Consulta el tamany del mapa
      \pre <em> Cert </em>
      \post S'ha retornat el tamany del parametre implicit
  */
  int tamany() const;

  //consultoras
  /** @brief Es busca un clùster amb l'identificador "idn"
      \pre "idn" no esta vuit
      \post S'ha retornat false si un clùster del paràmetre implícit conte aquest identificador, true altrament
  */
  bool buscar_cluster (const string& idn) const;

  /** @brief Retorna el clúster associat amb l'identificador idn
      \pre "idn" esta dinst del conjunt de clusters
      \post S'ha retornat el clùster associat amb "idn"
  */
  Cluster consultar_cluster(const string& idn) const;

  //llegir i escriure
  /** @brief S'escriu la taula de distancies
      \pre <em> Cert </em>
      \post S'ha impres per el canal de sortida la taula de distancies
  */
  void imprimir_taula_distancies() const;

  /** @brief Es crea i s'escriu el arbre filogenetic que es crea del conjunt
      \pre <em> Cert </em>
      \post S'ha creat un arbre filogenetic i s'ha impres
  */
  void imprimir_arbre_filogenetic();

  /** @brief S'escriu el clúster amb identificador general "idn"
      \pre <em> Cert </em>
      \post S'ha impres el clúster per el canal de sortida amb el identificador "idn" donat
  */
  void escriure_cluster(const Cluster& c) const;
};
#endif
