#include "ServoExtended.h"

ServoExtended testservo;
void setup() {
  Serial.begin(9600);
  testservo.attach(9);
  testservo.set();
}

void loop() {
  // to do: generalize interepreter
  if (Serial.available() > 0) {
    String head = Serial.readStringUntil(' ');
    if (head == "Servo") {
      String command = Serial.readStringUntil(' ');
      if (command == "set;") testservo.set();
      else if (command == "halfset;") testservo.halfset();
      else if (command == "reset;") testservo.reset();
      else if (command == "absolute_degree;") testservo.absolute_degree();
      
      else if (command == "ac") {
        int relative_degree = Serial.readStringUntil(';').toInt();
        testservo.ac_relative(relative_degree);
      }
      
      else if (command == "c") {
        int relative_degree = Serial.readStringUntil(';').toInt();
        testservo.c_relative(relative_degree);
      }
      else if (command == "mode") {
        String mode = Serial.readStringUntil(' ');
        if (mode == "smooth;") testservo.set_mode_smooth();
        if (mode == "staggered") {
          int step_size = Serial.readStringUntil(' ').toInt();
          int step_time = Serial.readStringUntil(';').toInt();
          testservo.set_mode_staggered(step_size, step_time);
        }
      }
    }
  }
}
