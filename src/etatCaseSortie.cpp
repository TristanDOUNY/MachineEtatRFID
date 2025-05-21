#include "etatCaseSortie.h"
#include "RGB.h"
#include "Buzzer.h"

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */

 void EtatCaseSortie () {
    //arrêt des moteurs
    //emettre 2 signaux sonores   
    //couleur vert
    RGB();
    //envoyer les données du canapé
    //musique de fin
    Buzzer_init();
 }

 bool Transition_CaseSortie_Start () {

  }

  bool Transition_CaseSortie_Recovery () { 
   
  }