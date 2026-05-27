#include <ESP32Time.h>
#include "time_manager.h"

// Configuramos servidos NTP
const char* ntpServer = "1.ar.pool.ntp.org";
const long gmtOffSet_sec = -10800;  // Valores para Argentina (UTC-3)
const int daylightOffset_sec = 0;

// Cremos un objeto del tipo ESP32Time
// Pasamos el offset en segundos directamente al constructor
// De esta manera, cada vez que despierte de Deep Sleep, se inicializará con UTC-3
ESP32Time rtc(gmtOffSet_sec);

bool syncTimeWithNTP() {
  /* 
   * IMPORTANTE: Configuramos configTime con offset 0 (UTC).
   * Dejamos que el hardware del ESP32 mantenga la hora en UTC.
   * El offset de la zona horaria (en nuestro caso -> Argentina -3) lo aplicará la librería ESP32Time
   * a través de su constructor 'rtc(gmtOffSet_sec)'. Esto evita el "doble offset"
   * al despertar de Deep Sleep.
   */
  configTime(0, daylightOffset_sec, ntpServer);

  Serial.println("[NTP] Intentando sincronizar hora (UTC)...");

  /*Extraemos la información de nuestro RTC interno en una estructura tm, 
  colocamos un if en caso de que el proceso falle. 
  Si todo salió bien tendremos en tm la fecha-hora de nuestro RTC interno actualizado. 
  Ahora debemos actualizar nuestra variable rtc utilizando la función setTimeStruct 
  y pasando como parámetro el tm con la información*/

  struct tm timeinfo;
  const int timeoutMs = 8000;  // Definimos un tiempo máximo de espera de 8 segundos
  unsigned long startAttempt = millis();

  // Bloqueamos el flujo temporalmente hasta que llegue la info del servidor
  while (!getLocalTime(&timeinfo)) {
    if (millis() - startAttempt > timeoutMs) {
      Serial.println("[NTP] Error: Tiempo de espera agotado");
      return false;
    }
    delay(100); // Reducimos a 100ms para capturar la respuesta más rápido
    Serial.print(".");
  }

  // Si el bucle terminó, significa que getLocalTime fue exitoso.
  // Ahora sí pasamos la estructura tm calibrada a la librería ESP32Time.
  // Actualizamos el RTC inmediatamente para no perder milisegundos
  rtc.setTimeStruct(timeinfo);
  Serial.println("\n[NTP] Sincronización exitosa con el servidor NTP.");
  return true;
}

String getFormattedTime() {
  // Retorna la hora en formato de 24 hs
  return rtc.getTime("%H:%M:%S");
}

String getFormattedDate() {
  // Retorna la fecha
  return rtc.getTime("%d/%m/%Y");
}
