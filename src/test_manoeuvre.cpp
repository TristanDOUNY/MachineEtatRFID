// #include <Arduino.h>
// #include "config.h"
// #include "manoeuvre.h"



// void instructions(const char* liste) {
//   for (size_t i = 0; i < strlen(liste); i++) {
//     char instr = liste[i];
 
//     switch (instr) {
//       case 'A':
//         Serial.print("1200 pas\n");  // Avancer tout droit (1200 pas)
//         Serial.print("\n");
//         break;
//       case 'D':
//         Serial.print("+90°\n");  // Tourner à droite
//         Serial.print("1200 pas\n");        // Puis avancer (1200 pas)
//         Serial.print("\n");
//         break;
//       case 'G':
//         Serial.print("-90°\n");  // Tourner à gauche
//         Serial.print("1200 pas\n");        // Puis avancer (1200 pas)
//         Serial.print("\n");
//         break;
 
//       default:
//         Serial.print("Instruction inconnue : ");
//         Serial.println(instr);
//         break;
//     }
//   }
// }