# ESP32 RTC NTP & Deep Sleep Display

[![Blogger](https://img.shields.io/badge/Blogger-FF5722?style=for-the-badge&logo=blogger&logoColor=white)](https://thenerdyapprentice.blogspot.com/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg?style=for-the-badge)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-lightgrey.svg?style=for-the-badge)](https://www.espressif.com/en/products/socs/esp32)

Este proyecto implementa un reloj digital de alta precisión utilizando un ESP32, sincronización por red (NTP) y un modo de bajo consumo (Deep Sleep).

Puedes encontrar la explicación detallada y el tutorial completo en mi blog: [**The Nerdy Apprentice**](https://thenerdyapprentice.blogspot.com/).

## Características

- Sincronización NTP: Obtiene la hora exacta de internet al iniciar (Cold Boot).
- Reloj de Tiempo Real (RTC): Mantiene la hora internamente incluso durante el Deep Sleep.
- Deep Sleep: El dispositivo permanece apagado la mayor parte del tiempo, consumiendo microamperios.
- Activación por Botón (EXT0): Despierta instantáneamente al presionar un botón físico.
- Pantalla OLED SSD1306: Visualización clara de la hora y estado de conexión.
- Eficiencia Energética: Apaga el WiFi y el panel OLED antes de dormir.

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
