import RPi.GPIO as GPIO
import time

# Definición de pines
motor1_pins = [4, 17, 27, 22]
motor2_pins = [5, 6, 13, 26]

# Secuencia estándar de medio paso para un motor 28BYJ-48
seq = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1]
]

def setup_motor(pins):
    for pin in pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, 0)

def move_motor(pins, steps=512, delay=0.002, direction=1):
    for i in range(steps):
        for j in range(8):
            for pin in range(4):
                GPIO.output(pins[pin], seq[(j * direction) % 8][pin])
            time.sleep(delay)

def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)

    setup_motor(motor1_pins)
    setup_motor(motor2_pins)

    try:
        print("Motor 1 adelante")
        move_motor(motor1_pins, steps=256, delay=0.002, direction=1)
        print("Motor 1 atrás")
        move_motor(motor1_pins, steps=256, delay=0.002, direction=-1)

        time.sleep(1)

        print("Motor 2 adelante")
        move_motor(motor2_pins, steps=256, delay=0.002, direction=1)
        print("Motor 2 atrás")
        move_motor(motor2_pins, steps=256, delay=0.002, direction=-1)

    finally:
        GPIO.cleanup()
        print("Limpieza de pines completada.")

if __name__ == "__main__":
    main()
