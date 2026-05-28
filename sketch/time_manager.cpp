#include <ESP32Time.h>
#include <esp_sntp.h> // Librería nativa para controlar el estado de sincronización
#include "time_manager.h"

// Configuramos servidos NTP
const char* ntpServer = "1.ar.pool.ntp.org";
const long gmtOffSet_sec = -10800;  // Valores para Argentina (UTC-3)
const int daylightOffset_sec = 0;

// Cremos un objeto del tipo ESP32Time
ESP32Time rtc(gmtOffSet_sec);

bool syncTimeWithNTP() {
  /* 
   * CONFIGURACIÓN DE SINCRONIZACIÓN:
   * SNTP_SYNC_MODE_IMMED: Fuerza a que el reloj interno se actualice instantáneamente
   * en cuanto llegue el paquete NTP, ignorando la hora "vieja" desfasada.
   */
  sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
  configTime(0, daylightOffset_sec, ntpServer);

  Serial.println("[NTP] Intentando sincronizar hora (UTC)...");

  /* 
   * EL PROBLEMA DEL DEEP SLEEP:
   * Al despertar, el ESP32 ya tiene una hora en su RTC interno (aunque esté desfasada).
   * Por eso, no podemos usar getLocalTime() para esperar, porque daría "true" de inmediato.
   * En su lugar, consultamos sntp_get_sync_status().
   */

  const int timeoutMs = 8000;  // 8 segundos de margen (reducido a petición del usuario)
  unsigned long startAttempt = millis();

  // Esperamos hasta que el estado sea "COMPLETED" (significa que llegó un paquete fresco del servidor)
  while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
    if (millis() - startAttempt > timeoutMs) {
      Serial.println("\n[NTP] Error: Tiempo de espera agotado (El servidor no respondió)");
      return false;
    }
    delay(500);
    Serial.print(".");
  }

  // Una vez confirmado que el sistema se actualizó, obtenemos la estructura de tiempo
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("\n[NTP] Error: Sincronizó pero no se pudo leer timeinfo");
    return false;
  }

  // Actualizamos nuestro objeto rtc con la hora exacta recién recibida
  rtc.setTimeStruct(timeinfo);
  Serial.println("\n[NTP] Sincronización exitosa y RTC calibrado.");
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
