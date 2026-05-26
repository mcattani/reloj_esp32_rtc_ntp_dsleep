#include <WiFi.h>
#include "wifi_connect.h"
#include "display_utils.h"
#include "time_manager.h"

void setup() {
  Serial.begin(115200);

  // Inicializamos el display
  displayInit();
  displayStatus("Conectando WiFi...");

  // Intentamos conectar y guardamos el resultado
  if (setup_wifi()) {
    // Éxito: Mostramos la IP en pantalla
    displayInfoNet(WiFi.SSID(), WiFi.localIP().toString());
    delay(1000);

    displayStatus("Sincronizando NTP");

    // Sincronizamos el RTC a través del servidor NTP solo si hay WiFi
    if (syncTimeWithNTP()) {
      displayStatus("Sincronizado NTP");
    } else {
      displayStatus("Error NTP");
    }
  } else {
    // Fallo de WiFi: Mostramos error en pantalla y seguimos con el RTC actual
    displayStatus("Error: No WiFi");
  }

  delay(2000);
}

void loop() {
  // Leemos el RTC
  String horaActual = getFormattedTime();

  // Imprimimos en monitor Serie (depuración)
  Serial.print("Hora RTC: ");
  Serial.println(horaActual);

  // Mostramos en display
  displayTime(horaActual);

  // Actualizamos cada 1 seg
  delay(1000);
}
