#pragma once
#include <Arduino.h>

/**
 * Inicializa la pantalla OLED SSD1306.
 * Configura el bus I2C y establece los parámetros iniciales del texto.
 */
void displayInit();

/**
 * Muestra un mensaje de estado en la pantalla.
 * Limpia la pantalla y escribe el mensaje con una etiqueta de "Estado:".
 * @param message El texto a mostrar.
 */
void displayStatus(String message);

/**
 * Muestra la hora actual formateada en la pantalla.
 * Utiliza un tamaño de fuente mayor para facilitar la lectura.
 * @param horas Hora (0-23).
 * @param minutos Minutos (0-59).
 * @param segundos Segundos (0-59).
 */
void displayTime(int horas, int minutos, int segundos);

/**
 * Muestra información de la red (SSID e IP).
 * @param ssid Nombre de la red WiFi.
 * @param ip Dirección IP asignada.
 */
void displayInfoNet(String ssid, String ip);

/**
 * Limpia la pantalla y apaga el panel OLED.
 * Útil para reducir el consumo antes de entrar en Deep Sleep.
 */
void displayPowerOff();
