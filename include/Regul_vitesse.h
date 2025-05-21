#ifndef Regul_vitesse_H
#define Regul_vitesse_H
 
#include "config.h"
 
// Déclaration des fonctions
void setMoteurGauche(int pwm);
void setMoteurDroit(int pwm);
void Regul_vitesse_init();
void Regul_vitesse();
void Regul_vitesseDroit();
void Regul_vitesse_and_front();
 
 
 
 
 
#endif