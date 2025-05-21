#include "Regul_vitesse.h"
#include "multiplexeur_Tof.h"

/**
 * Fonction exécutée pendant l'état initial
 * éteint la LED et passe à l'état ATTENTE sur appui du bouton
 * @param aucun
 * @return code_matrice
 */

 // === Fonction moteur gauche ===
void setMoteurGauche(int pwm) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, pwm);
  }
  
  // === Fonction moteur droit ===
void setMoteurDroit(int pwm) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, pwm);
  }
  

float erreur = 0;
float erreur_prec = 0;
float integral = 0;
unsigned long lastTime = 0;



void Regul_vitesse_init() 
{
  // Initialisation moteurs
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  lastTime = millis();
}

void Regul_vitesse() 
{
  // === Simule ou récupère les distances TOF ===
  int D3 = Tof_D();//lireDistanceGauche();   // ← à remplacer par ton code
  int D4 = Tof_G();//lireDistanceDroite();   // ← à remplacer par ton code

  
  // === PID LATÉRAL ===
  erreur = D3 - D4;  // erreur positive = trop à gauche
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  integral += erreur * dt;
  float derivative = (erreur - erreur_prec) / dt;
  erreur_prec = erreur;

  float correction = Kp * erreur + Ki * integral + Kd * derivative;

  // === Application de la correction sur la vitesse ===
  int vitesseG = constrain(baseSpeed + correction, 0, 240);
  int vitesseD = constrain(baseSpeed - correction, 0, 240);

  setMoteurGauche(vitesseG);
  setMoteurDroit(vitesseD);

  // === Debug ===
   Serial.print("D3: "); Serial.print(D3);
  Serial.print(" | D4: "); Serial.print(D4);
  Serial.print(" | Erreur: "); Serial.print(erreur);
  Serial.print(" | Correction: "); Serial.print(correction);
  Serial.print(" | VitesseG: "); Serial.print(vitesseG);
  Serial.print(" | VitesseD: "); Serial.println(vitesseD);

  //delay(50);
}

void Regul_vitesseDroit() 
{
  // === Simule ou récupère les distances TOF ===
  int D3 = Tof_D();//lireDistanceGauche();   // ← à remplacer par ton code
  int consigne = SEUIL_MUR_droitreg_D;

  
  // === PID LATÉRAL ===
  erreur = D3 - consigne;  // erreur positive = trop à gauche
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  integral += erreur * dt;
  float derivative = (erreur - erreur_prec) / dt;
  erreur_prec = erreur;

  float correction = KpD * erreur + KiD * integral + KpD * derivative;

  // === Application de la correction sur la vitesse ===
  int vitesseG = constrain(baseSpeedD + correction, 0, baseSpeedD);
  int vitesseD = constrain(baseSpeedD - correction, 0, baseSpeedD);

  Serial.println("vitesseG: ");
  Serial.println(vitesseG);
  Serial.println("vitesseD: ");
  Serial.println(vitesseD);

  setMoteurGauche(vitesseG);
  setMoteurDroit(vitesseD);

  // === Debug ===
//   Serial.print("D3: "); Serial.print(D3);
//   Serial.print(" | D4: "); Serial.print(D4);
//   Serial.print(" | Erreur: "); Serial.print(erreur);
//   Serial.print(" | Correction: "); Serial.println(correction);

  //delay(50);
}

void Regul_vitesse_and_front()
{
if (Tof_AV_G () > 50)
    {
       Regul_vitesse(); 
    }
    else
    {
        digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
        digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); analogWrite(ENB, 0);
    }
  }