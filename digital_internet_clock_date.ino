// ===== MAX7219 32 x 8 : 4 in 1 & ESP32 CP2102 Pin Diagram =====
// VCC --> V5 (kanan)
// GND --> GND (kanan)
// DIN --> G23 (kiri)
// CS --> G5 (kiri)
// CLK --> G18 (kiri)

#include <WiFi.h>
#include <time.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// ===== WIFI =====
const char* ssid     = "Acanma";
const char* password = "dutdutdut";

// ===== NTP =====
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600;
const int   daylightOffset_sec = 0;

// ===== MAX7219 =====
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5

MD_Parola display(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// ===== BUFFER =====
char timeBuf[6];     // HH:MM
char dateBuf[20];    // 22 JAN 2024

// ===== TIMER =====
unsigned long lastDateShow = 0;

// ===== MODE =====
enum Mode { MODE_JAM, MODE_TANGGAL };
Mode currentMode = MODE_JAM;

// ===== NAMA BULAN =====
const char* bulan[] = {
  "JAN","FEB","MAR","APR","MEI","JUN",
  "JUL","AGS","SEP","OKT","NOV","DES"
};

void setup() {
  Serial.begin(115200);

  display.begin();
  display.setIntensity(5);
  display.setCharSpacing(1);
  display.displayClear();
  display.setZoneEffect(0, true, PA_FLIP_LR);
  display.setZoneEffect(0, true, PA_FLIP_UD);

  display.displayText("WIFI...", PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(300);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) delay(300);

  display.displayClear();
  lastDateShow = millis();
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  unsigned long now = millis();

  // ===== MODE JAM =====
  if (currentMode == MODE_JAM) {

    // colon berkedip berdasarkan detik NTP
    char colon = (timeinfo.tm_sec % 2 == 0) ? ':' : ' ';

    sprintf(timeBuf, "%02d%c%02d",
            timeinfo.tm_hour,
            colon,
            timeinfo.tm_min);

    display.displayText(
      timeBuf,
      PA_CENTER,
      0,
      0,
      PA_PRINT,
      PA_NO_EFFECT
    );

    // tiap 20 detik → tanggal
    if (now - lastDateShow >= 20000) {
      lastDateShow = now;
      currentMode = MODE_TANGGAL;

      sprintf(dateBuf, "%02d %s %04d",
              timeinfo.tm_mday,
              bulan[timeinfo.tm_mon],
              timeinfo.tm_year + 1900);

      display.displayClear();
      display.displayText(
        dateBuf,
        PA_LEFT,
        60,
        0,
        PA_SCROLL_RIGHT,
//        PA_NO_EFFECT,     
        PA_SCROLL_RIGHT
      );
    }
  }

  // ===== MODE TANGGAL =====
  else if (currentMode == MODE_TANGGAL) {
    if (display.displayAnimate()) {
      // setelah teks benar-benar keluar kiri
      display.displayClear();
      currentMode = MODE_JAM;

      // jam masuk dengan efek slide-down
      display.displayText(
        timeBuf,
        PA_CENTER,
        40,
        0,
        PA_SLICE,
        PA_NO_EFFECT
      );
    }
  }

  display.displayAnimate();
}
