#ifndef ENCODEUR
#define ENCODEUR_H

#include "config.h"


// Déclaration des fonctions
void EncoderInit();
void EncoderCPT_G();
void EncoderCPT_D();
void Encoder_afichage(char choix_moteur);
void turnD(int nbPas);

void turnG(int nbPas);

void Tout_Droit(int nbPas);

void regul_encodeur(int nbPas);

void Encoder_reset();

#endif