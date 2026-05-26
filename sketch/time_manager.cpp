#include <ESP32Time.h>
#include "time_manager.h"

// Cremos un objeto del tipo ESP32Time
ESP32Time rtc;

// Configuramos servidos NTP
const char* ntpServer = "1.ar.pool.ntp.org";
const long gmtOffSet_sec = -10800;  // Valores para Argentina (UTC-3)
const int daylightOffset_sec = 0;

bool syncTimeWithNTP() {
  // Configuramos el servidor y la zona horario en el core del ESP32
  // Esto inicia la solicitud UDP en segundo plano
  configTime(gmtOffSet_sec, daylightOffset_sec, ntpServer);

  Serial.println("[NTP] Intentando sincronizar hora...");

  /*Extraemos la información de nuestro RTC interno en una estructura tm, 
  colocamos un if en caso de que el proceso falle. 
  Si todo salió bien tendremos en tm la fecha-hora de nuestro RTC interno actualizado. 
  Ahora debemos actualizar nuestra variable rtc utilizando la función setTimeStruct 
  y pasando como parámetro el tm con la información*/

  struct tm timeinfo;
  const int timeoutMs = 8000;  // Definimos un tiempo máximo de espera de 8 segundos
  unsigned long startAttempt = millis();

  // Bloqueamos el flujo tempralmente hasta que llegue la info del servidor
  while (!getLocalTime(&timeinfo)) {
    // Si superamos el tiempo de espera, salimos para no bloquear infinitamente
    if (millis() - startAttempt > timeoutMs) {
      Serial.println("[NTP] Error: Tiempo de espera agotado");
      return false;
    }
    delay(500);
    Serial.print(".");
  }

  // Si el bucle terminó, significa que getLocalTime fue exitoso.
  // Ahora sí pasamos la estructura tm calibrada a la librería ESP32Time.
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
