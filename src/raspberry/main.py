import RPi.GPIO as GPIO
import time
import threading

from config import motor1_pins, motor2_pins
from motor import motor_continuo, mover_motor_ida_y_vuelta
from sensor_peso import inicializar_hx711, leer_peso
from vision import capturar_imagen, clasificar

GPIO.setmode(GPIO.BCM)
for pin in motor1_pins + motor2_pins:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, 0)

hx = inicializar_hx711()

try:
    while True:
        peso_base = leer_peso(hx)
        print(f"Peso base: {peso_base:.2f} g")

        stop_flag = threading.Event()
        hilo_motor1 = threading.Thread(target=motor_continuo, args=(motor1_pins, 0.001, stop_flag))
        hilo_motor1.start()

        while True:
            peso_actual = leer_peso(hx)
            diferencia = abs(peso_actual - peso_base)
            print(f"Peso actual: {peso_actual:.2f} g | Dif: {diferencia:.2f}")
            if diferencia > 2:
                stop_flag.set()
                hilo_motor1.join()
                imagen = capturar_imagen()
                clase = clasificar(imagen)
                print(f"Clasificación: {clase}")
                sentido = 1 if clase != 'no_coin' else -1
                mover_motor_ida_y_vuelta(motor2_pins, pasos=128, sentido=sentido)
                break
            time.sleep(0.1)

except KeyboardInterrupt:
    print("\nPrograma interrumpido.")

finally:
    GPIO.cleanup()
