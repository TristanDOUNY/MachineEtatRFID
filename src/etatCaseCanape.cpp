#include "etatCaseCanape.h"
#include "RGB.h"	
#include "Buzzer.h"

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */
int flag_EtatCaseCanape_1 = 0;
bool EtatCaseCanape_1 = false;
 void EtatCaseCanape () {
    if (flag_EtatCaseCanape_1 == 0) {
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        BuzzerMelody();
        flag_EtatCaseCanape_1 = 1;
    }

    EtatCaseCanape_1 = true;


//arrêt des moteurs
//emettre 1 signal sonore
//couleur bleu
    //RGB();
//ajouter flag canapé
 }

 bool Transition_CaseCanape_Labyrinthe () { 
return EtatCaseCanape_1;
 }

 bool Transition_CaseCanape_Recovery () { 
    //"recovery" sur télécommande IR
 }