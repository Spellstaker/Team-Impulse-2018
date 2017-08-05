#include <Servo.h>

class ServoExtended : public Servo{
  private:
    const int max = 180, min = 0; // max and min degrees of servo
    int deg = 0; // stores current degree of servo
    bool mode = true; // true for smooth, false for staggered
    int step_size = 0, step_time = 0; // step size and delay time for staggered mode

    /************************************************
      Helper Functions
    ************************************************/

    void smooth(int new_deg) {
      Serial.println("Moving Smoothly");
      deg = new_deg;
      write(deg);
    }

    void staggered(int new_deg) {
      for (int dir = deg < new_deg ? 1 : -1; dir * (new_deg - deg) > 0; delay(step_time)) {
        write(deg);
        deg += dir * step_size;
      }
      deg = new_deg;
      write(deg);
    }

    void move(int new_deg) {
      if (new_deg > max) new_deg = min + (new_deg % (max - min));
      if (new_deg < min) new_deg = min;
      if (mode) smooth(new_deg);
      else staggered(new_deg);
      Serial.print("Moved to: "); Serial.println(deg);
    }

    void get_step_data() {
      step_size = Serial.parseInt();
      step_time = Serial.parseInt();
      Serial.print("Step Size: "); Serial.println(step_size);
      Serial.print("Step time: "); Serial.println(step_time);
    }

  public:

    /************************************************
      Task functions
    ************************************************/
    
    // Sets servo at max
    void set() {
      move(max);
    }
    // Sets servo at min
    void reset() {
      move(min);
    }
    // Sets Servo at halfway point between max and min
    void halfset() {
      move((max + min) / 2);
    }
    // Displays the degree servo is at
    void absolute_degree() {
      Serial.print("At degree: "); Serial.println(deg);
    }


    // Moves servo anti clockwise by 'move_to' degrees
    void ac_relative(int move_to) {
      move(deg - move_to);
    }
    // Moves servo clockwise by 'move_to' degrees
    void c_relative(int move_to) {
      move(deg + move_to);
    }
    // Moves servo anti clockwise by degrees recieved from Serial
    void ac_relative() {
      int move_to = Serial.parseInt();
      ac_relative(move_to);
    }
    // Moves servo clockwise by degrees recieved from Serial
    void c_relative() {
      int move_to = Serial.parseInt();
      c_relative(move_to);
    }

    void set_mode_smooth() {
      mode = true;
      Serial.println("Mode switched to smooth");
    }

    void set_mode_staggered() {
      mode = false;
      Serial.println("Mode switched to staggered");
      get_step_data();
    }
};