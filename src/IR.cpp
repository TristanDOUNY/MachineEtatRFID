
#include "config.h"
#include "IR.h"
 
// Définition de la variable globale
storedIRDataStruct sStoredIRData0;
storedIRDataStruct sStoredIRData1;
 
bool DataStored0 = false;
bool DataStored1 = false;
bool robotOn = true;

void setupIR() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    IrSender.begin(); 
}   
 
void storeCode0() {
    if(DataStored0 == true) {    
        return;
    }
   
    // Vérifier si l'adresse est 0
    if (IrReceiver.decodedIRData.address != 0) {
        // Copie des données reçues dans la structure
        sStoredIRData0.receivedIRData = IrReceiver.decodedIRData;
        return;
    }   
 
    if (sStoredIRData0.receivedIRData.protocol == UNKNOWN) {
        sStoredIRData0.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
        IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData0.rawCode);
    } else {
        DataStored0 = true;        
    }
}
 
void storeCode1() {
    if(DataStored1 == true) {
        Serial.println(F("Données déjà envoyées."));
        return;
    }

    if (IrReceiver.decodedIRData.rawDataPtr->rawlen < 4) {
        return;
    }
 
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
        return;
    }
 
    // Vérifier si l'adresse est 1
    if (IrReceiver.decodedIRData.address != 1) {
         // Copie des données reçues dans la structure
        sStoredIRData1.receivedIRData = IrReceiver.decodedIRData;
        return;
    }
 
   
    if (sStoredIRData1.receivedIRData.protocol == UNKNOWN) {
        sStoredIRData1.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
        IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData1.rawCode);
    } else {
        DataStored1 = true; 
    }    
}


bool printReceivedIR_R() {
    if (IrReceiver.decode()) {
        Serial.println();
        IrReceiver.printIRResultShort(&Serial);        
        // IrReceiver.resume();  // Enable receiving of the next value
         if (IrReceiver.decodedIRData.protocol == NEC &&
            IrReceiver.decodedIRData.address == 0x00 &&
            IrReceiver.decodedIRData.command == 0x43) {
            //Serial.println(F("Démarrage mode recovery :"));
            return true;  
        }
        else{
            return false;
        }
       
        IrReceiver.resume();  // Enable receiving of the next value
    }
    return false;
}
bool printReceivedIR_S() {
    if (IrReceiver.decode()) {
        Serial.println();
        IrReceiver.printIRResultShort(&Serial);        
        IrReceiver.resume();  // Enable receiving of the next value
    
        if (IrReceiver.decodedIRData.protocol == NEC &&
            IrReceiver.decodedIRData.address == 0x00 &&
            IrReceiver.decodedIRData.command == 0x44) {
            if(robotOn == false) {
                Serial.println(F("Démarrage du robot :"));
                
                return true;
            }
        } else {
            return false;
        }
        IrReceiver.resume();  // Enable receiving of the next value
    }
}
 
void sendCode0(storedIRDataStruct *aIRDataToSend) {
          
    Serial.println(F("Envoi des données IR décodées :"));
    Serial.print(F("Protocole : "));
    Serial.println(aIRDataToSend->receivedIRData.protocol);
    Serial.print(F("Adresse : "));
    Serial.println(aIRDataToSend->receivedIRData.address, HEX);
    Serial.print(F("Commande : "));
    Serial.println(aIRDataToSend->receivedIRData.command, HEX);
    IrSender.write(&aIRDataToSend->receivedIRData);
    Serial.println(F("Données IR envoyées."));
}
 
void sendCode1(storedIRDataStruct *aIRDataToSend) {
    
    Serial.println(F("Envoi des données IR décodées :"));
    Serial.print(F("Protocole : "));
    Serial.println(aIRDataToSend->receivedIRData.protocol);
    Serial.print(F("Adresse : "));
    Serial.println(aIRDataToSend->receivedIRData.address, HEX);
    Serial.print(F("Commande : "));
    Serial.println(aIRDataToSend->receivedIRData.command, HEX);
    IrSender.write(&aIRDataToSend->receivedIRData);
    Serial.println(F("Données IR envoyées."));
}
