import subprocess
import io
from PIL import Image
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array
import numpy as np
from config import IMG_SIZE, MODEL_PATH, CLASES

modelo = load_model(MODEL_PATH)

def capturar_imagen(path="/tmp/foto.jpg"):
    comando = [
        "libcamera-still",
        "-t", "1000",
        "--shutter", "10000",
        "--sharpness", "1.0",
        "--width", "1640",
        "--height", "1232",
        "-o", path
    ]
    subprocess.run(comando, check=True)
    with open(path, "rb") as f:
        img = Image.open(io.BytesIO(f.read()))
    return img

def clasificar(imagen):
    imagen = imagen.resize(IMG_SIZE)
    imagen = img_to_array(imagen) / 255.0
    imagen = np.expand_dims(imagen, axis=0)
    pred = modelo.predict(imagen)[0]
    return CLASES[np.argmax(pred)]
