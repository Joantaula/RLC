import subprocess
import datetime
import os

def tomar_foto():
    # Crear nombre único para la foto con timestamp
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    nombre_foto = f"foto_test_{timestamp}.jpg"

    comando = [
        "libcamera-still",
        "-t", "1000",
        "--shutter", "10000",
        "--sharpness", "1.0",
        "--width", "1640",
        "--height", "1232",
        "-o", nombre_foto
    ]

    print("Tomando foto con la cámara...")
    try:
        resultado = subprocess.run(comando, check=True)
        print(f"✅ Foto tomada correctamente: {nombre_foto}")
    except subprocess.CalledProcessError as e:
        print("❌ Error al ejecutar libcamera-still")
        print(e)

if __name__ == "__main__":
    tomar_foto()
