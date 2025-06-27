import RPi.GPIO as GPIO
import time

step_sequence = [
    [1,0,0,0],
    [1,1,0,0],
    [0,1,0,0],
    [0,1,1,0],
    [0,0,1,0],
    [0,0,1,1],
    [0,0,0,1],
    [1,0,0,1]
]

def motor_continuo(pins, delay, stop_flag):
    step_index = 0
    step_count = len(step_sequence)
    next_step_time = time.perf_counter()
    while not stop_flag.is_set():
        now = time.perf_counter()
        if now >= next_step_time:
            step = step_sequence[step_index]
            for pin, val in zip(pins, step):
                GPIO.output(pin, val)
            step_index = (step_index + 1) % step_count
            next_step_time += delay

def mover_motor_ida_y_vuelta(pins, pasos=128, sentido=1, delay=0.001):
    seq = step_sequence if sentido == 1 else list(reversed(step_sequence))
    rev_seq = list(reversed(seq))

    for _ in range(pasos):
        for step in seq:
            for pin, val in zip(pins, step):
                GPIO.output(pin, val)
            time.sleep(delay)
    for _ in range(pasos):
        for step in rev_seq:
            for pin, val in zip(pins, step):
                GPIO.output(pin, val)
            time.sleep(delay)
