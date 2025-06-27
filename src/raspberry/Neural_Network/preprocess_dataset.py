import cv2
import numpy as np
import os

input_root = 'Raw_images'
output_root = 'Monedas_dataset/train'  # O val, o test

os.makedirs(output_root, exist_ok=True)

for class_name in os.listdir(input_root):
    input_class_dir = os.path.join(input_root, class_name)
    output_class_dir = os.path.join(output_root, class_name)
    os.makedirs(output_class_dir, exist_ok=True)

    for filename in os.listdir(input_class_dir):
        if not filename.lower().endswith(('.jpg', '.png', '.jpeg')):
            continue

        img_path = os.path.join(input_class_dir, filename)
        image = cv2.imread(img_path)
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        gray = cv2.medianBlur(gray, 5)

        circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, dp=1.2, minDist=100, param1=50, param2=30, minRadius=30, maxRadius=0)

        if circles is not None:
            x, y, r = np.uint16(np.around(circles))[0][0]
            mask = np.zeros_like(gray)
            cv2.circle(mask, (x, y), r, 255, -1)
            pad = 10
            x1 = max(x - r - pad, 0)
            y1 = max(y - r - pad, 0)
            x2 = min(x + r + pad, image.shape[1])
            y2 = min(y + r + pad, image.shape[0])
            cropped = image[y1:y2, x1:x2]
            cropped_mask = mask[y1:y2, x1:x2]
            result = cv2.bitwise_and(cropped, cropped, mask=cropped_mask)
            save_path = os.path.join(output_class_dir, filename)
            cv2.imwrite(save_path, result)
