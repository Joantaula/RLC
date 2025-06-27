#include <Keypad.h>
#include "Monedero.h"
#include "Motores.h"
#include "lcd.h"

const byte ROWS = 4; 
const byte COLS = 4; 


const char DISP_TOTAL = 'D';
const char RET_MONEY = 'R';

char state = DISP_TOTAL;

char key;


float calcularTotalMonedas() {
  int totalCents = 0;
  for (int i = 0; i < numTipos; i++) {
    totalCents += monedas[i].valor * monedas[i].cantidad;
  }
  return totalCents / 100.0;  // Convertimos a euros
}

void setup(){
  Serial.begin(9600);
  configurarMotores();
  lcd.init();
  lcd.backlight();
}

void loop(){
  
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Leer línea
    input.trim(); // Elimina espacios y saltos de línea

    int valor = input.toInt();  // Convertir a número

    // 2. Buscar si ese valor está en la colección
    bool encontrado = false;
    for (int i = 0; i < numTipos; i++) {
      if (monedas[i].valor == valor) {
        monedas[i].cantidad++;
        Serial.println("Moneda añadida: " + String(valor) + " cents");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Moneda: " + String(valor) + "c");
        lcd.setCursor(0, 1);
        lcd.print("Total: " + String(calcularTotalMonedas(), 2) + " EUR");
        encontrado = true;
        break;
      }
    }
  }
  float total_money = calcularTotalMonedas();
  switch (state){
    case DISP_TOTAL:
      Serial.println("Total: " + String(total_money));

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total: ");
      lcd.print(total_money, 2);  // 2 decimales
      lcd.setCursor(0, 1);
      lcd.print("Pulsa '#'");

      while(key != '#'){
        key = keypad.getKey();
      }
      state = RET_MONEY;

      break;
    case RET_MONEY:
      String input = "";
      Serial.println("Introduce cantidad: ");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cantidad:");

      key = NO_KEY;
      bool hasComa;
      int decimals;

      while (key != 'C'){
        key = keypad.getKey();
        hasComa = input.indexOf('.') != -1;

        if ((key >= '0' && key <= '9') || key == '*') {
          if (hasComa && key == '*'){
            Serial.println("Un numero solo puede tener una coma");
            lcd.setCursor(0, 1);
            lcd.print("Una sola coma  ");
            delay(1000);
            lcd.setCursor(0, 1);
            lcd.print("                ");
            continue;
          }
          if (hasComa){
            decimals = input.length() - input.indexOf('.');
            if (decimals > 2){
              Serial.println("No introduzcas mas de 2 decimales");
              lcd.setCursor(0, 1);
              lcd.print("Max 2 decimales");
              delay(1000);
              lcd.setCursor(0, 1);
              lcd.print("                ");
              continue;
            }
          }

          // Añadir carácter al input y mostrarlo
          input += (key == '*') ? '.' : key; 
          lcd.setCursor(0, 1);
          lcd.print("                "); // borrar línea
          lcd.setCursor(0, 1);
          lcd.print(input);
          Serial.println("Input actual: " + input);
        }

        else if (key == 'C'){
          float quantity = input.toFloat();
          int n_coins[8] = {0};

          if (input == ""){
            Serial.println("Introduce una cantidad");
            lcd.setCursor(0, 1);
            lcd.print("Vacio            ");
            delay(1000);
            lcd.setCursor(0, 1);
            lcd.print("                ");
          }
          else if (quantity < 0.01){   
            Serial.println("Introduce una cantidad valida");
            lcd.setCursor(0, 1);
            lcd.print("Cantidad invalida");
            delay(1000);
            lcd.setCursor(0, 1);
            lcd.print("                ");
          }
          else if (total_money - quantity >= 0){
            Serial.println("Cantidad a retirar: " + input);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Retirando:");
            lcd.setCursor(0, 1);
            lcd.print(input);

            int quantity_cents = round(quantity * 100);
            calcularCambio(quantity_cents, n_coins);
            moveMotors(n_coins[0], n_coins[1], n_coins[2], n_coins[3],
                      n_coins[4], n_coins[5], n_coins[6], n_coins[7], quantity);
            delay(3000);
            state = DISP_TOTAL;
          }
          else{
            Serial.println("Dinero insuficiente");
            lcd.setCursor(0, 1);
            lcd.print("Saldo insuf.     ");
            delay(1500);
            lcd.setCursor(0, 1);
            lcd.print("                ");
          }
        }

        else if (key == 'B'){
          state = DISP_TOTAL;
          break;
        }
      }
      

      break;
    default:
      break;
  }
}
