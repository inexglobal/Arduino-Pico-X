#include <PICOX.h>
void setup() {
}
void loop() {
  for (int  i = 1; i <= 180; i++) {
    // set servo port 1 degree to i
    servo(1, i);
    delay(20);
  }
  for (int  i = 180; i >= 1; i--) {
    // set servo port 1 degree to i
    servo(1, i);
    delay(20);
  }
}
