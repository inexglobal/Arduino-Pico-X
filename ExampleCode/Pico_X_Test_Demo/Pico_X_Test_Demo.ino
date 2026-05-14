#include <PICOX.h>
#include <WiFi.h>
const int led1_Pin = LED_BUILTIN;  //LED1
const int led2_Pin = PIN_LED;      //LED2
int pins[] = { A0, A1, A2, A3, A4, A5, 10, 11, 12, 0, 1 };
void setup() {

  for (int i = 0; i < 11; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
  oled.show();
  delay(2000);  // Show logo
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "wait SW1");
  oled.show();
  waitSW_1();
  oled.clearDisplay();
  oled.show();
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "wait SW2");
  oled.show();
  waitSW_2();
  oled.clearDisplay();
  oled.show();
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "Test Motor");
  oled.show();
  // Servo Motor 1 - 4
  servo(1, 30);
  servo(2, 60);
  servo(3, 90);
  servo(4, 120);
  delay(1000);  // Wait 1 Sec.
  // Motor 1 & 2 Forward power 50%
  motor(1, 50);
  motor(2, 50);
  delay(500);  // Wait 1 Sec.
  // motor Stop
  motor(1, -50);
  motor(2, -50);
  delay(500);  // Wait 1 Sec.
  // motor Stop
  motor(1, 0);
  motor(2, 50);
  delay(500);  // Wait 1 Sec.
  motor(1, 0);
  motor(2, -50);
  delay(500);  // Wait 1 Sec.
    // motor Stop
  motor(1, 50);
  motor(2, 0);
  delay(500);  // Wait 1 Sec.
  // motor Stop
  motor(1, -50);
  motor(2, 0);
  delay(500);  // Wait 1 Sec.
  // motor Stop
  ao();
  delay(500);  // Wait 1 Sec.
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "Test LED");
  oled.show();

  pinMode(led1_Pin, OUTPUT);
  pinMode(led2_Pin, OUTPUT);
  digitalWrite(led1_Pin, HIGH);
  digitalWrite(led2_Pin, LOW);
  delay(500);
  digitalWrite(led1_Pin, LOW);
  digitalWrite(led2_Pin, HIGH);
  delay(500);
  digitalWrite(led1_Pin, HIGH);
  digitalWrite(led2_Pin, LOW);
  delay(500);
  digitalWrite(led1_Pin, LOW);
  digitalWrite(led2_Pin, HIGH);
  delay(500);
  digitalWrite(led1_Pin, LOW);
  digitalWrite(led2_Pin, LOW);

  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "Test Wifi");
  oled.show();
  scan_wifi();
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0, 0, "Test INPUT");
  oled.show();
}
void loop() {

  oled.clearDisplay();
  for (int i = 0; i < 11; i++) {
    if (digitalRead(pins[i]) == 0) {
      oled.text(0, 0, "%d  ", pins[i]);
      oled.show();
    }
  }
}
const char *macToString(uint8_t mac[6]) {
  static char s[20];
  sprintf(s, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return s;
}

const char *encToString(uint8_t enc) {
  switch (enc) {
    case ENC_TYPE_NONE: return "NONE";
    case ENC_TYPE_TKIP: return "WPA";
    case ENC_TYPE_CCMP: return "WPA2";
    case ENC_TYPE_AUTO: return "AUTO";
  }
  return "UNKN";
}
void scan_wifi() {
  delay(5000);
  Serial.printf("Beginning scan at %lu\n", millis());
  auto cnt = WiFi.scanNetworks();
  oled.clearDisplay();
  oled.textSize(1);
  oled.text(0, 0, "scan done");
  oled.show();
  if (!cnt) {
    Serial.printf("No networks found\n");
    oled.clearDisplay();
    oled.textSize(1);
    oled.text(0, 0, "No networks found");
    oled.show();
  } else {
    Serial.printf("Found %d networks\n\n", cnt);
    Serial.printf("%32s %5s %17s %2s %4s\n", "SSID", "ENC", "BSSID        ", "CH", "RSSI");
    for (auto i = 0; i < cnt; i++) {
      uint8_t bssid[6];
      WiFi.BSSID(i, bssid);
      Serial.printf("%32s %5s %17s %2d %4ld\n", WiFi.SSID(i), encToString(WiFi.encryptionType(i)), macToString(bssid), WiFi.channel(i), WiFi.RSSI(i));
      oled.text(i, 0,WiFi.SSID(i));
    }
    oled.show();
  }
  Serial.printf("\n--- Sleeping ---\n\n\n");
  delay(5000);
}
