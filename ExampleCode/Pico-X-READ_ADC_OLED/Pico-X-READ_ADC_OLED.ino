#include <PICOX.h>
int adc_pin = A0 ; 
void setup() {
  oled.clearDisplay();
  oled.textSize(2);
}
void loop() {
  int adc = analogRead(adc_pin);
  oled.text(0,2,"Read A0");
  oled.text(2,0,"Raw:%d   ",adc);
  oled.text(3,0,"Volt:%f   ",adc*3.3/1023);
  oled.show();
}