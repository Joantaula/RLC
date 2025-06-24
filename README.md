# Cointer

Sistema de válvula/receptor de monedas automático para detección y dispensado óptimo de cambio, desarrollado como proyecto para la asignatura de Ingeniería Informática y Robótica.

---

## 📋 Descripción

Cointer es un robot que detecta monedas introducidas por el usuario, calcula el total disponible y devuelve el importe solicitado en la combinación de monedas óptima (algoritmo voraz), controlando tres motores paso a paso para dispensar las denominaciones de 2 €, 1 € y 0,50 €.

---

## ⚙️ Características

- **Lectura de saldo**: muestra por Serial el total de euros disponible.
- **Entrada de importe**: teclado matricial 4×4 para introducir cantidades con coma (‘*’).
- **Algoritmo de cambio**: voraz con respaldo y reversión si no hay cambio exacto.
- **Dispensado**: control de motores para entregar las monedas.
- **Modularidad**: separa lógica de cálculo de cambio (Monedero) y control de motores (Motores).

---

## 📦 Estructura de ficheros

```text
/  
├─ Monedero.h         # Definición de tipos y cálculo de cambio  
├─ Monedero.cpp       # Implementación del algoritmo voraz y reversión  
├─ Motores.h          # API para configurar y mover motores  
├─ Motores.cpp        # (Módulo ya validado) control de motores paso a paso  
├─ ControlDineroCompleto.ino  
└─ README.md          # Este documento
```

## 🔧 Requisitos de hardware
Placa Arduino compatible (UNO, Nano, …)

N drivers de motor paso a paso (e.g. A4988, DRV8825)

N motores paso a paso (uno por denominación: 2 €, 1 €, 0,50 €...)

Teclado matricial 4×4 (pins D2–D9)

Cables y fuente de alimentación adecuada para los motores
