#ifndef MONEDERO_H
#define MONEDERO_H

#include <Arduino.h>

struct Moneda {
  int valor;      // En céntimos
  int cantidad;   // Disponibles en la hucha
};

// Variables globales
extern Moneda monedas[];
extern const int numTipos;

// Funciones
void calcularCambio(int cantidad, int usado[]);

#endif
