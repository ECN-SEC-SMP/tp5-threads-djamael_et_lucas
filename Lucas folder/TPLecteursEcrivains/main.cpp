#include <iostream>           
#include <thread>             
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "Semaphore.hpp"

using namespace std;

int ressourcePartagee = 0;
Semaphore mutex_ressource(1); // pour l'accès à la ressource partagée
Semaphore ecrit(1); // pour l'accès en écriture
int l = 0; // nombre de lecteurs en cours de lecture

void lecteur(int numLecteur){
  for (int i = 0; i < 4; i++){
    mutex_ressource.P(numLecteur);
    l++;
    if (l == 1) {
      ecrit.P(numLecteur); // premier lecteur bloque les écrivains
    }
    mutex_ressource.V(numLecteur);

    std::cout << "Lecteur n° " << numLecteur << " en cours " << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000) );
    std::cout << "        Valeur lue = " << ressourcePartagee << "  " << endl;

    mutex_ressource.P(numLecteur);
    l--;
    if (l == 0) {
      ecrit.V(numLecteur); // dernier lecteur débloque les écrivains
    }
    mutex_ressource.V(numLecteur);
  }
}

void ecrivain(int numEcrivain){

  int x;
  for (int i = 0; i < 4; i++){
    ecrit.P(numEcrivain);

    std::cout << "Ecrivain n° " << numEcrivain << " en cours " << endl;
    x = ressourcePartagee;
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000) );
    std::cout << "valeur à incrémenter de la ressourcePartagee = " << x << "  " << endl;
    ressourcePartagee = x+1 ;

    ecrit.V(numEcrivain);
  }

}

int main() {
  std::srand((unsigned)std::time(nullptr));
  std::cout << "Début du programme" << endl;

  const int nbr = 8; // nombre de lecteurs et écrivains
  std::thread r[nbr];
  std::thread w[nbr];
  //int ressourcePartagee = 0;


  for (int i = 1; i < nbr; i++){ // création des threads
    r[i] = std::thread(lecteur, -i);
    w[i] = std::thread(ecrivain, i);
  }
// Join des threads 
  for (int i = 1; i < nbr; i++) {
  r[i].join(); 
  w[i].join();   
  }
  return 0;
}
