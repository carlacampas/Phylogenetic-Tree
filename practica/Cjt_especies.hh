/** @file Cjt_especies.hh
    @brief Especificació de la clase Cjt_especies
*/
#ifndef CJT_ESP_HH
#define CJT_ESP_HH

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
using namespace std;
#endif

/** @class Cjt_especies
    @brief Representa l'informació i les operacions associades a un conjunt d'especies.

    Aquí trobem l'especificació del conjunt d'espècies tractat al programa principal. Dins d'aquest podem manipular les espècies que conte (afegir i esborrar), però també creem una taula de distàncies (implementada com un mapa)
    per saber quines espècies són més similars. Aquesta classe fa servir la classe "Espècie" com ajut a la seva implantació i posteriorment serveix com una plantilla per la implementació del conjunt de clústers.
*/
class Cjt_especies{

    //Descripció: Conté el conjunt d'especies, el conjunt de les seves distancies i un iterador per alimentar les distancies a la clase de clusters

private:
  /** @brief Especies del conjunt*/
  map <string, Especie> mesp;
  /** @brief Distancies entre els especies, trobat amb els dos identificador corresponents */
  map <string, map <string, double> > distancies;

  /** @brief Crea un iterador per pasar les especies a la clase de cluster controlat per els metodes principi, proper i final*/
  map <string, Especie>::const_iterator it_clust;

public:
  //constructoras

  /** @brief Constructora de la classe Cjt_espècies
      \pre <em> cert </em>
      \post s'ha creat un conjunt d'espècies buit
  */
  Cjt_especies();

  //destructora
  /** @brief Destructora de la classe cjt_especies
      \pre <em> Cert </em>
      \post El paràmetre implícit ja no existeix
  */
  ~Cjt_especies();

  //modificadoras
  /** @brief Elimina l'espècie basat en la posició del vector
      \pre 0 <= i < nesp
      \post S'ha eliminat l'espècie corresponent a i del paràmetre implícit
  */
  void elimina_especie (const string& idn);

  /** @brief S'afegeix una espècie al conjunt d'espècies en ordre lexografic
      \pre Espècie "e" no esta dintre del paràmetre implícit
      \post S'ha afegit "e" dins del paràmetre implícit
  */
  void afegir_especie (Especie e);

  //consultoras
  /** @brief Busqueda de una especie dins del conjunt
      \pre "idn" no esta buit
      \post S'ha retornat true si l'idn es troba dins del conjunt i false altrament
  */
  bool search (const string& idn) const;

  /** @brief Consultar una espècie del conjunt d'espècie
      \pre "idn" esta dins del conjunt
      \post Retorna l'espècie del parametre implìcit corresponent al indentificador
  */
  Especie consultar_especie (const string& idn) const;

  /** @brief Consulta la distancia de dos especies
      \pre "e1" i "e2" estan dintre del parametre implicit
      \post s'ha retornat la distancia entre les dos especies del parametre implicit
  */
  double consultar_distancia (string idn, const string idn1);

  /** @brief Inicia iterador per fer la transferencia d'especies al conjunt de clusters
      \pre <em> Cert </em>
      \post S'ha iniciat el iterador "it_clust" al principi del conjunt d'especies
  */
  void principi();

  /** @brief Retorna l'especie apuntada per "it_clusts"
      \pre <em> Cert </em>
      \post Ha retornat l'identificador de la especie al que apunta "it_clusts" i l'augmenta
  */
  string proper();

  /** @brief Mira si it_clusts ha arribat al final del parametre implicit
      \pre <em> Cert </em>
      \post S'ha retornat true si el iterador it_clusts ha arribat al final del parametre implicit
  */
  bool final() const;

  //lectura i escriputra
  /** @brief Es llegix un conjunt d'espècies
      \pre Hi ha informacio d'espècies esperant al canal d'entrada
      \post S'ha llegit el conjunt d'espècies al paràmetre implícit
  */
  void llegir ();

  /** @brief Escriu el conjunt d'conjunt d'espècies
      \pre <em> Cert </em>
      \post S'ha impres l'informacio del paràmetre implícit pel canal de sortida
  */
  void escriure () const;

  /** @brief S'imprimeix la taula de distancies
      \pre <em> Cert </em>
      \post S'ha impre la taula de distancies pel canal de sortida
  */
  void imprimir_taula_distancies () const;
};
#endif
