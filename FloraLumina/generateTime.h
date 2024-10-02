#ifndef GENERATETIME_H
#define GENERATETIME_H



// Définition d'un itérateur personnalisé pour notre générateur
class GenerateTime {
public:
    // Constructeur prenant le seuil comme argument
    GenerateTime(int start, int destination, int motorSpeedValue);

    // Fonction pour initialiser l'itérateur
    void begin();

    // Fonction pour vérifier si nous avons atteint la fin de la séquence
    bool end();

    // Opérateur d'incrémentation de l'itérateur
    void next();

    // Opérateur de récupération de la valeur courante
    int value();

private:
    int current;              // Position actuelle
    int endAcceleration;      // Fin de l'accélération
    int startOfDecelerations; // Début de la décélération
    int minSpeed;   // Vitesse maximale et minimale
    int maxSpeed;
    int distance;
    double speed, steep;      // Vitesse et Pente
};



#endif