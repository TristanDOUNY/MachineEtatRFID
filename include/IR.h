//version 3 marche

#include "config.h"
 
// Pour inclure la librarie IRremote, il faut faire un premier include dans le fichier main (voir main.cpp).
// Ensuite, il faut inclure le fichier IRremoteInt.h avec la ligne suivante dans le code propre à l'infrarouge.
#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp> // This include is required for the IRremote library to work properly
#include <Arduino.h>
#include <IRremoteInt.h>
 
 
 
#include <IRremote.hpp>
 
// Déclaration de la structure
struct storedIRDataStruct {
    IRData receivedIRData;
    uint8_t rawCode[RAW_BUFFER_LENGTH];
    uint8_t rawCodeLength;
};
 
// Déclaration externe de la variable
extern storedIRDataStruct sStoredIRData0;
extern storedIRDataStruct sStoredIRData1;




 
// Prototypes des fonctions
void setupIR();
bool printReceivedIR_R();
bool printReceivedIR_S();
void sendCode0(storedIRDataStruct *aIRDataToSend);
void sendCode1(storedIRDataStruct *aIRDataToSend);
void storeCode0();
void storeCode1();
 
