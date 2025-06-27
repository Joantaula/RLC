# Pines motores
motor1_pins = [4, 17, 27, 22]
motor2_pins = [5, 6, 13, 26]

# Pines HX711
DT_PIN = 19
SCK_PIN = 21
REFERENCE_UNIT = -408.43

# Tamaño entrada del modelo
IMG_SIZE = (128, 128)

# Nombre del modelo
MODEL_PATH = "modelo_monedas.h5"

# Clases del modelo
CLASES = ['1cent', '2cent', '5cent', '10cent', '20cent', '50cent', '1eur', '2eur', 'no_coin']
