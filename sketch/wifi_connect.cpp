#include "wifi_connect.h"
#include "config.h"

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Bucle mientras se conecta
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  // Conexión exitosa -> mostramos los datos de conexión
  Serial.println("");
  Serial.println("WiFi Conectado!");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  // mDNS
  if (!MDNS.begin(MDNS_NAME)) {  // Seteamos el hostname
    Serial.println("Error iniciando mDNS");
    return;
  }

  // Mostramos los datos de mDNS
  Serial.print("mDNS iniciado: http://");
  Serial.print(MDNS_NAME);
  Serial.println(".local");
}
