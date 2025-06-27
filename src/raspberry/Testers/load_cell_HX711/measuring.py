import time
import RPi.GPIO as GPIO
from hx711 import HX711

# Pines usados (ajusta si usas otros)
DT_PIN = 19
SCK_PIN = 21

# Cambia este valor por el reference_unit calculado en la calibracion
REFERENCE_UNIT = -408.43

def medir_peso():
    hx = HX711(DT_PIN, SCK_PIN)
    hx.set_reading_format("MSB", "MSB")
    hx.set_reference_unit(REFERENCE_UNIT)

    hx.reset()
    hx.tare()
    print("Balanza tarada. Coloca un objeto para medir su peso.")

    try:
        while True:
            peso = hx.get_weight(5)
            print(f"Peso: {peso:.2f} g")
            hx.power_down()
            hx.power_up()
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nMedicion detenida por usuario.")
        GPIO.cleanup()

if __name__ == "__main__":
    medir_peso()
