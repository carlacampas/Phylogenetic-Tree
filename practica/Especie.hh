/** @file Especie.hh
    @brief Conte l'especificació de la classe Especie

    Aquesta és la classe corresponent a les espècies del conjunt d'espècies que manipulem al programa principal. En aquesta classe es tenen guardades les dades de les espècies, i també s'utilitza per calcular la distància basada en els seus k-mers (seqüències de longitud k del gen). Que dóna la similitud entre les diferents espècies.
*/
#ifndef ESPECIES_HH
#define ESPECIES_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
using namespace std;
#endif

/** @class Especie
    @brief Representa l'informació i les operacions associades a una espècie.

    Aquesta és la classe corresponent a les espècies del conjunt d'espècies que manipulem al programa principal. En aquesta classe es tenen guardades les dades de les espècies, i també s'utilitza per calcular la distància basada en els seus k-mers (seqüències de longitud k del gen). Que dóna la similitud entre les diferents espècies.
*/
class Especie {

  //Descripció: Conte l'identificador, el gen de l'especie i els k-mers basats en el gen

private:
  /** @brief Identificador de l'especie*/
  string idn;
  /** @brief Gen de l'especie*/
  string gen;
  /** @brief Numero utilitzat per crear els kmers per calcular distancies, igual per totes les especies (static) i entra al principi del programa*/
  static int k;
  /** @brief Kmers per calcular distancia */
  map <string, int> kmer;

  /** @brief S'executa kmer per calcular la distancia entre espècies s'inicialitza a la constructora
      \pre <em> Cert </em>
      \post "kmer" del parametre implicit s'ha omplert
  */
  void produir_kmer();
public:
  //constructoras
  /** @brief Constructora de la clase espècie
      \pre <em> Cert </em>
      \post S'ha creat l'espècie buida
  */
  Especie ();

  //destructora
  /** @brief Destructora de la clase espècie
      \pre <em> Cert </em>
      \post El paràmetre implícit ja no existeix
  */
  ~Especie();
  //modifcadoras

  /** @brief Calcula la distancia entre el parametre implicit i "e1"
      \pre "e1" espècies no buides
      \post S'ha calculat la distancia amb el metode kmer
  */
  double distancia (Especie e1);

  /** @brief funcio que ompla la k amb l'int que entra al principi del codi
      \pre k ha set llegida del programa d'entrada inicialment
      \post s'ha afegit el valor de k per totes les especies
  */
  static void set_k(int k_set);

  //consultoras
  /** @brief Consultora del gen de l'espècie
      \pre <em> Cert </em>
      \post Retorna el gen de l'espècie
  */
  string consultar_gen () const;

  /** @brief Consultora de l'identificador de l'espècie
      \pre <em> Cert </em>
      \post Retorna l'identificador de l'espècie
  */
  string consultar_idn () const;

  /** @brief Es llegix l'espècie
      \pre Al canal d'entrada hi ha l'identificador i gen
      \post S'ha llegit la nova espècie
  */
  void llegir();

  /** @brief Escriu l'especie del parametre implicit per el canal de sortida
      \pre <em> Cert </em>
      \post Ha sortit l'especies per el canal de sortida
  */
  void escriure() const;
};

#endif
