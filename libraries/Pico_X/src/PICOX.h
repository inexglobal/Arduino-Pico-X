#include "Wire.h"
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "OLED_I2C_SSD1309.h"
#include "Servo.h"
#define OLED_RESET -1

#define pinTxD 0
#define pinRxD 1

#define pinSDA 4
#define pinSCL 5

#define pinSW1 8
#define pinSW2 9

#define pinD1 10
#define pinD2 11
#define pinD3 12

#define pinM2DIR 13
#define pinM2EN  14

#define pinM1DIR 17
#define pinM1EN  16

#define pinSV1 18
#define pinSV2 19
#define pinSV3 20
#define pinSV4 21

Servo SV1,SV2,SV3,SV4;  // create servo object to control a servo

#define pinA0 40
#define pinA1 41
#define pinA2 42
#define pinA3 43
#define pinA4 44
#define pinA5 45

OLED_I2C_SSD1309 oled(OLED_RESET);

void init(void){
	oled.begin(SSD1309_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  oled.show();
}
// Set init
void init(int _addre){
	oled.begin(SSD1309_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  oled.show();
	oled.clearDisplay();
	oled.show();

}

void servo(uint8_t ch,int angle){
    angle = (angle > 200 ? 200 : angle);
    angle = (angle < -1 ? -1 : angle);

    // ใช้ static bool เพื่อจำว่าเคย attach หรือยัง
    static bool isSV1Attached = false;
    static bool isSV2Attached = false;
    static bool isSV3Attached = false;
    static bool isSV4Attached = false;

    if (ch == 1) {
        if (!isSV1Attached) {
            SV1.attach(pinSV1);
            isSV1Attached = true; // ตั้งค่าเป็น true เพื่อไม่ให้เข้าเงื่อนไขนี้อีก
        }
        SV1.write(angle);
    }else if (ch == 2) {
        if (!isSV2Attached) {
            SV2.attach(pinSV2);
            isSV2Attached = true; // ตั้งค่าเป็น true เพื่อไม่ให้เข้าเงื่อนไขนี้อีก
        }
        SV2.write(angle);
    }else if (ch == 3) {
        if (!isSV3Attached) {
            SV3.attach(pinSV3);
            isSV3Attached = true; // ตั้งค่าเป็น true เพื่อไม่ให้เข้าเงื่อนไขนี้อีก
        }
        SV3.write(angle);
    }else if (ch == 4) {
        if (!isSV4Attached) {
            SV4.attach(pinSV4);
            isSV4Attached = true; // ตั้งค่าเป็น true เพื่อไม่ให้เข้าเงื่อนไขนี้อีก
        }
        SV4.write(angle);
    }
  
}

void motor(int8_t ch, int power,float t=0) {
  static bool isinitIO = false;
  if (!isinitIO) {
        pinMode(pinM1DIR,OUTPUT);
        pinMode(pinM1EN,OUTPUT);
        pinMode(pinM2DIR,OUTPUT);
        pinMode(pinM2EN,OUTPUT);
        isinitIO = true; // ตั้งค่าเป็น true เพื่อไม่ให้เข้าเงื่อนไขนี้อีก
  }
  int _power = constrain(power, -100, 100);
  int pwm = map(_power, -100, 100, -255, 255);
  if (ch == 1) {
    digitalWrite(pinM1DIR,(_power >= 0? LOW : HIGH));
    analogWrite(pinM1EN, abs(pwm));
  } else if (ch == 2) {
    digitalWrite(pinM2DIR,(_power >= 0? LOW : HIGH));
    analogWrite(pinM2EN, abs(pwm));
  }
  delay(t*1000);
}
void motor_stop(int8_t ch,float t=0) {
  analogWrite(pinM1EN, 0);
  analogWrite(pinM2EN, 0);
  delay(t*1000);
}
void ao(void) {
  motor(1, 0);
  motor(2, 0);
}
void fd(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, power);
  motor(2, power);
  delay(t*1000);
 
}
void fd2(int power1,int power2,float t=0) {
  power1 = (power1 > 100 ? 100 : power1);
  power1 = (power1 < 0 ? 0 : power1);
  motor(1,power1);

  power2 = (power2 > 100 ? 100 : power2);
  power2 = (power2 < 0 ? 0 : power2);
  motor(2,power2);
  
  delay(t*1000);

}
void bk(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, -power);
  motor(2, -power);
  delay(t*1000);
}

void bk2(int power1,int power2,float t=0) {
  power1 = (power1 > 100 ? 100 : power1);
  power1 = (power1 < 0 ? 0 : power1);
  motor(1, -power1);

  power2 = (power2 > 100 ? 100 : power2);
  power1 = (power2 < 0 ? 0 : power2);
  motor(2, -power2);
  delay(t*1000);

}

void sl(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, -power);
  motor(2, power);
  delay(t*1000);
}

void sr(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, power);
  motor(2, -power);
  delay(t*1000);
}

void tl(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, 0);
  motor(2, power);
  delay(t*1000);
}

void tr(int power,float t=0) {
  power = (power > 100 ? 100 : power);
  power = (power < 0 ? 0 : power);
  motor(1, power);
  motor(2, 0);
  delay(t*1000);
}

int analog(uint8_t ch){
	return analogRead(ch);
}

int in(uint8_t ch){
	  pinMode(ch,INPUT_PULLUP);
	  return digitalRead(ch);
}

void out(int8_t ch, bool state){
	pinMode(ch,OUTPUT);
	digitalWrite(ch,state);
}
//-------------------------------------------------------------
// End Andlog
//-------------------------------------------------------------

//-------------------------------------------------------------
// Switch A B
//-------------------------------------------------------------

int SW_1(void)
{
  pinMode(pinSW1,INPUT_PULLUP);
  if (digitalRead(pinSW1)==0)
  {
	return(1);
  }
  else
  {
	return(0);
  }
}

void waitSW_1(void)
{
  pinMode(pinSW1,INPUT_PULLUP);
  while(digitalRead(pinSW1));
}

int SW_2(void)
{
  pinMode(pinSW2,INPUT_PULLUP);
  if (digitalRead(pinSW2)==0)
  {
	return(1);
  }
  else
  {
	return(0);
  }
}

void waitSW_2(void)
{
  pinMode(pinSW2,INPUT_PULLUP);
  while(digitalRead(pinSW2));
}
