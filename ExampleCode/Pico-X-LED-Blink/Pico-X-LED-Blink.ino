const int led1_Pin = LED_BUILTIN; //LED1
const int led2_Pin = PIN_LED;     //LED2
void setup() {
  pinMode(led1_Pin, OUTPUT);
  pinMode(led2_Pin, OUTPUT);
}
void loop() {
  digitalWrite(led1_Pin, HIGH);
  digitalWrite(led2_Pin, LOW);
  delay(500);
  digitalWrite(led1_Pin, LOW);
  digitalWrite(led2_Pin, HIGH);
  delay(500);
}
