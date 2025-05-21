#include "Fin_course.h"
 
void Fin_course_init(){
    pinMode(finCourse, INPUT_PULLUP);
    static int lastButtonState = LOW; // État précédent
    int buttonState = LOW; // État actuel
    
}
 
bool Fin_course(int nb_case){
    // Lecture de l'état du bouton
   buttonState = digitalRead(finCourse);
    //FRONT MONTANT : LOW -> HIGH
  if (buttonState == HIGH && lastButtonState == LOW) {
    compteur_fin_course++;
    //Serial.print("Compteur : ");
    //Serial.println(compteur_fin_course);
  }
  //delay(10);
  lastButtonState = buttonState; // Mise à jour pour prochaine boucle
  if (compteur_fin_course >= nb_case){
        return true;
    }
    else{
        return false;
    }
}
/*bool test_fin_course(){
    if (compteur_fin_course <= 1){
        return true;
    }
    else{
        return false;
    }
}*/