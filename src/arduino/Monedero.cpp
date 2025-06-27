#include "Monedero.h"

// Definición de las monedas
Moneda monedas[] = {
  {200, 0},  // 2 euros
  {100, 0},  // 1 euro
  {50, 0},   // 50 cents
  {20, 0},   // 20 cents
  {10, 0},   // 10 cents
  {5, 0},    // 5 cents
  {2, 0},    // 2 cents
  {1, 0}     // 1 cent
};

const int numTipos = sizeof(monedas) / sizeof(Moneda);

void calcularCambio(int cantidad, int usado[]) {
  int original = cantidad;
  for (int i = 0; i < numTipos; i++) {
    while (cantidad >= monedas[i].valor && monedas[i].cantidad > 0) {
      cantidad -= monedas[i].valor;
      monedas[i].cantidad--;
      usado[i]++;
    }
  }

  if (cantidad == 0) {
    Serial.print("Cambio para ");
    Serial.print(original / 100.0, 2);
    Serial.println(" €:");

    for (int i = 0; i < numTipos; i++) {
      if (usado[i] > 0) {
        Serial.print(" - ");
        Serial.print(usado[i]);
        Serial.print(" moneda(s) de ");
        Serial.print(monedas[i].valor / 100.0, 2);
        Serial.println(" €");
      }
    }
  } else {
    Serial.println("No se puede devolver el cambio exacto con las monedas disponibles.");
    
    // Revertimos los cambios en caso de fallo
    for (int i = 0; i < numTipos; i++) {
      monedas[i].cantidad += usado[i];
    }
  }
}
