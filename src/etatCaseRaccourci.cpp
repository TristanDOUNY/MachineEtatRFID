#include "etatCaseRaccourci.h"

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */

 void EtatCaseRaccourci () {
    //arrêt des moteurs
    //emettre 3 signaux sonores
    //ajouter flag raccourci
    //tempo de 5s
    delay(5000);   
 }

 bool Transition_CaseRaccourci_Labyrinthe () {
    return millis() >= 5000;
 }

 bool Transition_CaseRaccourci_Recovery () { 
    //"recovery" sur télécommande IR
 }