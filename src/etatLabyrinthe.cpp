#include "etatLabyrinthe.h"
#include "Buzzer.h"
#include "Regul_vitesse.h"
#include "RGB.h"
#include "mode_recovery.h"
#include "encodeur.h"
#include "etatCaseStart.h"


/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */
int flag_EtatLabyrinthe_1 = 0;
bool EtatLabyrinthe_canape_1 = false;
bool EtatLabyrinthe_sortie_1 = false;
bool EtatLabyrinthe_racourcis_1 = false;

// Declare instructions as a global variable


int flag_fauteuil = 0;
void EtatLabyrinthe () {
    EtatLabyrinthe_canape_1 = false;
    EtatLabyrinthe_sortie_1 = false;
    EncoderInit();
    Serial.println("EtatLabyrinthe");
    
    if (flag_EtatLabyrinthe_1 == 0) {
        Buzzer();
        flag_EtatLabyrinthe_1 = 1;
    }

    for(int i = 0; i < 50; i++)
    {
        Serial.print(instructionStartToChill[i]);
        Serial.print(" ");
    } 

    instructionsStart(instructionStartToChill);

    

    //instructionStartToChill[0] = 0;

    if (RGB() == 'b' && flag_fauteuil == 0) {
        flag_EtatLabyrinthe_1 = 0;
        flag_fauteuil = 1;
        EtatLabyrinthe_canape_1 = true;
    }

    if (RGB() == 'g' && flag_fauteuil == 1) {
        flag_EtatLabyrinthe_1 = 0;
        flag_fauteuil = 0;
        EtatLabyrinthe_sortie_1 = true;
    }

//démarrage des moteurs
//faire 20cm
//check son emplacement

}

bool Transition_Labyrinthe_Canape () {
return EtatLabyrinthe_canape_1;
}

bool Transition_Labyrinthe_Raccourci () {
return EtatLabyrinthe_racourcis_1;
}

bool Transition_Labyrinthe_Sortie () {
return EtatLabyrinthe_sortie_1;
}

bool Transition_Labyrinthe_Recovery () { 
    //"recovery" sur télécommande IR
}