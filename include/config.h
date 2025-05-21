// ce fichier de configuration rassemble au même endroit toutes les constantes

// ces lignes permettent d'éviter les inclusions multiples
#ifndef CONFIG_H
#define CONFIG_H 



#include <Arduino.h>
#include <StateMachine.h>
#include <mfrc522.h>
#include <SPI.h>
#include <DFRobot_TCS34725.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>
//#include <IRremote.hpp>
#include <Motor_PID.h>

#include "manoeuvre.h"

#define DEBUG 1 // 1 pour activer le mode debug, 0 pour le désactiver
#if DEBUG

#endif 

// le mot clé #define permet de définir des constantes, les valeurs seront effectivement remplacées
// dans le code avant la compilation.
// C'est une bonne pratique de mettre les constantes en majuscules.

// Définition des broches 
// capteur infara rouge 
// ir maj arduino mega 
#define ir_recepteur 22
#define ir_emeteur  44

//RFID
// maj arduino mega 
#define RST_PIN         23    //49
#define SS_PIN          24   //53

//matrice
extern bool test;
extern int* pointdata;
extern int* pathdijkStartToShort;
extern int* pathdijkStartToChill;
extern int* pathdijkShortToChill;
extern int* pathdijkChillToShort;
extern int* pathdijkChillToGoal;
extern int* pathdijkShortToGoal;
extern int* instructionStartToShort;
extern int* instructionStartToChill;
extern int* instructionShortToChill;
extern int* instructionChillToShort;
extern int* instructionChillToGoal;
extern int* instructionShortToGoal;

//Buzzer maj arduino mega 
#define buzzerPin 45

//passage de ligne  maj arduino mega
static int compteur_fin_course = 0;
#define finCourse  29 //pin arduino 
static int buttonState = LOW;       // État actuel du bouton
static int lastButtonState = LOW;   // État précédent


//BP test 
//const int Srfid = 4;
//const int Srgb = 5;
//char couleur; //stocke la première lettre de la couleur RGB

//Suiveur de ligne 
// maj arduino mega 
#define analogique A0
#define LIGNE_D1   39
#define LIGNE_D2   40
#define LIGNE_D3   41
#define LIGNE_D4   42
#define LIGNE_D5   43
#define calibration 25 

#define LIGNE_D3_int   18
extern bool flagPassagePorte;
/// =========================
// CONFIGURATION MOTEURS  
// =========================
//Broches L298N
#define ENA 12     // PWM moteur gauche
#define IN1 5
#define IN2 4

#define ENB 13   // PWM moteur droit
#define IN3 7
#define IN4 6

//Encodeurs
#define ENC_G_A 2
#define ENC_G_B 8
#define ENC_D_A 3
#define ENC_D_B 9

//Paramètres encodeur / roue
const int PPR = 360;              // impulsions par tour
const float diametreRoue = 6.5;   // en cm
const float distanceCibleCM = 1000.0;  // distance en cm à parcourir

// rgb 
//maj arduino mega 

#define ledRGB 27
#define intRGB 19  

//Xshut capteur tof
#define XSHUT1 31  // Broche XSHUT du capteur 1
#define XSHUT2 33  // Broche XSHUT du capteur 2
#define XSHUT3 35

extern Adafruit_VL53L0X sensor1; 
extern Adafruit_VL53L0X sensor2; 
extern Adafruit_VL53L0X sensor3; 

//-----------
//--encodeur--
//-----------


//---------------
//--Main droite--
//---------------

// === Seuil distance pour détecter mur ===
#define SEUIL_MUR_droite 300
#define SEUIL_MUR_devant 180 
#define nbPasEntreeCase 1300
#define nbPasRotationDroite 1700
#define nbPasRotationGauche 600 //1000 
#define nbPasSortieCase 2000

#define SEUIL_MUR_droitreg_D 200 // 200

#define baseSpeed_encodeur  150

//--------------
//--Régulation--
//--------------
// === PID LATÉRAL ===
#define Kp 1.2
#define Ki 0.0
#define Kd 0.8
// ===Pid main droite ===
#define KpD 1.2
#define KiD 0.0
#define KdD 0.6//0.8

// === Vitesse de base ===
#define baseSpeed 240
#define baseSpeedD 150 //ok a 200 !!pid!!

// Définition des délais
#define DELAI_BOUCLE_MS 10 // 10 millisecondes par boucle

// Déclaration des variables globales (définies dans main.cpp)
extern StateMachine machine;
extern unsigned long tempsDebut;

// Partie concernant le capteur IR
// ----------------------------------------------------------------
// Infrarouge
// protocole NEC uniquement pour ce projet
#define DECODE_NEC
#define EXCLUDE_EXOTIC_PROTOCOLS
#define RAW_BUFFER_LENGTH  750
// ----------------------------------------------------------------
 
// le mot clé #define permet de définir des constantes, les valeurs seront effectivement remplacées
// dans le code avant la compilation.
// C'est une bonne pratique de mettre les constantes en majuscules.
 
// Définition des broches
#define IR_RECEIVE_PIN 22
#define IR_SEND_PIN 44

//-----Eccelereation encodeur----
//int baseSpeed_encodeur = 0;         // Vitesse actuelle variable
//int targetSpeed_encodeur = 150;     // Vitesse désirée finale
//const int maxSpeed_encodeur = 240;
//const int accelerationStep_encodeur = 3; // plus petit = plus fluide






#endif
