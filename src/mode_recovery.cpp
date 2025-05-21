#include "mode_recovery.h"
#include "multiplexeur_Tof.h"
#include "Regul_vitesse.h"
#include "Encodeur.h"



// === Fonctions de base ===



// Vérifie si un mur est présent
// bool mur_present(int direction_relative) {
//   if (direction_relative == 0) return Tof_G() < SEUIL_MUR;
//   else if (direction_relative == 1) return Tof_D() < SEUIL_MUR;
//   else return Tof_G() < SEUIL_MUR;
// }
bool mur_present_droite ()
{
  if (Tof_D() < SEUIL_MUR_droite)
  {
  return true;

  }
  return false;
}
bool mur_present_gauche ()
{
  if (Tof_G() <  SEUIL_MUR_droite)
  {
  return true;
  }
}
bool mur_present_front ()
{
  if (Tof_AV_D() < SEUIL_MUR_devant)
  {
  return true;
  Serial.println("Mur devant");
  }
  return false;
  Serial.println("Pas de mur devant");
}

// === Setup ===
/*void mode_recovery_init() {
  
  // Initialiser les moteurs
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  delay(1000);
}*/

// === Boucle principale ===
void mode_recovery() {
  Serial.println("Mode recovery");
  if (!mur_present_droite()) 
  {
    Serial.println("Pas de mur à droite");
    Tout_Droit(nbPasEntreeCase);
  
    turnD(nbPasRotationDroite);
    
    Tout_Droit(nbPasSortieCase);
   
  } else if (mur_present_front()) 
  {
     Serial.println("Mur devant");
    turnG(nbPasRotationGauche);
    
  } /*else if (mur_present_gauche())
  {
    Regul_vitesse();
  }*/
  else 
  {
    Regul_vitesseDroit(); 
    // digitalWrite(IN4, HIGH);
    // digitalWrite(IN3, HIGH);
    // digitalWrite(IN2, HIGH);
    // digitalWrite(IN1, HIGH);
  }
}