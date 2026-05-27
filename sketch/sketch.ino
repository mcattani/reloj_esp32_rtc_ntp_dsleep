#include <WiFi.h>
#include "wifi_connect.h"
#include "display_utils.h"
#include "time_manager.h"

/*El compilador espera rigurosamente que su primer argumento sea un tipo de dato llamado gpio_num_t 
(un enumerador interno que define los pines del chip válidos)*/
const gpio_num_t PUSH_BUTTON = GPIO_NUM_27; 

// Definimos las variables para el contador millis()
unsigned long timeInit = 0;
const unsigned long timePowerOn = 10000;  // Segundos que permanece encendido

void setup() {
  Serial.begin(115200);

  // Inicializamos el display
  displayInit();

  // Leemos la causa de despertar
  esp_sleep_wakeup_cause_t sleep_cause = esp_sleep_get_wakeup_cause();

  // Siempre intentamos sincronizar al despertar para evitar el "drift" (desviación) del RTC interno
  if (sleep_cause == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Despertado por botón. Sincronizando para precisión...");
    displayStatus("Actualizando hora...");
  } else {
    Serial.println("Cold Boot / Reset manual. Iniciando sincronización...");
    displayStatus("Conectando WiFi...");
  }

  // Intentamos conectar y sincronizar
  if (setup_wifi()) {
    // Éxito: Mostramos información de red brevemente si es Cold Boot
    if (sleep_cause != ESP_SLEEP_WAKEUP_EXT0) {
      displayInfoNet(WiFi.SSID(), WiFi.localIP().toString());
      delay(1000);
    }

    displayStatus("Sincronizando NTP");

    if (syncTimeWithNTP()) {
      displayStatus("Sincronizado");
    } else {
      displayStatus("Error NTP");
    }
    
    // Una vez tenemos la hora, ya no necesitamos el WiFi
    disconnect_wifi();
  } else {
    // Fallo de WiFi: Mostramos error y seguimos con el RTC actual (aunque tenga drift)
    displayStatus("Error: No WiFi");
  }

  // Guardamos el momento en que termina el setup y arranca el loop (visualización)
  timeInit = millis();
}

void loop() {
  // Mientras no hayan pasado timePowerOn (10 seg.), refrescamos el display

  if (millis() - timeInit < timePowerOn) {
    // Leemos el RTC
    String horaActual = getFormattedTime();
    // Imprimimos en monitor Serie (depuración)
    Serial.print("Hora RTC: ");
    Serial.println(horaActual);

    // Mostramos en display
    displayTime(horaActual);

    // Actualizamos cada 1 seg
    delay(1000);
  } else {
    // Se cumplió el tiempo
    Serial.println("Tiempo cumplido. Apagando pantalla y entrando en modo Deep Sleep...");
    // Apagamos el display
    displayPowerOff();
    // Configuramos el despertar por Ext0 en el GPIO definido cuando pase a estado HIGH (1)
    esp_sleep_enable_ext0_wakeup(PUSH_BUTTON, 1);

    // Acivamos el modo deep sleep
    esp_deep_sleep_start();
  }
}
