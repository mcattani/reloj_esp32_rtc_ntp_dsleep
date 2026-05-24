#include <WiFi.h>
#include "wifi_connect.h"
#include "display_utils.h"

void setup() {
  Serial.begin(115200);
  
  // Inicializamos el display
  displayInit();
  displayStatus("Conectando WiFi...");

  // Intentamos conectar y guardamos el resultado
  if (setup_wifi()) {
    // Éxito: Mostramos la IP en pantalla
    displayInfoNet(WiFi.SSID(), WiFi.localIP().toString());
  } else {
    // Fallo: Mostramos error en pantalla
    displayStatus("Error: No WiFi");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
