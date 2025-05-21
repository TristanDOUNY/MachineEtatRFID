#include "Buzzer.h"
 
#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784
#define NOTE_B5  988
#define NOTE_C6  1047
int melody[] = {
  659,  // E5
  784,  // G5
  659,  // E5
  523   // C5
};
int durations[] = {
  400, 400, 400, 800
};
 
void Buzzer_init(){
    pinMode(buzzerPin, OUTPUT);
 
    // Mario short theme (intro)
    tone(buzzerPin, NOTE_E5, 150);
    delay(150);
    tone(buzzerPin, NOTE_E5, 150);
    delay(300);
    tone(buzzerPin, NOTE_E5, 150);
    delay(300);
    tone(buzzerPin, NOTE_C5, 150);
    delay(150);
    tone(buzzerPin, NOTE_E5, 150);
    delay(300);
    tone(buzzerPin, NOTE_G5, 150);
    delay(550);
    tone(buzzerPin, NOTE_G4, 150);
    delay(550);
 
  noTone(buzzerPin);
}
 
void Buzzer(){
  tone(buzzerPin, 1000); // Joue un son de 1000 Hz
  delay(500);            // Pendant 500 millisecondes
  noTone(buzzerPin);     // Arrête le son
}

void BuzzerMelody() {
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, melody[i]);             // Joue la note
    delay(durations[i]);                 // Attend la durée de la note
    noTone(buzzerPin);                      // Arrête le son
    delay(100);                          // Pause entre les notes
  }
}

void jouerMelodie() {
  // Fréquences en Hz et durées en millisecondes
  int notes[][2] = {
  {194, 12},  {129, 12},  {108, 96},  {65, 36},  {108, 84},
  {86, 12},  {65, 24},  {108, 72},  {215, 12},  {1938, 12},
  {108, 12},  {129, 12},  {1593, 12},  {409, 12},  {431, 12},
  {129, 60},  {151, 12},  {431, 12},  {151, 24},  {215, 12},
  {237, 12},  {258, 408},  {431, 12},  {409, 12},  {366, 12},
  {388, 24},  {431, 36},  {409, 24},  {431, 24},  {409, 60},
  {431, 12},  {409, 60},  {1077, 12},  {1012, 24},  {172, 12},
  {366, 36},  {775, 12},  {797, 36},  {1206, 12},  {409, 48},
  {323, 36},  {409, 12},  {323, 36},  {301, 168},  {280, 36},
  {1357, 24},  {280, 48},  {560, 48},  {538, 24},  {1055, 48},
  {1034, 24},  {1012, 24},  {495, 72},  {474, 72},  {452, 84},
  {431, 84},  {409, 36},  {388, 12},  {581, 12},  {560, 60},
  {538, 12},  {517, 24},  {172, 48},  {388, 12},  {172, 12},
  {366, 36},  {172, 24},  {194, 12},  {172, 36},  {194, 12}
};
  int nombreNotes = sizeof(notes) / sizeof(notes[0]);

  for (int i = 0; i < nombreNotes; i++) {
    int freq = notes[i][0];
    int duree = notes[i][1];
    tone(buzzerPin, freq, duree);
    delay(duree + 50); // Petite pause entre les notes
  }
}
 