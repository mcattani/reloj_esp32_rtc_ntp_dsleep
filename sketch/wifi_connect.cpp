#include "wifi_connect.h"
#include "config.h"

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>

bool setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Intentar conectar durante un máximo de 20 intentos (aprox 10 seg)
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // mDNS
    if (!MDNS.begin(MDNS_NAME)) {
      Serial.println("Error iniciando mDNS");
    } else {
      Serial.print("mDNS: http://");
      Serial.print(MDNS_NAME);
      Serial.println(".local");
    }
    return true; // Éxito
  } else {
    Serial.println("\nError: Tiempo de espera agotado.");
    return false; // Fallo
  }
}
