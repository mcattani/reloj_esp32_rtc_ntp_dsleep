#pragma once

// Se conecta al servidor NTP, obtiene la hora exacta y calibra el RTC interno del ESP32
// Devuelve true si la sincronización fue exitosa, false si falló por timeout
bool syncTimeWithNTP();

// Devuelve una cadena de texto formateada con la hora actual leída directamente del RTC
// Formato: "HH:MM:SS"
String getFormattedTime();

// Devuelve la fecha formateada ("DD/MM/YYYY")
String getFormattedDate();