#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP

#include <thread>             
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std; 

class Controleur {
  public:
    Controleur (int valeur_initiale) : 
    val(valeur_initiale)
    {
    }
    
    // Train qui veut entrer en B pour aller vers A (sens B->A)
    bool controlinEnB(int numero) { 
        // Autorisé si voie libre ou déjà dans le même sens
        if (sens == 0 || sens == -1) {
            if (sens == 0) sens = -1;   // fixe le sens si voie était libre
            nbSurVoie++;
            return true;
        }
        return false;
    }  

    // Train qui veut entrer en A pour aller vers B (sens A->B)
    bool controlinEnA(int numero) { 
        // Autorisé si voie libre ou déjà dans le même sens
        if (sens == 0 || sens == 1) {
            if (sens == 0) sens = 1;   // fixe le sens si voie était libre
            nbSurVoie++;
            return true;
        }
        return false;
    }  

    // Train A->B qui sort en B
    bool controloutEnB(int numero){ 
      if(nbSurVoie > 0) {nbSurVoie--;}
      if (nbSurVoie == 0) {sens = 0;} // libère la voie si plus personne dessus
      return true;
    }

    // Train B->A qui sort en A
    bool controloutEnA(int numero){ 
      if(nbSurVoie > 0) {nbSurVoie--;}
      if (nbSurVoie == 0) {sens = 0;} // libère la voie si plus personne dessus
      return true;
    }

  private:
    int val;
    int nbSurVoie = 0; // nombre de trains sur la voie unique
    int sens = 0;      // 0=libre, 1=A->B, -1=B->A
};

#endif //CONTROLEUR_HPP
