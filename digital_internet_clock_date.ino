// ===== MAX7219 32 x 8 : 4 in 1 & ESP32 CP2102 Pin Diagram =====
// VCC --> V5 (kanan)
// GND --> GND (kanan)
// DIN --> G23 (kiri)
// CS --> G5 (kiri)
// CLK --> G18 (kiri)

// ===== Passive Buzzer Pin Diagram =====
// GND --> GND (kiri)
// I/O --> G25 (kanan)
// VCC --> 3V3 (Kanan)

//| Modul   | Fungsi | GPIO   | Ambil dari |
//| ------- | ------ | ------ | ---------- |
//| MAX7219 | DIN    | GPIO23 | **Kiri**   |
//| MAX7219 | CS     | GPIO5  | **Kiri**   |
//| MAX7219 | CLK    | GPIO18 | **Kiri**   |
//| MAX7219 | VCC    | 5V     | **Kiri**   |
//| MAX7219 | GND    | GND    | **Kiri**   |
//| Buzzer  | I/O    | GPIO25 | **Kiri**   |
//| Buzzer  | VCC    | 3.3V   | **Kiri**   |
//| Buzzer  | GND    | GND    | **Kiri**   |

//| Modul   | Fungsi | GPIO   | Ambil dari |
//| ------- | ------ | ------ | ---------- |
//| MAX7219 | DIN    | GPIO23 | **Kanan**  |
//| MAX7219 | CS     | GPIO5  | **Kanan**  |
//| MAX7219 | CLK    | GPIO18 | **Kanan**  |
//| MAX7219 | VCC    | 5V     | **Kanan**  |
//| MAX7219 | GND    | GND    | **Kanan**  |
//| Buzzer  | I/O    | GPIO25 | **Kanan**  |
//| Buzzer  | VCC    | 3.3V   | **Kanan**  |
//| Buzzer  | GND    | GND    | **Kanan**  |

#include <WiFi.h>
#include <time.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include <WebServer.h>

WebServer server(80);

// ================= TAKE ON ME =================
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 360;

//int melody[] = {
//
//  // Take on me, by A-ha
//  // Score available at https://musescore.com/user/27103612/scores/4834399
//  // Arranged by Edward Truong
//
//  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
//  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
//  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
//  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
//  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
//  
//  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
//  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
//  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
//  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
//  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
//  
//  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
//  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
//  
//};

int melody[] = {
  NOTE_FS5,8, NOTE_FS5,8, NOTE_D5,8, NOTE_B4,8, REST,8, 
  NOTE_B4,8, REST,8, 
  NOTE_E5,8, REST,8, 
  NOTE_E5,8, REST,8, 
  NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8, NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, 
  NOTE_D5,8, REST,8, 
  NOTE_FS5,8, REST,8, 
  NOTE_FS5,8, REST,8, 
  NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, 
};

// ================= SERIAL =================
#define SERIAL_BAUD 115200

// ===== ALARM =====
bool alarmEnabled = false;
int alarmHour = 6;
int alarmMinute = 0;
bool alarmTriggered = false;

// ===== MANUAL TIME =====
bool manualTime = false;
int setHour, setMinute;

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

// ===== BUZZER =====
#define BUZZER_PIN 25
#define BUZZER_CH  0

// ===== BUFFER =====
char timeBuf[6];     // HH:MM
char dateBuf[25];    // 22 JAN 2024

// ===== TIMER =====
unsigned long lastDateShow = 0;

// ===== MODE =====
enum Mode { MODE_JAM, MODE_TANGGAL };
Mode currentMode = MODE_JAM;

// ===== LAST TIME =====
int lastMinute = -1;
int lastHour   = -1;

// ===== NAMA BULAN =====
const char* bulan[] = {
  "JAN","FEB","MAR","APR","MEI","JUN",
  "JUL","AGS","SEP","OKT","NOV","DES"
};

// ===== NAMA HARI =====
const char* hari[] = {
  "MIN","SEN","SEL","RAB","KAM","JUM","SAB"
};

// ===== FUNGSI BUZZER =====
void beep(int freq, int dur) {
  ledcWriteTone(BUZZER_CH, freq);
  delay(dur);
  ledcWriteTone(BUZZER_CH, 0);
}



// ===== WEB VIEW SETTING =====

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Clock</title>
<style>
body { font-family: Arial; background:#111; color:#0f0; text-align:center; }
input, button { font-size:18px; margin:5px; padding:5px; }
.card { border:1px solid #0f0; padding:15px; margin:10px; }
</style>
</head>
<body>

<h2>⏰ ESP32 JAM DIGITAL</h2>

<div class="card">
<h3>Set Jam Manual</h3>
<form action="/settime">
Jam <input type="number" name="h" min="0" max="23">
Menit <input type="number" name="m" min="0" max="59">
<br>
<button type="submit">SET JAM</button>
</form>
</div>

<div class="card">
<h3>Alarm</h3>
<form action="/setalarm">
Jam <input type="number" name="ah" min="0" max="23">
Menit <input type="number" name="am" min="0" max="59">
<br>
<button type="submit">SET ALARM</button>
</form>

<form action="/alarmon">
<button>ALARM ON</button>
</form>

<form action="/alarmoff">
<button>ALARM OFF</button>
</form>
</div>

</body>
</html>
)rawliteral";

// ================= WEB HANDLER =================

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void handleSetTime() {
  if (server.hasArg("h") && server.hasArg("m")) {
    setHour = server.arg("h").toInt();
    setMinute = server.arg("m").toInt();
    manualTime = true;
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSetAlarm() {
  if (server.hasArg("ah") && server.hasArg("am")) {
    alarmHour = server.arg("ah").toInt();
    alarmMinute = server.arg("am").toInt();
    alarmTriggered = false;
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleAlarmOn() {
  alarmEnabled = true;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleAlarmOff() {
  alarmEnabled = false;
  alarmTriggered = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

void jamMelodyCute() {
  int melody[] = {
    988,   // B5
    1046,  // C6
    1318,  // E6
    1046,  // C6
    1568   // G6
  };

  int dur[] = {80, 80, 80, 80, 160};

  for (int i = 0; i < 5; i++) {
    beep(melody[i], dur[i]);
    delay(40);
  }
}

void playTakeOnMe() {
  int notes = sizeof(melody) / sizeof(melody[0]);

  // hitung durasi not dasar dari tempo BPM
  int wholeNote = (60000 * 4) / tempo;

  for (int i = 0; i < notes; i++) {

    int noteDuration = wholeNote / 8; // semua not = 1/4 beat

    if (melody[i] != 0) {
      tone(BUZZER_PIN, melody[i], noteDuration);
    }

    delay(noteDuration * 1.3);
    noTone(BUZZER_PIN);
  }
}

// ===== SETUP =====

void setup() {
  //  Serial.begin(115200);
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  Serial.println("\n=== ESP32 BOOT OK ===");

  display.begin();
  display.setIntensity(1);
  display.setCharSpacing(1);
  display.displayClear();
  display.setZoneEffect(0, true, PA_FLIP_LR);
  display.setZoneEffect(0, true, PA_FLIP_UD);

  // ===== BUZZER INIT =====
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);
  ledcSetup(BUZZER_CH, 2000, 8);
  beep(1500, 100);

  display.displayText("WIFI...", PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT);

  //  WiFi.begin(ssid, password);
  //  while (WiFi.status() != WL_CONNECTED) delay(300);
  //
  //  Serial.print("IP ESP32: ");
  //  Serial.println(WiFi.localIP());

  // WIFI
  Serial.print("Connecting WiFi");
  WiFi.begin(ssid, password);

  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi OK");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    display.displayText("ONLINE", PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT);
  } else {
    Serial.println("\nWiFi FAILED");
    display.displayText("NO WIFI", PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT);
  }

  // NTP (NON BLOCKING)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //  struct tm timeinfo;
  //  while (!getLocalTime(&timeinfo)) delay(300);

  //  display.displayClear();
  //  lastDateShow = millis();

  // ===== WEB SERVER =====
  server.on("/", handleRoot);
  server.on("/settime", handleSetTime);
  server.on("/setalarm", handleSetAlarm);
  server.on("/alarmon", handleAlarmOn);
  server.on("/alarmoff", handleAlarmOff);
  
  server.begin();

  Serial.println("WebServer READY");
}

// ===== LOOP =====

void loop() {
  server.handleClient();
  
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  int curHour = timeinfo.tm_hour;
  int curMinute = timeinfo.tm_min;
  
  if (manualTime) {
    curHour = setHour;
    curMinute = setMinute;
  }
  
  if (alarmEnabled &&
      curHour == alarmHour &&
      curMinute == alarmMinute &&
      !alarmTriggered) {
  
    alarmTriggered = true;
  
    for (int i = 0; i < 5; i++) {
      beep(3000, 300);
      delay(200);
    }
  }

  unsigned long now = millis();

  // ===== BUZZER EVENT =====
//  if (timeinfo.tm_min != lastMinute) {
//    lastMinute = timeinfo.tm_min;
////    beep(2000, 80);           // bunyi tiap menit
//    // jamMelodyCute();
////    playTakeOnMe();
//  }

  if (timeinfo.tm_hour != lastHour) {
    lastHour = timeinfo.tm_hour;
//    beep(2500, 120);          // bunyi jam
//    delay(100);
//    beep(2500, 120);

    playTakeOnMe();
  }

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

      sprintf(dateBuf, "%s %02d %s %04d",
              hari[timeinfo.tm_wday],
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
        // PA_NO_EFFECT,     
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

  server.handleClient();
}
