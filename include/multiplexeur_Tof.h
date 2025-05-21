#ifndef multiplexeur_Tof_H
#define multiplexeur_Tof_H
 
#include "config.h"
 
// Déclaration des fonctions
void tcaSelect(uint8_t i);
void multiplexeur_Tof_init();
void multiplexeur_Tof();
int Tof_AV_G();
int Tof_AV_D();
int Tof_D();
int Tof_G();
 
 
 
#endif