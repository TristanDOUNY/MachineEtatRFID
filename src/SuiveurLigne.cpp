#include"SuiveurLigne.h"
 
/**
 * Fonction exécutée pendant l'état initial
 * éteint la LED et passe à l'état ATTENTE sur appui du bouton
 * @param aucun
 * @return aucun
 */
 
void LIGNE_init()
{
    pinMode(LIGNE_D1, INPUT);
    pinMode(LIGNE_D2, INPUT);
    pinMode(LIGNE_D3, INPUT);
    pinMode(LIGNE_D4, INPUT);
    pinMode(LIGNE_D5, INPUT);
}
 
void LIGNE()
{
    delay(250);
    if(digitalRead(LIGNE_D1)==1)
    {
        Serial.println(">>>>");
    }
 
    if(digitalRead(LIGNE_D2)==1)
    {
        Serial.println(">>");
    }
 
    if(digitalRead(LIGNE_D3)==1)
    {
        Serial.println("||");
    }
 
    if(digitalRead(LIGNE_D4)==1)
    {
        Serial.println("<<");
    }
 
    if(digitalRead(LIGNE_D5)==1)
    {
        Serial.println("<<<<");
    }
}