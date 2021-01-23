/**
* @mainpage Pràctica PRO2 Primavera 20/05/2020: Carla Campàs Gené

  En aquesta pràctica s'ha treballat els arbres filogenètics, en concret la seva creació i relació mitjançant clústers i especies.
  Les classes que s'han utilitzat per gestionar aquesta pràctica són: <em> Especie </em> , <em> Cjt_especies </em> i <em> Cjt_clusters </em>
*/

/** @file main.cc

    @brief Programa principal de la Practica de PRO2 de Priamvera 2020. La següent pràctica útilitza les classes descrites en aquesta documentació mitjança les següents comandes.
    Per fer la manipulació del codi utilitzem dos conjunts, un de espècies i un de clústers els quals treballem utilitzen les operacions descrites en aquest codi.

    Pel que fa el conjunt d'Especies (ce) tenim una seguida d'opcions per modificar el conjunt (crea_especie, elimina_especie), que afegeixen especies i esborren especies respectivament.
    També tenim unes instruccions per consultar les dades d'aquest conjunt (obtener_gen, distancia, existe_especie).
    Per últim en aquest conjunt es pot imprimir tant el conjunt com les distancies entre les diferents espècies del conjunt (imprime_cjt_especies, tabla_distancias).

    El conjunt de Clusters (cc) es tracta una mica diferent, respecte a opcions per modificar només n'hi han dos que modifiquen el conjunt en si (inicializa_clusters, imprime_arbol_filogenetico).
    A l'inicialitzar els clústers es queda un conjunt de clústers que tenen únicament una espècie. L'instruccio imrpime_arbol_filogenetico reinicialitza el conjunt i s'executa l'algoritme WPGMA (Weighted Pair Group Arithmetic Mean) fins que ens queda només un clúster, aquest clúster ens indica la "similitud" entre les diferents espècies del conjunt.
    Tenim una instruccio que s'utilitza per trobar les especies mes "similars" i juntarles, crean un nou cluster (pas_wpgma). I una instruccio per consultar e imprimir un cluster del conjunt (imprime_cluster)
*/

#include "Cjt_especies.hh"
#include "Cjt_clusters.hh"
using namespace std;

/** @brief Programa principal de la pràctica, es rep el codi i s'executa l'instrucció demanada */

int main(){
  int k;
  //S'insereix el valor de k per fer els kmers de les especies com valor estatic per la classe de especies
  cin >> k;
  Especie::set_k(k);

  string op;
  Cjt_especies ce;
  Cjt_clusters cc;
  cin >> op;
  while (op != "fin"){
   /* Cada cop que ens entra una operació imprimim la operacio, assumin que
    * l'input es correcte i en cada operacio fem l'output dels elements necessaris
    * per fer l'eco de la operacio*/
    cout << "# " << op;
    if (op == "crea_especie"){
      Especie e;
      e.llegir();
      cout << " " << e.consultar_idn() << " " << e.consultar_gen() << endl;
      bool b = ce.search (e.consultar_idn());

      if (not b) ce.afegir_especie (e);
      else cout << "ERROR: La especie " << e.consultar_idn() << " ya existe." << endl;
    }

    else if (op == "obtener_gen"){
      string idn;
      cin >> idn;
      cout << " " << idn << endl;
      bool b = ce.search(idn);
      if (b) cout << ce.consultar_especie(idn).consultar_gen() << endl;
      else cout << "ERROR: La especie " << idn << " no existe." << endl;
    }

    else if (op == "distancia"){
      string idn, idn1;
      cin >> idn >> idn1;
      cout << " " << idn << " " << idn1 << endl;
      bool b = ce.search(idn);
      bool b1 = ce.search (idn1);
      if (not b and b1) cout << "ERROR: La especie " << idn << " no existe." << endl;
      else if (b and not b1) cout << "ERROR: La especie " << idn1 << " no existe." << endl;
      else if (not b and not b1) cout << "ERROR: La especie " << idn << " y la especie " << idn1 << " no existen." << endl;
      else cout << ce.consultar_distancia(idn, idn1) << endl;
    }

    if (op == "elimina_especie"){
      string idn;
      cin >> idn;
      cout << " " << idn << endl;
      bool b = ce.search(idn);
      if (not b) cout << "ERROR: La especie " << idn << " no existe." << endl;
      else ce.elimina_especie (idn);
    }

    else if (op == "existe_especie"){ //existe especie
      string idn;
      cin >> idn;
      cout << " " << idn << endl;
      bool b = ce.search(idn);
      if (not b) cout << "NO" << endl;
      else cout << "SI" << endl;
    }

    else if (op == "lee_cjt_especies"){
      cout << endl;
      ce.llegir();
    }

    else if (op == "imprime_cjt_especies"){
      cout << endl;
      ce.escriure();
    }

    else if (op == "tabla_distancias"){
      cout << endl;
      ce.imprimir_taula_distancies();
    }

   else if (op == "inicializa_clusters"){
        cout << endl;
        cc = Cjt_clusters (ce);
        cc.imprimir_taula_distancies();
    }

    else if (op == "ejecuta_paso_wpgma"){
      cout << endl;
      if (cc.tamany() <= 1) cout << "ERROR: num_clusters <= 1" << endl;
      else{
        cc.pas_wpgma();
        cc.imprimir_taula_distancies();
      }
    }

    else if (op == "imprime_cluster"){
      string clust;
      cin >> clust;
      cout << " " << clust << endl;
      bool b = cc.buscar_cluster(clust);
      if (b) cc.escriure_cluster(cc.consultar_cluster(clust));
      else cout << "ERROR: El cluster " << clust << " no existe.";
      cout << endl;
    }

    else if (op == "imprime_arbol_filogenetico"){
      cout << endl;
      cc = Cjt_clusters (ce);
      if (cc.tamany() == 0) cout << "ERROR: El conjunto de clusters es vacio.";
      else cc.imprimir_arbre_filogenetic();
      cout << endl;
    }

    cin >> op;
    cout << endl;
  }
}
