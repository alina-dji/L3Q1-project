/**
 * @file generateTime.cpp
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "generateTime.h"

/**
 * @brief Constructeur prenant la position de départ, la position de destination et la valeur maximale comme arguments
 * 
 * @param start 
 * @param destination 
 * @param motorSpeedValue 
 */
GenerateTime::GenerateTime(int start, int destination, int motorSpeedValue){
  current = 0;                      // Initialise la position actuelle à 0
  maxSpeed = motorSpeedValue;                    // Initialise la vitesse maximale à 20
  minSpeed = 150;                   // Initialise la vitesse minimale à 150
  speed = minSpeed;                 // Initialise la vitesse actuelle à la vitesse minimale
  distance = (start<destination) ? destination-start : start-destination;   // Calcul de la distance totale à parcourir
  endAcceleration = distance/8;     // Calcul de la fin de l'accélération
  startOfDecelerations = distance- endAcceleration; // Calcul du début de la décélération
  
  steep = 0.02;                     // Initialise la pente

}
/**
 * @brief Fonction pour vérifier si nous avons atteint la fin de la séquence
 * 
 * @return true 
 * @return false 
 */
bool GenerateTime::end(){
  return !(current < distance);     // Renvoie vrai si la position actuelle est supérieure ou égale à la distance totale
}
/**
 * @brief Fonction pour incrémenter l'itérateur
 * 
 */
void GenerateTime::next(){
  if(current <= endAcceleration){
     speed -=  steep;               // Augmente la vitesse pendant la phase de d'accélération
  }
  if(current >= startOfDecelerations){
    speed += steep;                 // Réduit la vitesse pendant la phase décélération
  }
  speed = (speed<maxSpeed) ? maxSpeed : speed;    // Limite la vitesse maximale
  speed = (speed>minSpeed) ? minSpeed : speed;    // Limite la vitesse minimale
  current++;
}
/**
 * @brief Fonction pour récupérer la valeur courante (vitesse)
 * 
 * @return int 
 */
int GenerateTime::value(){
  return (int)speed;                // Fonction pour récupérer la valeur courante (vitesse)
} 

