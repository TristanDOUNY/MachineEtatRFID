#include "config.h"
#include "etatCaseStart.h"
#include "etatAttenteStart.h"
#include "etatPassagePorte.h"
#include "etatLabyrinthe.h"
#include "etatMascotte.h"
#include "etatCaseCanape.h"
#include "etatCaseRaccourci.h"
#include "etatCaseSortie.h"
#include "etatCaseStart_Recovery.h"
#include "etatAttenteStart_Recovery.h"
#include "etatPassagePorte_Recovery.h"
#include "etatLabyrinthe_Recovery.h"
#include "etatCaseCanape_Recovery.h"
#include "etatCaseRaccourci_Recovery.h"
#include "etatMascotte_Recovery.h"
#include "etatCaseSortie_Recovery.h"


// inclusion des capteurs
#include "multiplexeur_Tof.h"
#include "RGB.h"
#include "Regul_vitesse.h"
#include "Fin_course.h"
#include "Encodeur.h"
#include "mode_recovery.h"
#include "SuiveurLigne.h"
#include "Buzzer.h"
#include <IRremote.hpp>
#include "IR.h"
#include "RFID.h"

#include "manoeuvre.h"

bool flagPassagePorte = false; // Variable pour indiquer si le capteur de ligne a détecté une ligne

//Définition des variables globales
StateMachine machine = StateMachine();

// Création des états
State* etatCaseStart = machine.addState(&EtatCaseStart);
State* etatAttenteStart = machine.addState(&EtatAttenteStart);
State* etatPassagePorte = machine.addState(&EtatPassagePorte);
State* etatLabyrinthe = machine.addState(&EtatLabyrinthe);
State* etatCaseCanape = machine.addState(&EtatCaseCanape);
State* etatCaseRaccourci = machine.addState(&EtatCaseRaccourci);
State* etatCaseSortie = machine.addState(&EtatCaseSortie);
State* etatMascotte = machine.addState(&EtatMascotte);
State* etatCaseStart_Recovery = machine.addState(&EtatCaseStart_Recovery);
State* etatAttenteStart_Recovery = machine.addState(&EtatAttenteStart_Recovery);
State* etatPassagePorte_Recovery = machine.addState(&EtatPassagePorte_Recovery);
State* etatLabyrinthe_Recovery = machine.addState(&EtatLabyrinthe_Recovery);
State* etatCaseCanape_Recovery = machine.addState(&EtatCaseCanape_Recovery);
State* etatCaseRaccourci_Recovery = machine.addState(&EtatCaseRaccourci_Recovery);
State* etatMascotte_Recovery = machine.addState(&EtatMascotte_Recovery);
State* etatCaseSortie_Recovery = machine.addState(&EtatCaseSortie_Recovery);

int* instructionStartToShort = nullptr;
int* instructionStartToChill = nullptr;
int* instructionShortToChill = nullptr;
int* instructionChillToShort = nullptr;
int* instructionChillToGoal = nullptr;
int* instructionShortToGoal = nullptr;

int* pathdijkStartToShort = nullptr;
int* pathdijkStartToChill = nullptr;
int* pathdijkShortToChill = nullptr;
int* pathdijkChillToShort = nullptr;
int* pathdijkChillToGoal = nullptr;
int* pathdijkShortToGoal = nullptr;

//bool test = false;
int* pointdata = nullptr;

//Fonction lié a l'interruption du suiveur de ligne
void detectionLigne() 
{
    //Serial.println("Détection de ligne !");
    // Vérifie si le capteur de ligne détecte une ligne
    Buzzer();
    flagPassagePorte = true;
}

void setup () {
    //Initialisation de la communication série
    Serial.begin(9600);
    //initialisation des capteurs
    
    multiplexeur_Tof_init();
    delay(100);
    RGB_init();
    Regul_vitesse_init();
    Fin_course_init();
    LIGNE_init();
    setupIR();
    rfid_init();
    
    



    //Configuration des broches

    //Configuration des transitions automatiques
    etatCaseStart->addTransition(&Transition_CaseStart_AttenteStart,etatAttenteStart);
    etatAttenteStart->addTransition(&Transition_AttenteStart_PassagePorte,etatPassagePorte);
    etatPassagePorte->addTransition(&Transition_PassagePorte_Labyrinthe,etatLabyrinthe);

    etatLabyrinthe->addTransition(&Transition_Labyrinthe_Canape,etatCaseCanape);
    etatLabyrinthe->addTransition(&Transition_Labyrinthe_Raccourci,etatCaseRaccourci);
    etatLabyrinthe->addTransition(&Transition_Labyrinthe_Sortie,etatCaseSortie);

    etatCaseCanape->addTransition(&Transition_CaseCanape_Labyrinthe,etatLabyrinthe);
    etatCaseRaccourci->addTransition(&Transition_CaseRaccourci_Labyrinthe,etatLabyrinthe);
    etatCaseSortie->addTransition(&Transition_CaseSortie_Start,etatCaseStart);

    //Configuration des transitions automatiques
    etatCaseStart_Recovery->addTransition(&Transition_CaseStart_AttenteStart_Recovery,etatAttenteStart_Recovery);
    etatAttenteStart_Recovery->addTransition(&Transition_AttenteStart_PassagePorte_Recovery,etatPassagePorte_Recovery);
    etatPassagePorte_Recovery->addTransition(&Transition_PassagePorte_Labyrinthe_Recovery,etatLabyrinthe_Recovery);

    etatLabyrinthe_Recovery->addTransition(&Transition_Labyrinthe_Canape_Recovery,etatCaseCanape_Recovery);
    etatLabyrinthe_Recovery->addTransition(&Transition_Labyrinthe_Raccourci_Recovery,etatCaseRaccourci_Recovery);
    etatLabyrinthe_Recovery->addTransition(&Transition_Labyrinthe_Sortie_Recovery,etatCaseSortie_Recovery);

    etatCaseCanape_Recovery->addTransition(&Transition_CaseCanape_Labyrinthe_Recovery,etatLabyrinthe_Recovery);
    etatCaseRaccourci_Recovery->addTransition(&Transition_CaseRaccourci_Labyrinthe_Recovery,etatLabyrinthe_Recovery);
    etatCaseSortie_Recovery->addTransition(&Transition_CaseSortie_Start_Recovery,etatCaseStart_Recovery);


    //Configuration des transitions entre recovery et normal
    etatCaseStart_Recovery->addTransition(&Transition_CaseStart,etatCaseStart);
    etatCaseStart->addTransition(&Transition_CaseStart_Recovery,etatCaseStart_Recovery);

    etatAttenteStart_Recovery->addTransition(&Transition_AttenteStart,etatAttenteStart);
    etatAttenteStart->addTransition(&Transition_AttenteStart_Recovery,etatAttenteStart_Recovery);

    etatPassagePorte_Recovery->addTransition(&Transition_PassagePorte,etatPassagePorte);
    etatPassagePorte->addTransition(&Transition_PassagePorte_Recovery,etatPassagePorte_Recovery);
  
    etatLabyrinthe_Recovery->addTransition(&Transition_Labyrinthe,etatLabyrinthe);
    etatLabyrinthe->addTransition(&Transition_Labyrinthe_Recovery,etatLabyrinthe_Recovery);

    etatCaseCanape_Recovery->addTransition(&Transition_CaseCanape,etatCaseCanape);
    etatCaseCanape->addTransition(&Transition_CaseCanape_Recovery,etatCaseCanape_Recovery);

    etatCaseRaccourci_Recovery->addTransition(&Transition_CaseRaccourci,etatCaseRaccourci);
    etatCaseRaccourci->addTransition(&Transition_CaseRaccourci_Recovery,etatCaseRaccourci_Recovery);

    etatMascotte_Recovery->addTransition(&Transition_Mascotte,etatMascotte);
    etatMascotte->addTransition(&Transition_Mascotte_Recovery,etatMascotte_Recovery);

    etatCaseSortie_Recovery->addTransition(&Transition_CaseSortie,etatCaseSortie);
    etatCaseSortie->addTransition(&Transition_CaseSortie_Recovery,etatCaseSortie_Recovery);

    pinMode(LIGNE_D3, INPUT);
    pinMode(LIGNE_D3_int, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(LIGNE_D3_int), detectionLigne, RISING);

    
    

    //Démarrage de la machine d'état
    machine.run();
}

void loop() {
    //Mettre à jour la machine d'état
    machine.run();
    

    /*
    if ("ligne"->isActive()) {
    bool Transition_Labyrinthe_Mascotte () = 1;
        if ("ligne"->isDesactive()) {
            bool Transition_Labyrinthe_Mascotte () = 0;
            bool Transition_Mascotte_Labyrinthe () = 1;
        }
    }
    */


    //Petit délai pour éviter une utilisatuion excessive du CPU
    delay(DELAI_BOUCLE_MS);
}