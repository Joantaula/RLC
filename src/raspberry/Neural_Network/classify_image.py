import cv2
import numpy as np
import tensorflow as tf
import os

# Cargar modelo
model = tf.keras.models.load_model('coin_classifier.h5')
class_names = ['1cent', '2cent', '5cent', '10cent', '20cent', '50cent', '1eur', '2eur', 'no_coin']

# Función de preprocesado
def preprocess_image(image_path):
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.medianBlur(gray, 5)

    circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, dp=1.2, minDist=100, param1=50, param2=30, minRadius=30, maxRadius=0)

    if circles is not None:
        circles = np.uint16(np.around(circles))
        x, y, r = circles[0][0]
        mask = np.zeros_like(gray)
        cv2.circle(mask, (x, y), r, 255, thickness=-1)
        pad = 10
        x1 = max(x - r - pad, 0)
        y1 = max(y - r - pad, 0)
        x2 = min(x + r + pad, image.shape[1])
        y2 = min(y + r + pad, image.shape[0])
        cropped = image[y1:y2, x1:x2]
        mask_cropped = mask[y1:y2, x1:x2]
        result = cv2.bitwise_and(cropped, cropped, mask=mask_cropped)
        result = cv2.resize(result, (128, 128))
        result = result.astype('float32') / 255.0
        return result
    else:
        print(f"No se detectó círculo en {image_path}")
        return None

# Clasificar imagen
def classify(image_path):
    image = preprocess_image(image_path)
    if image is None:
        return
    image = np.expand_dims(image, axis=0)
    preds = model.predict(image)[0]
    idx = np.argmax(preds)
    print(f"{os.path.basename(image_path)} -> Predicción: {class_names[idx]} (confianza: {preds[idx]:.4f})")

# Ejemplo
classify('Monedas_dataset/test/2eur/Moneda15.jpg')
