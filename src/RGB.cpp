#include "RGB.h"
#include "Buzzer.h"
#include "multiplexeur_Tof.h"
 
 
 
/**
 * Fonction exécutée pendant l'état initial
 * éteint la LED et passe à l'état ATTENTE sur appui du bouton
 * @param aucun
 * @return code_matrice
 */
 
DFRobot_TCS34725 tcs = DFRobot_TCS34725(&Wire, TCS34725_ADDRESS, TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
 
void RGB_init() {
    // Sélectionner le canal 3 du multiplexeur
    tcaSelect(0);
 
    // Initialiser le capteur RGB
    Serial.println("Color View Test!");
    while (tcs.begin() != 0) {
        Serial.println("No TCS34725 found ... check your connections");
        delay(1000);
    }
 
    Serial.println("Capteur RGB initialisé sur le canal 0 !");
}
 
char RGB() {
    // Sélectionner le canal 3 du multiplexeur
    tcaSelect(0);
 
    uint16_t clear, red, green, blue;
    tcs.getRGBC(&red, &green, &blue, &clear);
    tcs.lock();
    // Serial.print("C:\t"); Serial.print(clear);
    // Serial.print("\tR:\t"); Serial.print(red);
    // Serial.print("\tG:\t"); Serial.print(green);
    // Serial.print("\tB:\t"); Serial.print(blue);
    // Serial.println("\t");
 
    // Figure out some basic hex code for visualization
    uint32_t sum = clear;
    float r, g, b;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;
    Serial.print("\t");
    Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
    Serial.println();
    //delay(1000);
    if (r > g && r > b){
        Serial.println("rouge");
        //return('R');
        //Buzzer();
        //delay(100);
        //Buzzer();
        return 'r';
    }
    else{
        if (g > r && g > b){
            Serial.println("vert");
            //return('g');
            //Buzzer();
            //delay(100);
            //Buzzer();
            //delay(100);
            //Buzzer();
            return 'g';
 
        }
        else{
            if (b > g && b > r && b > 300){
            Serial.println("bleu");
             //return('b');
            //Buzzer();
            return 'b';  
        }
        }
       
    }
   
}