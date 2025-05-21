#include "etatAttenteStart.h"
#include "RGB.h"
#include "Buzzer.h"
#include "IR.h"

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */

bool EtatAttenteStart_S = false;
bool EtatAttenteStart_R = false;
int flag_EtatAttenteStart_1 = 0;
void EtatAttenteStart () {
    Serial.println("EtatAttenteStart");
    if (flag_EtatAttenteStart_1 == 0) {
#if DEBUG
        Buzzer();
#endif 
        flag_EtatAttenteStart_1 = 1;
    }
    /*if (printReceivedIR_S() == true) {
#if DEBUG
        Buzzer();
#endif
        EtatAttenteStart_S = true;
    }
     if (printReceivedIR_R() == true) {
#if DEBUG
        Buzzer();
#endif 
        EtatAttenteStart_R = true;
    }*/
    delay(100);
    EtatAttenteStart_S = true;
    
    
    
   

 }


bool Transition_AttenteStart_PassagePorte () { 
    //"on" sur télécommande IR
    return EtatAttenteStart_S;
}

bool Transition_AttenteStart_Recovery () { 
    //"recovery" sur télécommande IR
    return EtatAttenteStart_R;
}