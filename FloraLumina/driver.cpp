/**
 * @file driver.cpp
 * @author Simon Groc (simon.groc@u-paris.fr)
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
  #include "driver.h"
  // #include "wemosWebServer.h"


// Constructeur
/**
 * @brief Construct a new Driver:: Driver object
 * 
 */
Driver::Driver() {
  // Initialisation des numéros de broches
  Step = 13;
  Dire = 15;
  Sleep = 12;
  captHigh = 16;
  captLow = 14;
  // Configuration des modes de broche
  pinMode(Step, OUTPUT);    //Step pin as output
  pinMode(Dire, OUTPUT);    //Direction pin as output
  pinMode(Sleep, OUTPUT);   //Set Sleep OUTPUT Control button as output
  digitalWrite(Step, LOW);  // Currently no stepper motor movement
  digitalWrite(Dire, HIGH);

  //capteur de fin de course
  pinMode(captHigh, INPUT);
  pinMode(captLow, INPUT);
  // Initialize the stepper motor Driver
  digitalWrite(Sleep, LOW);  //A logic high allows normal operation of the A4988 by removing from sleep
  dir = 1;
  moment = 0;
  continut = false;
  spr = 100;
  // nombre de pas
  high = 0;
  // positions courante
  curentPos = 0;
  wantPos = 1;
  // generateur de temp
  stopDuring = false;
  gt = nullptr;
  //stepCounter();
}
/**
 * @brief Fonction pour vérifier si le moteur n'est pas en rotation
 * 
 * @return true 
 * @return false 
 */
bool Driver::isRotate() {
  return gt == nullptr || gt->end() || stopDuring;
}
/**
 * @brief Fonction pour vérifier si la limite haute est atteinte
 * 
 * @return true 
 * @return false 
 */
bool Driver::stopHigh() {
  finHigh = digitalRead(captHigh);
  return !finHigh;
}
/**
 * @brief Fonction pour vérifier si la limite basse est atteinte
 * 
 * @return true 
 * @return false 
 */
bool Driver::stopLow() {
  finLow = digitalRead(captLow);
  return !finLow;
}
/**
 * @brief Fonction pour effectuer l'opération de comptage des pas
 * 
 * @param server 
 */
void Driver::stepCounter(ESP8266WebServer &server) {
  server.handleClient();
  // wemosWebServerLoop();
  // Fait tourner le moteur jusqu'à ce que la limite haute soit atteinte
  while (!stopHigh()) {
    move(2000, 50);
    server.handleClient();
    // wemosWebServerLoop();
  }
  dir = 0;
  // Fait tourner le moteur jusqu'à ce que la limite basse soit atteinte
  while (!stopLow()) {
    high += move(2000, 50);
    server.handleClient();
    // wemosWebServerLoop();
  }
}
/**
 * @brief Fonction pour changer la position du moteur
 * 
 * @param pos 
 * @param motorSpeedValue 
 */
void Driver::changePosition(int pos, int motorSpeedValue) {
  // Vérifie si le moteur ne tourne pas actuellement et si la position est différente de l'ancienne position
  if ((gt == nullptr || gt->end() || stopDuring) && pos != oldPos) {
    // Libère la mémoire allouée pour l'objet générateur de temps précédent
    free(gt);
    // Associe la position désirée à celle en nombre de pas du moteur
    wantPos = map(pos, 0, 100, 0, high);
    // Crée un nouvel objet générateur de temps
    gt = new GenerateTime(curentPos, wantPos,  motorSpeedValue);
    oldPos = pos;
    // Définit le drapeau de mouvement continu si la position désirée est aux limites
    if (wantPos == 0 || wantPos == high) {
      continut = true;
    }
    stopDuring = false;
  }
  // Déplace le moteur vers la position désirée
  if (curentPos < wantPos) {
    if (!stopHigh()) {
      dir = 1;
      move(2000);
    } else {
      high = curentPos;
      wantPos = high;
      stopDuring = true;
    }
  } else if (curentPos > wantPos) {
    if (!stopLow()) {
      dir = 0;
      move(2000);
    } else {
      high -= curentPos;
      curentPos = 0;
      wantPos = 0;
      stopDuring = true;
    }
  } else {
    if ((dir && !stopHigh() || !dir && !stopLow()) && continut) {
      high += move(2000, 150);
    } else {

      continut = false;
      
    }
  }
}
/**
 * @brief Fait avencer le moteur avec une vitese indiquer
 * 
 * @param steps 
 * @param time 
 * @return int 
 */
int Driver::move(int steps, int time) {
  int count = 0;
  spr = time;
  // Vérifie si le moteur doit tourner
  if (!(dir && !stopHigh() || !dir && !stopLow())) {
    
  } else {
    digitalWrite(Sleep, LOW);
    digitalWrite(Dire, dir);
  }
  int i = 0;
  // Effectue les pas
  while (i < steps && (dir && !stopHigh() || !dir && !stopLow())) {
    if (moment == spr) {
      digitalWrite(Step, HIGH);
      count += 1;
    }
    if (moment >= spr * 2) {
      digitalWrite(Step, LOW);
      count += 1;
      moment = 0;
    }
    moment++;
    i++;
  }
  return count;
}
/**
 * @brief Fais avencer le moteur avec une vites dinamique
 * 
 * @param steps 
 */
void Driver::move(int steps) {
  // Vérifie si le moteur doit tourner
  if (!(dir && !stopHigh() || !dir && !stopLow())) {
    
  } else {
    digitalWrite(Sleep, LOW);
    digitalWrite(Dire, dir);
  }

  int i = 0;
  // Effectue les pas
  while (wantPos != curentPos && i < steps && (dir && !stopHigh() || !dir && !stopLow())) {
    if (moment == spr) {
      spr = gt->value();
      digitalWrite(Step, HIGH);
      if (dir) {
        curentPos += 1;
      } else {
        curentPos -= 1;
      }
      gt->next();
    }
    if (moment >= spr * 2) {
      spr = gt->value();
      digitalWrite(Step, LOW);
      if (dir) {
        curentPos += 1;
      } else {
        curentPos -= 1;
      }
      moment = 0;
      gt->next();
    }
    moment++;
    i++;
  }
}