#include "ServoExtended.h"

ServoExtended testservo;
void setup() {
  Serial.begin(9600);
  testservo.attach(9);
  testservo.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    int set = Serial.read();
    switch (set) {
      case 's': // Sets servo at max
        testservo.set();
        break;
      case 'r': // Sets servo at min
        testservo.reset();
        break;
      case 'h': // Sets servo at halfpoint between min and max
        testservo.halfset();
        break;
      case 'd': // Outputs the current degree the servo is at
        testservo.absolute_degree();
        break;
      case 'a': // Rotates anticlosckwise
        testservo.ac_relative();
        break;
      case 'c': // Rotates clockwise
        testservo.c_relative();
        break;
      case '1': // mode 1 corresponds to smooth mode
        testservo.set_mode_smooth();
        break;
      case '2': // mode 2 corresponds to staggered mode
        testservo.set_mode_staggered();
        break;
    }
  }
}
