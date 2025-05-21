#include "multiplexeur_Tof.h"
/*
Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor3 = Adafruit_VL53L0X();
 
void multiplexeur_Tof_init() {
  // Initialiser les broches XSHUT
  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);
 
  // Éteindre les deux capteurs
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  delay(10);
 
  // Activer capteur 1 uniquement
  digitalWrite(XSHUT1, HIGH);
  delay(10);
  if (!sensor1.begin(0x30, true)) {
    Serial.println("Échec initialisation capteur 1");
    while (1);
  }
 
  // Activer capteur 2
  digitalWrite(XSHUT2, HIGH);
  delay(10);
  if (!sensor2.begin(0x31)) {
    Serial.println("Échec initialisation capteur 2");
    while (1);
  }
// Activer capteur 3
  digitalWrite(XSHUT3, HIGH);
  delay(10);
  if (!sensor3.begin(0x32)) {
    Serial.println("Échec initialisation capteur 3");
    while (1);
  }
  Serial.println("Les deux capteurs sont initialisés !");
}
 
int Tof_AV_G()
{
   VL53L0X_RangingMeasurementData_t measure2;
  sensor2.rangingTest(&measure2, false);
  Serial.print("Capteur AV G: ");
  if (measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
    Serial.print(" mm");
    return measure2.RangeMilliMeter;
  } else {
    Serial.print("Erreur");
  }
}
 
int Tof_G()
{
   VL53L0X_RangingMeasurementData_t measure3;
  sensor3.rangingTest(&measure3, false);
  Serial.print("  |  Capteur G: ");
  if (measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
    Serial.print(" mm");
    return measure3.RangeMilliMeter;
  } else {
    Serial.print("Erreur");
  }
}
int Tof_D()
{
   VL53L0X_RangingMeasurementData_t measure1;
  sensor1.rangingTest(&measure1, false);
  Serial.print("  |  Capteur D: ");
  if (measure1.RangeStatus != 4) {
    Serial.print(measure1.RangeMilliMeter);
    Serial.print(" mm");
    return measure1.RangeMilliMeter;
  } else {
    Serial.print("Erreur");
  }
}
 
void multiplexeur_Tof() {
  VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;
  VL53L0X_RangingMeasurementData_t measure3;
 
  sensor1.rangingTest(&measure1, false);
  sensor2.rangingTest(&measure2, false);
  sensor3.rangingTest(&measure3, false);
 
  Serial.print("Capteur 1: ");
  if (measure1.RangeStatus != 4) {
    Serial.print(measure1.RangeMilliMeter);
    Serial.print(" mm");
  } else {
    Serial.print("Erreur");
  }
 
  Serial.print("  |  Capteur 2: ");
  if (measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
    Serial.print(" mm");
  } else {
    Serial.print("Erreur");
  }
  Serial.print("  |  Capteur 3: ");
  if (measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
    Serial.print(" mm");
  } else {
    Serial.print("Erreur");
  }
 
  Serial.println();
  delay(100);
}*/
#define TCAADDR 0x70  // Adresse du TCA9548A
 
Adafruit_VL53L0X sensor;  // Un seul capteur utilisé à la fois
 
// Sélection d’un canal sur le TCA9548A
void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}
 
void multiplexeur_Tof_init()
{
  while (!Serial);
    delay(1000);
 
    Wire.begin();
   
   
    Serial.println("\nTCAScanner ready!");
   
    for (uint8_t t=0; t<8; t++) {
      tcaSelect(t);
      Serial.print("TCA Port #"); Serial.println(t);
 
      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR) continue;
 
        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
      }
    }
    Serial.println("\ndone");
  Wire.begin();
 
  // Initialisation du capteur sur chaque canal sans modifier d’adresse
  for (uint8_t t=1; t<4; t++) {
    tcaSelect(t);           // Sélection du canal
    delay(10);              // Laisse le temps au TCA de commuter
    if (!sensor.begin(0x29||0x30||0x31,true)) {
      Serial.print("❌ Capteur non détecté sur canal ");
      Serial.println(t);
    } else {
      Serial.print("✅ Capteur détecté sur canal ");
      Serial.println(t);
    }
    delay(50);
  }
 
}  
 
int Tof_AV_G() {
    tcaSelect(0);
    //delay(10); // Sécurité
 
    VL53L0X_RangingMeasurementData_t measure;
    sensor.rangingTest(&measure, false);
 
    if (measure.RangeStatus != 4) {
      return measure.RangeMilliMeter;
      //Serial.print("Distance : ");
     // Serial.print(measure.RangeMilliMeter);
      //Serial.println(" mm");
    } else {
      // Serial.println("Mesure hors plage !");
      return 9999;
    }
 
    //delay(1000);
}
int Tof_AV_D() {
    tcaSelect(1);
    //delay(10); // Sécurité
 
    VL53L0X_RangingMeasurementData_t measure;
    sensor.rangingTest(&measure, false);
 
    if (measure.RangeStatus != 4) {
   
      //Serial.print("Distance : ");
      //Serial.print(measure.RangeMilliMeter);
      //Serial.println(" mm");
      return measure.RangeMilliMeter;
    } else {
      //Serial.println("Mesure hors plage !");
      return 9999;
    }
 
    //delay(1000);
}
 
int Tof_D() {
    tcaSelect(3);
    //delay(10); // Sécurité
 
    VL53L0X_RangingMeasurementData_t measure;
    sensor.rangingTest(&measure, false);
 
    if (measure.RangeStatus != 4) {
      //Serial.print("Distance droite : ");
      //Serial.print(measure.RangeMilliMeter);
      //Serial.println(" mm");
      return measure.RangeMilliMeter;
    } else {
      //Serial.println("Mesure hors plage !");
      return 9999;
    }
 
    //delay(1000);
}
 
int Tof_G() {
    tcaSelect(2);
    //delay(10); // Sécurité
 
    VL53L0X_RangingMeasurementData_t measure;
    sensor.rangingTest(&measure, false);
 
    if (measure.RangeStatus != 4) {
      //Serial.print("Distance gauche : ");
      //Serial.print(measure.RangeMilliMeter);
      //Serial.println(" mm");
      return measure.RangeMilliMeter;
    } else {
      //Serial.println("Mesure hors plage !");
      return 9999;
    }
 
    //delay(1000);
}
 
/*void multiplexeur_Tof(){
  VL53L0X_RangingMeasurementData_t measure;
 
  for (int i = 0; i < 4; i++) {
    tcaSelect(i);
    delay(2);  // petite pause pour la sélection
 
    sensor.rangingTest(&measure, false);
 
    Serial.print("Capteur ");
    Serial.print(i);
    Serial.print(" : ");
 
    if (measure.RangeStatus != 4) {
      Serial.print(measure.RangeMilliMeter);
      Serial.println(" mm");
    } else {
      Serial.println("hors de portée !");
    }
 
    delay(100);
  }
 
  Serial.println("-----------");
  delay(500);
}*/
 