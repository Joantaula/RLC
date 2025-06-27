#include "Motores.h"

// Definición de los motores y posiciones
// Definición de los motores y posiciones
AccelStepper motor1(AccelStepper::FULL4WIRE, 22, 24, 23, 25);
AccelStepper motor2(AccelStepper::FULL4WIRE, 30, 32, 31, 33);
AccelStepper motor3(AccelStepper::FULL4WIRE, 26, 28, 27, 29);
AccelStepper motor4(AccelStepper::FULL4WIRE, 34, 36, 35, 37);
AccelStepper motor5(AccelStepper::FULL4WIRE, 50, 52, 51, 53);
AccelStepper motor6(AccelStepper::FULL4WIRE, 38, 40, 39, 41);
AccelStepper motor7(AccelStepper::FULL4WIRE, 46, 48, 47, 49);
AccelStepper motor8(AccelStepper::FULL4WIRE, 42, 44, 43, 45); 

const long posA = 0;
const long posB = 1024;

void configurarMotores() {
  AccelStepper* motores[] = {&motor1, &motor2, &motor3, &motor4, &motor5, &motor6, &motor7, &motor8};
  for (int i = 0; i < 8; i++) {
    motores[i]->setMaxSpeed(200);
    motores[i]->setSpeed(200);
    motores[i]->setAcceleration(10000);
  }
}

void moveMotors(int total_2eur, int total_1eur, int total_50cent, int total_20cent, int total_10cent, int total_5cent, int total_2cent, int total_1cent, float total) {
  motor1.moveTo(posB);
  motor2.moveTo(posB);
  motor3.moveTo(posB);
  motor4.moveTo(posB);
  motor5.moveTo(posB);
  motor6.moveTo(posB);
  motor7.moveTo(posB);
  motor8.moveTo(posB);

  float returned = 0;
  int returned_2eur = 0, returned_1eur = 0, returned_50cent = 0, returned_20cent = 0, returned_10cent = 0, returned_5cent = 0, returned_2cent = 0, returned_1cent = 0;

  while (returned < total) {
    if (returned_2eur < total_2eur) {
      if (motor1.distanceToGo() == 0) {
        if (motor1.currentPosition() == posB) {
          motor1.moveTo(posA);
        } else {
          returned += 2.0;
          returned_2eur++;
          motor1.moveTo(posB);
        }
      }
      motor1.run();
    }

    if (returned_1eur < total_1eur) {
      if (motor2.distanceToGo() == 0) {
        if (motor2.currentPosition() == posB) {
          motor2.moveTo(posA);
        } else {
          returned += 1.0;
          returned_1eur++;
          motor2.moveTo(posB);
        }
      }
      motor2.run();
    }

    if (returned_50cent < total_50cent) {
      if (motor3.distanceToGo() == 0) {
        if (motor3.currentPosition() == posB) {
          motor3.moveTo(posA);
        } else {
          returned += 0.5;
          returned_50cent++;
          motor3.moveTo(posB);
        }
      }
      motor3.run();
    }

    if (returned_20cent < total_20cent) {
      if (motor4.distanceToGo() == 0) {
        if (motor4.currentPosition() == posB) {
          motor4.moveTo(posA);
        } else {
          returned += 0.2;
          returned_20cent++;
          motor4.moveTo(posB);
        }
      }
      motor4.run();
    }

    if (returned_10cent < total_10cent) {
      if (motor5.distanceToGo() == 0) {
        if (motor5.currentPosition() == posB) {
          motor5.moveTo(posA);
        } else {
          returned += 0.1;
          returned_10cent++;
          motor5.moveTo(posB);
        }
      }
      motor5.run();
    }

    if (returned_5cent < total_5cent) {
      if (motor6.distanceToGo() == 0) {
        if (motor6.currentPosition() == posB) {
          motor6.moveTo(posA);
        } else {
          returned += 0.05;
          returned_5cent++;
          motor6.moveTo(posB);
        }
      }
      motor6.run();
    }

    if (returned_2cent < total_2cent) {
      if (motor7.distanceToGo() == 0) {
        if (motor7.currentPosition() == posB) {
          motor7.moveTo(posA);
        } else {
          returned += 0.02;
          returned_2cent++;
          motor7.moveTo(posB);
        }
      }
      motor7.run();
    }

    if (returned_1cent < total_1cent) {
      if (motor8.distanceToGo() == 0) {
        if (motor8.currentPosition() == posB) {
          motor8.moveTo(posA);
        } else {
          returned += 0.01;
          returned_1cent++;
          motor8.moveTo(posB);
        }
      }
      motor8.run();
    }
  }
}
