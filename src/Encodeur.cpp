#include"Encodeur.h"

/**
 * Fonction exécutée pendant l'état initial
 * éteint la LED et passe à l'état ATTENTE sur appui du bouton
 * @param aucun
 * @return code_matrice
 */

 // === Vitesse de base ===


 int cpt_mot_G = 0;
 int cpt_mot_D = 0;
bool reset = false;

void EncoderInit()
{
    pinMode(ENC_G_B,INPUT);
    pinMode(ENC_G_A,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_G_A),EncoderCPT_G , CHANGE);
    

    pinMode(ENC_D_B,INPUT);
    pinMode(ENC_D_A,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_D_A),EncoderCPT_D , CHANGE);
}

void EncoderCPT_G()
{
    cpt_mot_G++;
    //Pour afficher la valeur de lencodeur
    //Encoder_afichage('G'); //pas conseillé de faire un Serial.print dans une ISR
}

void EncoderCPT_D()
{
    cpt_mot_D++;  
    //Pour afficher la valeur de lencodeur
    //Encoder_afichage('D');//pas conseillé de faire un Serial.print dans une ISR
}

void Encoder_afichage(char choix_moteur)
{
    if (choix_moteur == 'G' || choix_moteur == 'g')
    {
        Serial.print("Nombre de pas gauche :");
        Serial.println(cpt_mot_G);
    }
    else if (choix_moteur == 'D' || choix_moteur == 'd')
    {
        Serial.print("Nombre de pas droite :");
        Serial.println(cpt_mot_D);
    }
    else 
    {
        Serial.print("Choisir un moteur");
        
    }
}

void turnD (int nbPas)
{
    int fini_mouv_D_G = 0;
    int fini_mouv_D_D = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, HIGH);
   
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(ENA, baseSpeed_encodeur);
    analogWrite(ENB, baseSpeed_encodeur);
    while (fini_mouv_D_D == 0 && fini_mouv_D_G == 0){
        Serial.println("Mouvement en cours gauche");
        //regul_encodeur(nbPas);
        if (nbPas <= cpt_mot_G){
            analogWrite(ENA, 0);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN1, HIGH);
            fini_mouv_D_G = 1;
            Serial.println("Fini mouvement");
        }
        if (nbPas <= cpt_mot_D){
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            fini_mouv_D_D = 1;
            Serial.println("Fini mouvement");
        }
   
    }
}
/*void turnD(int nbPas) {
    int fini_mouv_D_G = 0;
    int fini_mouv_D_D = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;

    int vMin = 80;
    int vMax = baseSpeed_encodeur;
    int vitesse_G = vMin;
    int vitesse_D = vMin;
    int rampStep = 1;
    int rampDelay = 10;

    // Active les moteurs en avant
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // moteur G
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); // moteur D

    // 🚀 RAMP-UP linéaire
    while (vitesse_G < vMax || vitesse_D < vMax) {
        vitesse_G = min(vitesse_G + rampStep, vMax);
        vitesse_D = min(vitesse_D + rampStep, vMax);
        analogWrite(ENA, vitesse_G);
        analogWrite(ENB, vitesse_D);
        delay(rampDelay);
    }

    // 🧠 BOUCLE DE MOUVEMENT AVEC RAMP-DOWN INTELLIGENTE
    while (fini_mouv_D_G == 0 || fini_mouv_D_D == 0) {
        Serial.println("Mouvement en cours tout droit");

        regul_encodeur(nbPas);  // ta régulation PID de vitesse ou position

        // 🛑 RAMP-DOWN basée sur la distance restante
        float ratio_G = (float)(nbPas - cpt_mot_G) / nbPas;
        float ratio_D = (float)(nbPas - cpt_mot_D) / nbPas;
        ratio_G = constrain(ratio_G, 0.0, 1.0);
        ratio_D = constrain(ratio_D, 0.0, 1.0);

        vitesse_G = constrain(vMin + ratio_G * (vMax - vMin), vMin, vMax);
        vitesse_D = constrain(vMin + ratio_D * (vMax - vMin), vMin, vMax);

        if (!fini_mouv_D_G) analogWrite(ENA, vitesse_G);
        if (!fini_mouv_D_D) analogWrite(ENB, vitesse_D);

        // Arrêt individuel
        if (!fini_mouv_D_G && cpt_mot_G >= nbPas) {
            analogWrite(ENA, 0);
            digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Frein moteur
            fini_mouv_D_G = 1;
            Serial.println("Fini mouvement G");
        }

        if (!fini_mouv_D_D && cpt_mot_D >= nbPas) {
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); // Frein moteur
            fini_mouv_D_D = 1;
            Serial.println("Fini mouvement D");
        }
    }
}*/


void turnG(int nbPas)
{
    int fini_mouv_G_D = 0;
    int fini_mouv_G_G = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, HIGH);
   
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENB, baseSpeed_encodeur);
    analogWrite(ENA, baseSpeed_encodeur);
    while (fini_mouv_G_G == 0 && fini_mouv_G_D == 0){
        Serial.println("Mouvement en cours gauche");
        //regul_encodeur(nbPas);
        if (nbPas <= cpt_mot_G){
            analogWrite(ENA, 0);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN1, HIGH);
            fini_mouv_G_G = 1;
            Serial.println("Fini mouvement");
        }
        if (nbPas <= cpt_mot_D){
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            fini_mouv_G_D = 1;
            Serial.println("Fini mouvement");
        }
   
    }
}
/*void turnG(int nbPas) {
    int fini_mouv_G_D = 0;
    int fini_mouv_G_G = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;

    int vMin = 80;
    int vMax = baseSpeed_encodeur;
    int vitesse_G = vMin;
    int vitesse_D = vMin;
    int rampStep = 1;
    int rampDelay = 10;

    // Active les moteurs en avant
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); // moteur G
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // moteur D

    // 🚀 RAMP-UP linéaire
    while (vitesse_G < vMax || vitesse_D < vMax) {
        vitesse_G = min(vitesse_G + rampStep, vMax);
        vitesse_D = min(vitesse_D + rampStep, vMax);
        analogWrite(ENA, vitesse_G);
        analogWrite(ENB, vitesse_D);
        delay(rampDelay);
    }

    // 🧠 BOUCLE DE MOUVEMENT AVEC RAMP-DOWN INTELLIGENTE
    while (fini_mouv_G_D == 0 || fini_mouv_G_G == 0) {
        Serial.println("Mouvement en cours tout droit");

        regul_encodeur(nbPas);  // ta régulation PID de vitesse ou position

        // 🛑 RAMP-DOWN basée sur la distance restante
        float ratio_G = (float)(nbPas - cpt_mot_G) / nbPas;
        float ratio_D = (float)(nbPas - cpt_mot_D) / nbPas;
        ratio_G = constrain(ratio_G, 0.0, 1.0);
        ratio_D = constrain(ratio_D, 0.0, 1.0);

        vitesse_G = constrain(vMin + ratio_G * (vMax - vMin), vMin, vMax);
        vitesse_D = constrain(vMin + ratio_D * (vMax - vMin), vMin, vMax);

        if (!fini_mouv_G_G) analogWrite(ENA, vitesse_G);
        if (!fini_mouv_G_D) analogWrite(ENB, vitesse_D);

        // Arrêt individuel
        if (!fini_mouv_G_G && cpt_mot_G >= nbPas) {
            analogWrite(ENA, 0);
            digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Frein moteur
            fini_mouv_G_G = 1;
            Serial.println("Fini mouvement G");
        }

        if (!fini_mouv_G_D && cpt_mot_D >= nbPas) {
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); // Frein moteur
            fini_mouv_G_D = 1;
            Serial.println("Fini mouvement D");
        }
    }
}*/

void Tout_Droit(int nbPas)
{
    int fini_mouv_tout_droit_G = 0;
    int fini_mouv_tout_droit_D = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, HIGH);
   
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, baseSpeed_encodeur);
    analogWrite(ENB, baseSpeed_encodeur);
    while (fini_mouv_tout_droit_G == 0 && fini_mouv_tout_droit_D == 0){
        Serial.println("Mouvement en cours tout droit");
        regul_encodeur(nbPas);
        if (nbPas <= cpt_mot_G){
            analogWrite(ENA, 0);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN1, HIGH);
            fini_mouv_tout_droit_G = 1;
            Serial.println("Fini mouvement");
        }
        if (nbPas <= cpt_mot_D){
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            fini_mouv_tout_droit_D = 1;
            Serial.println("Fini mouvement");
        }

}
}
/*void Tout_Droit(int nbPas) {
    int fini_mouv_tout_droit_G = 0;
    int fini_mouv_tout_droit_D = 0;
    cpt_mot_D = 0;
    cpt_mot_G = 0;

    int vMin = 80;
    int vMax = baseSpeed_encodeur;
    int vitesse_G = vMin;
    int vitesse_D = vMin;
    int rampStep = 1;
    int rampDelay = 10;

    // Active les moteurs en avant
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // moteur G
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // moteur D

    // 🚀 RAMP-UP linéaire
    while (vitesse_G < vMax || vitesse_D < vMax) {
        vitesse_G = min(vitesse_G + rampStep, vMax);
        vitesse_D = min(vitesse_D + rampStep, vMax);
        analogWrite(ENA, vitesse_G);
        analogWrite(ENB, vitesse_D);
        delay(rampDelay);
    }

    // 🧠 BOUCLE DE MOUVEMENT AVEC RAMP-DOWN INTELLIGENTE
    while (fini_mouv_tout_droit_G == 0 || fini_mouv_tout_droit_D == 0) {
        Serial.println("Mouvement en cours tout droit");

        regul_encodeur(nbPas);  // ta régulation PID de vitesse ou position

        // 🛑 RAMP-DOWN basée sur la distance restante
        float ratio_G = (float)(nbPas - cpt_mot_G) / nbPas;
        float ratio_D = (float)(nbPas - cpt_mot_D) / nbPas;
        ratio_G = constrain(ratio_G, 0.0, 1.0);
        ratio_D = constrain(ratio_D, 0.0, 1.0);

        vitesse_G = constrain(vMin + ratio_G * (vMax - vMin), vMin, vMax);
        vitesse_D = constrain(vMin + ratio_D * (vMax - vMin), vMin, vMax);

        if (!fini_mouv_tout_droit_G) analogWrite(ENA, vitesse_G);
        if (!fini_mouv_tout_droit_D) analogWrite(ENB, vitesse_D);

        // Arrêt individuel
        if (!fini_mouv_tout_droit_G && cpt_mot_G >= nbPas) {
            analogWrite(ENA, 0);
            digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); // Frein moteur
            fini_mouv_tout_droit_G = 1;
            Serial.println("Fini mouvement G");
        }

        if (!fini_mouv_tout_droit_D && cpt_mot_D >= nbPas) {
            analogWrite(ENB, 0);
            digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); // Frein moteur
            fini_mouv_tout_droit_D = 1;
            Serial.println("Fini mouvement D");
        }
    }
}*/


// === PID LATÉRAL ===
float Kp_encodeur = 1.2;
float Ki_encodeur = 0.0;
float Kd_encodeur = 0.8;

float erreur_encodeur = 0;
float erreur_encodeur_prec = 0;
float integral_encodeur = 0;
unsigned long lastTime_encodeur = 0;




// === Fonction moteur gauche ===
void setMoteurGauche_encodeur(int pwm) {
    //digitalWrite(IN1, HIGH);
    //digitalWrite(IN2, LOW);
    analogWrite(ENA, pwm);
  }
  
  // === Fonction moteur droit ===
void setMoteurDroit_encodeur(int pwm) {
    //digitalWrite(IN3, HIGH);
    //digitalWrite(IN4, LOW);
    analogWrite(ENB, pwm);
  }

void regul_encodeur_init() 
{
  
}
void regul_encodeur(int nbPas) 
{
     
  // === Simule ou récupère les distances TOF ===
  int D3 = cpt_mot_D;//lireDistanceGauche();   // ← à remplacer par ton code
  int D4 = cpt_mot_G;//lireDistanceDroite();   // ← à remplacer par ton code

  
  // === PID LATÉRAL ===
  erreur_encodeur = D3 - D4;  // erreur_encodeur positive = trop à gauche
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime_encodeur) / 1000.0;
  lastTime_encodeur = currentTime;

  integral_encodeur += erreur_encodeur * dt;
  float derivative = (erreur_encodeur - erreur_encodeur_prec) / dt;
  erreur_encodeur_prec = erreur_encodeur;

  float correction = Kp_encodeur * erreur_encodeur + Ki_encodeur * integral_encodeur + Kd_encodeur * derivative;

  // === Application de la correction sur la vitesse ===
  int vitesseG = constrain(baseSpeed_encodeur + correction, 0, 150);
  int vitesseD = constrain(baseSpeed_encodeur - correction, 0, 150);
  if (nbPas <= cpt_mot_G){
           vitesseG = 0; 
        }
        if (nbPas <= cpt_mot_D){
            vitesseD = 0;
        }

  setMoteurGauche_encodeur(vitesseG);
  setMoteurDroit_encodeur(vitesseD);

  // === Debug ===
 /*Serial.print("D3: "); Serial.print(D3);
  Serial.print(" | D4: "); Serial.print(D4);
  Serial.print(" | erreur_encodeur: "); Serial.print(erreur_encodeur);
  Serial.print(" | Correction: "); Serial.print(correction);
  Serial.print(" | VitesseG: "); Serial.print(vitesseG);
  Serial.print(" | VitesseD: "); Serial.println(vitesseD);

  //delay(50);*/
}