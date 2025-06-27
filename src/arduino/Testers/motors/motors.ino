#include <AccelStepper.h>

// Definición de los 8 motores
AccelStepper motor1(AccelStepper::FULL4WIRE, 22, 24, 23, 25);
AccelStepper motor2(AccelStepper::FULL4WIRE, 30, 32, 31, 33);
AccelStepper motor3(AccelStepper::FULL4WIRE, 26, 28, 27, 29);
AccelStepper motor4(AccelStepper::FULL4WIRE, 34, 36, 35, 37);
AccelStepper motor5(AccelStepper::FULL4WIRE, 50, 52, 51, 53);
AccelStepper motor6(AccelStepper::FULL4WIRE, 38, 40, 39, 41);
AccelStepper motor7(AccelStepper::FULL4WIRE, 46, 48, 47, 49);
AccelStepper motor8(AccelStepper::FULL4WIRE, 42, 44, 43, 45);

// Array de punteros a motores
AccelStepper* motores[] = {
  &motor1, &motor2, &motor3, &motor4,
  &motor5, &motor6, &motor7, &motor8
};

const int numMotores = 8;
const int pasos = 200;        // Número de pasos por giro (ajusta según motor)
const int velocidad = 200;    // Pasos por segundo
const int aceleracion = 100;  // Aceleración en pasos/s²

void setup() {
  Serial.begin(9600);

  // Configurar todos los motores
  for (int i = 0; i < numMotores; i++) {
    motores[i]->setMaxSpeed(velocidad);
    motores[i]->setAcceleration(aceleracion);
  }

  Serial.println("Inicio del test de motores...");
}

void loop() {
  for (int i = 0; i < numMotores; i++) {
    Serial.print("Moviendo motor ");
    Serial.println(i + 1);

    motores[i]->moveTo(pasos);
    while (motores[i]->distanceToGo() != 0) {
      motores[i]->run();
    }

    delay(500);

    motores[i]->moveTo(0);  // Volver a la posición original
    while (motores[i]->distanceToGo() != 0) {
      motores[i]->run();
    }

    delay(1000);  // Pausa antes de pasar al siguiente motor
  }

  Serial.println("Test completo. Reiniciando en 5s...");
  delay(5000);
}
