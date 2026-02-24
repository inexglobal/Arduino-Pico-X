#include <PICOX.h>
void setup() {
  oled.show();delay(2000); // Show logo
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0,0,"wait SW1");
  oled.show();
  waitSW_1();
  oled.clearDisplay();
  oled.show();
  oled.clearDisplay();
  oled.textSize(2);
  oled.text(0,0,"wait SW2");
  oled.show();
  waitSW_2();
  oled.clearDisplay();
  oled.show();
}
void loop() {
  // Servo Motor 1 - 4 
  servo(1,30);
  servo(2,60);
  servo(3,90);
  servo(4,120);
  delay(1000); // Wait 1 Sec.
  // Motor 1 & 2 Forward power 50%
  motor(1, 50);
  motor(2, 50);
  delay(1000);  // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);// Wait 1 Sec.
  // Motor 1 & 2 Forward power 50%
  fd(50);  delay(1000); // Wait 1 Sec.
  // motor Stop
  ao();delay(1000); // Wait 1 Sec.
  // Motor 1 & 2 Backward power 50%
  bk(50);  delay(1000); // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);  // Wait 1 Sec.
  // Motor 1 Backward  2 Forward power 50%
  sl(50); delay(1000);  // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);   // Wait 1 Sec.
  // Motor 1 Forward  2 Backward power 50%
  sr(50);delay(1000);   // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);   // Wait 1 Sec.
  // Motor 1 to 0 and  2 Forward power 50%
  tl(50);delay(1000); // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);   // Wait 1 Sec.
  // Motor 1 Forward power 50% and 2 to 0
  tr(50);delay(1000);   // Wait 1 Sec.
  // motor Stop
  ao();delay(1000);   // Wait 1 Sec.
}
