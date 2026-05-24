#include "display_utils.h"

// Librerías de Adafruit para el manejo del display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dimensiones de la pantalla SSD1306 (128x64 píxeles)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// El pin de reset no se usa en la mayoría de estos módulos (usamos -1)
#define OLED_RESET -1
// Dirección I2C típica: 0x3C para la mayoría de pantallas 128x64
#define SCREEN_ADDRESS 0x3C

// Instancia del objeto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayInit() {
  // Pequeña pausa para asegurar que el display esté energizado
  delay(100);

  // Inicializa
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error: No se pudo encontrar el display SSD1306"));
    // Si falla, el programa se detiene aquí para depuración
    for (;;) ;
  }

  // Configuración inicial por defecto
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void displayStatus(String message) {
  display.clearDisplay();
  
  // Encabezado
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Estado:");
  
  // Mensaje principal
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.println(message);
  
  // Enviar buffer a la pantalla
  display.display();
}

void displayTime(int horas, int minutos, int segundos) {
  display.clearDisplay();
  display.setTextSize(2); // Fuente grande (aprox 14px de alto)
  display.setCursor(15, 25); // Centrado aproximado

  // Formateo manual para añadir ceros a la izquierda (01:05:09)
  if (horas < 10) display.print('0');
  display.print(horas);
  display.print(':');
  
  if (minutos < 10) display.print('0');
  display.print(minutos);
  display.print(':');
  
  if (segundos < 10) display.print('0');
  display.print(segundos);
  
  display.display();
}

void displayInfoNet(String ssid, String ip) {
  display.clearDisplay();
  
  // Línea superior (Zona amarilla)
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("WiFi: ");
  display.println(ssid);
  
  // Línea decorativa divisoria
  display.drawFastHLine(0, 14, 128, SSD1306_WHITE);
  
  // Información de IP (Zona azul)
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("Direccion IP:");
  
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println(ip);
  
  display.display();
}

void displayPowerOff() {
    display.clearDisplay();
    display.display(); // Borra lo que haya antes de apagar
    
    // Envía el comando de hardware para apagar el panel y ahorrar batería
    display.ssd1306_command(SSD1306_DISPLAYOFF); 
}
