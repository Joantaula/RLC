#ifndef MOTORES_H
#define MOTORES_H

#include <AccelStepper.h>

// Declaración de los motores y posiciones
extern AccelStepper motor1;
extern AccelStepper motor2;
extern AccelStepper motor3;
extern AccelStepper motor4;
extern AccelStepper motor5;
extern AccelStepper motor6;
extern AccelStepper motor7;
extern AccelStepper motor8;

extern const long posA;
extern const long posB;

// Declaración de la función
void configurarMotores(); // inicializa velocidad y aceleración
void moveMotors(int total_2eur, int total_1eur, int total_50cent, int total_20cent, int total_10cent, int total_5cent, int total_2cent, int total_1cent, float total);

#endif
