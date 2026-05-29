# ESP32 RTC NTP & Deep Sleep Display

[![Blogger](https://img.shields.io/badge/Blogger-FF5722?style=for-the-badge&logo=blogger&logoColor=white)](https://thenerdyapprentice.blogspot.com/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg?style=for-the-badge)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-lightgrey.svg?style=for-the-badge)](https://www.espressif.com/en/products/socs/esp32)

Este proyecto se propone implementar un reloj digital utilizando un ESP32, el RTC incluido en el mismo, sincronización por red (NTP) y un modo de bajo consumo (Deep Sleep).

![Imagen proyecto](https://i.ibb.co/0ygCyb2S/20260527-175541.jpg)

Puedes encontrar más información en mi blog: [**The Nerdy Apprentice**](https://thenerdyapprentice.blogspot.com/).

## Características

- Sincronización NTP: Obtiene la hora exacta de internet en cada despertar para asegurar precisión total.
- Reloj de Tiempo Real (RTC): Mantiene la hora internamente durante el Deep Sleep (usado como respaldo si falla el WiFi).
- Deep Sleep: El dispositivo permanece apagado la mayor parte del tiempo, consumiendo microamperios.
- Activación por Botón (EXT0): Despierta al presionar un botón físico para mostrar la hora.
- Pantalla OLED SSD1306: Visualización clara de la hora y mensajes de estado.
- Gestión de Drift: Corrige automáticamente la desviación natural del oscilador interno del ESP32.

## El problema del "Time Drift" (Desviación Temporal)

Durante el desarrollo de este proyecto, se identificó que el RTC interno del ESP32 (específicamente el oscilador RC de 150kHz) tiene una desviación significativa cuando funciona de forma autónoma durante el Deep Sleep. En pruebas de varias horas, el reloj puede adelantarse o retrasarse varios minutos debido a:
1. Inestabilidad térmica del oscilador RC interno.
2. Falta de un cristal de cuarzo externo de 32.768 kHz en la mayoría de las placas de desarrollo.

**Solución implementada:** Para garantizar que el usuario siempre vea la hora correcta al presionar el botón, el código ahora realiza una sincronización NTP rápida en cada despertar. Aunque esto aumenta ligeramente el consumo de batería por cada consulta, asegura que el dispositivo funcione como un reloj confiable.

## Requisitos de Hardware

- ESP32 (ej: DOIT DevKit V1, NodeMCU-32S, etc.)
- Display OLED SSD1306 (128x64, I2C)
- Pulsador (Push Button)
- Resistencia de 10kΩ (Pull-down)
- Batería o Fuente de Alimentación: Se recomienda alimentar vía pin 5V/VIN.

## Estructura del Proyecto

- `sketch/sketch.ino`: Lógica principal (gestión de estados y sueño).
- `sketch/time_manager.cpp/h`: Sincronización NTP y gestión del RTC interno.
- `sketch/wifi_connect.cpp/h`: Conectividad WiFi y mDNS.
- `sketch/display_utils.cpp/h`: Controladores de la pantalla OLED.
- `sketch/config_example.h`: Plantilla para credenciales (debe renombrarse a `config.h`).

## Configuración e Instalación

1. **Librerías Necesarias:** Instala las siguientes librerías desde el Gestor de Librerías de Arduino:
   - `ESP32Time` (por fbiego)
   - `Adafruit SSD1306`
   - `Adafruit GFX Library`

2. **Configuración de Red:**
   - Renombra `sketch/config_example.h` a `sketch/config.h`.
   - Edita `sketch/config.h` con tu SSID y Password de WiFi.

3. **Conexiones:**
   - **OLED:** SDA -> GPIO 21, SCL -> GPIO 22.
   - **Botón:** Pin 27 -> (Pulsador) -> 3.3V.
   - **Resistencia:** Conectar una resistencia de **10kΩ** entre el Pin 27 y GND (Pull-down) para asegurar lecturas estables.

## Notas sobre Alimentación

Para una máxima seguridad, se recomienda alimentar el proyecto a través del pin **5V (VIN)**. Esto permite que el regulador de voltaje de la placa estabilice la entrada (especialmente útil con baterías de Litio que cargadas superan los 4V), evitando daños al ESP32 y eliminando la necesidad de convertidores elevadores (Boost) externos que reducirían la eficiencia.

## Licencia

Este proyecto está bajo la licencia **GNU General Public License v3.0 (GPL-3.0)**. Consulta el archivo `LICENSE` para más detalles.
