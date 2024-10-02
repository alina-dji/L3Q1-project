#ifndef driver_H
#define driver_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "generateTime.h"


class Driver{
  private:
    //Pin pour changer la polariter du moteur
    int Step;
    // Dire Pin pour changer la direction du moteur et dir : valirable qui indique la directions du moteur
    int Dire, dir;
    // Pin pour On/Off le moteur avec LOW/HIGH
    int Sleep;
    //variable qui determine quand conter le nombre de pas du moteur

    //Pin du capteur High et Low
    int captHigh, captLow;
    // Pas par tour
    int spr;
    //conteur de temp entre deux pas
    int moment;
    // État des capteur haut et bas
    int finHigh, finLow;

  // Variables de position et de mouvement
    int high;           // Nombre total de pas 
    int curentPos;      // Position actuelle
    int wantPos;        // Position désirée
    int oldPos;         // Ancienne position  

    // Autres variables de contrôle
    GenerateTime *gt; // Pointeur vers l'objet générateur de temps
    bool continut;    // Indicateur de mouvement continu
    bool stopDuring;  // Indicateur d'arrêt pendant le mouvement

    // Fonctions membres privées
    bool stopHigh();  // Vérifie si la limite haute est atteinte
    bool stopLow();   // Vérifie si la limite basse est atteinte
    int move(int steps, int time); // Fait avencer le moteur avec une vitese indiquer
    void move(int steps); // Fais avencer le moteur avec une vites dinamique

  public:
    // Fonctions membres publiques
    void stepCounter(ESP8266WebServer&); // Effectue l'opération de comptage des pas
    Driver();                            // Constructeur

    void changePosition(int pos, int motorSpeedValue);        // Change la position du moteur
    bool isRotate();                     // Vérifie si le moteur n'est pas en rotation
};
#endif
