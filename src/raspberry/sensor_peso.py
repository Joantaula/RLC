from hx711 import HX711
from config import DT_PIN, SCK_PIN, REFERENCE_UNIT

def inicializar_hx711():
    hx = HX711(DT_PIN, SCK_PIN)
    hx.set_reading_format("MSB", "MSB")
    hx.set_reference_unit(REFERENCE_UNIT)
    hx.reset()
    hx.tare()
    print("HX711 tarado.")
    return hx

def leer_peso(hx, muestras=5):
    return hx.get_weight(muestras)
