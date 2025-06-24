# Cointer

Sistema de válvula/receptor de monedas automático para detección y dispensado óptimo de cambio, desarrollado como proyecto para la asignatura de Ingeniería Informática y Robótica.

---

## 📋 Descripción

Cointer es un robot que detecta monedas introducidas por el usuario, calcula el total disponible y devuelve el importe solicitado en la combinación de monedas óptima (algoritmo voraz), controlando tres motores paso a paso para dispensar las denominaciones de 2 €, 1 € y 0,50 €.

---

## 📊 Lista de componentes y presupuesto

| Componente                                                            | P. unitario (€) | Cantidad | Subtotal (€) |
| --------------------------------------------------------------------- | ---------------:| --------:| ------------:|
| Raspberry Pi 4 Model B 8 GB RAM                                       |           88,55 |        1 |         88,55 |
| I2C HX711                                                             |            4,95 |        1 |         4,95 |
| Cámara Raspberry Pi v2 – 8 Megapixels                                 |           19,95 |        1 |        19,95 |
| Pantalla LCD 20×4 con módulo I²C                                       |            7,95 |        1 |         7,95 |
| Motor paso a paso 28BYJ-48 (5 V) con driver ULN2003                   |            2,95 |       10 |        29,50 |
| Motor paso a paso NEMA 8 – 180 g/cm                                   |           27,60 |        1 |        27,60 |
| LED Luxeon RGB 3 W con base de aluminio                               |            5,90 |        1 |         5,90 |
| Teclado matricial de 12 botones                                       |            5,50 |        1 |         5,50 |
| Raspberry Pi Pico                                                      |            4,95 |        1 |         4,95 |
| Memoria MicroSD Kingston 128 GB (Clase 10)                            |           10,70 |        1 |        10,70 |
| Driver Pololu A4988 StepStick (Prusa/Reprap)                          |            6,60 |        1 |         6,60 |
| Célula de carga 5 kg con amplificador HX711                           |            4,10 |        1 |         4,10 |
| Fuente alimentación 4 salidas 5/12/−5/−12 125 W                       |           38,50 |        1 |        38,50 |
| **Total**                                                             |                 |          |      **254,75** |

> Consulta `Cointer_RLP_Budget 2.xlsx` para detalles de proveedores, enlaces y fechas de pedido.

---

## ⚙️ Características

- **Lectura de saldo**: muestra por Serial el total de euros disponible.  
- **Entrada de importe**: teclado matricial 4×4 para introducir cantidades con coma (‘*’).  
- **Algoritmo de cambio**: voraz con respaldo y reversión si no hay cambio exacto.  
- **Dispensado**: control de 3 motores (2 €, 1 €, 0,50 €) para entregar las monedas.  
- **Modularidad**: separa lógica de cálculo de cambio (Monedero) y control de motores (Motores).  

---

## 📦 Estructura de ficheros

```text
/  
├─ Monedero.h         
├─ Monedero.cpp       
├─ Motores.h          
├─ Motores.cpp        
├─ ControlDineroCompleto.ino  
├─ Cointer_RLP_Budget 2.xlsx   # Presupuesto detallado
└─ README.md          
```

## 🔧 Requisitos de hardware
Placa Arduino compatible (UNO, Nano, …)

Raspberry Pi 4 Model B 8 GB RAM (gestión avanzada/opcional)

3 drivers de motor paso a paso (A4988, DRV8825…)

3 motores paso a paso (2 €, 1 €, 0,50 €)

Teclado matricial 4×4 (pines D2–D9)

Célula de carga con HX711 (I2C)

Pantalla LCD 20×4 con I²C

Cámara Raspberry Pi v2 (reconocimiento de monedas, opcional)

Fuente de alimentación 5/12/−5/−12 V, 125 W

Cables y estructura mecánica


## 🛠️ Instalación y compilación
Abre el proyecto en el Arduino IDE (y en VS Code/Thonny para Pi, si lo usas).

Instala la librería Keypad desde el Gestor de Bibliotecas.

Copia los archivos .h, .cpp, el .ino y el .xlsx en la misma carpeta de sketch/repositorio.

Selecciona placa y puerto correctos.

Compila y sube al Arduino; en el Pi, lanza el script de visión si corresponde.



