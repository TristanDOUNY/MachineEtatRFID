#include <Arduino.h>
#include "config.h"
#include "manoeuvre.h"
#include "Encodeur.h"
#include "Regul_vitesse.h"

//extern int nbPas;

void instructions(int* liste) {
  for (size_t i = 0; i < 50; i++) {
    int instr = liste[i];
 
    if (instr == -1) {
      break;  // Sortir de la boucle si l'instruction est -1
    }
    switch (instr) {
      case 0:
        Tout_Droit(3725);  // Avancer tout droit
        break;

      case 2:
        turnD(1300);  // Tourner à droite
        Tout_Droit(3725);  // Avancer tout droit
        break;

      case 1:
        turnG(1350);  // Tourner à gauche
        Tout_Droit(3725);  // Avancer tout droit
        break;
 
      default:
        Serial.print("Instruction inconnue : ");
        Serial.println(instr);
        break;
    }
  }
}

void instructionsStart(int* liste) {
  for (size_t i = 1; i < 50; i++) {
    int instr = liste[i];
 
    if (instr == -1) {
      break;  // Sortir de la boucle si l'instruction est -1
    }
    switch (instr) {
      case 0:
        Tout_Droit(3725);  // Avancer tout droit
        break;

      case 2:
        turnD(1300);  // Tourner à droite
        Tout_Droit(3725);  // Avancer tout droit
        break;

      case 1:
        turnG(1350);  // Tourner à gauche
        Tout_Droit(3725);  // Avancer tout droit
        break;
 
      default:
        Serial.print("Instruction inconnue : ");
        Serial.println(instr);
        break;
    }
  }
}