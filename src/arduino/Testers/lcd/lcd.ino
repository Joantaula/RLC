#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Usa la dirección que descubriste, por ejemplo: 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2); // (dirección, columnas, filas)

void setup() {
  lcd.init();               // Inicializa la pantalla
  lcd.backlight();          // Enciende la luz de fondo
  lcd.setCursor(0, 0);      // Coloca el cursor en la primera línea
  lcd.print("Hola Mundo!");
  lcd.setCursor(0, 1);      // Segunda línea
  lcd.print("Con Arduino :)");
}

void loop() {
  // No se necesita hacer nada aquí
}