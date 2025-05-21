#include "etatPassagePorte.h"
#include "Regul_vitesse.h"
#include "Fin_course.h"
#include "Buzzer.h"

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */
int nb_case = 2;
int flag_EtatPassagePorte_1 = 0;
bool EtatPassagePorte_1 = false;
void EtatPassagePorte() {
    Serial.println("EtatPassagePorte");
    if (flag_EtatPassagePorte_1 == 0) {
        Buzzer();
        flag_EtatPassagePorte_1 = 1;
    }

    Regul_vitesse();
    
    if (flagPassagePorte == true) {
        digitalWrite(IN4, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, HIGH);
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        EtatPassagePorte_1 = true;
    }
//désactive TOF avant
//démarrage des moteurs


}

bool Transition_PassagePorte_Labyrinthe () {

//dès que le fin de course détecte le passage de la case, il passe à l'état labyrinthe 
//return !finCourse;
return EtatPassagePorte_1;

}

bool Transition_PassagePorte_Recovery () { 
    //"recovery" sur télécommande IR
}