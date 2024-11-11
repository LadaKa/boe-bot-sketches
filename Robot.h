#ifndef Robot_h
#define Robot_h

#include "Control.h"
#include "Sensors.h"
#include "Enums.h"
#include "Config.h"

/* Robot following the black line (when in "Running" state) */
class Robot

{
private:
  Control control;
  Sensors sensors;

  Enums::State state;  // {BeforeStart, Running}

public:

  Robot(){};

  /* basic setup */

  void setMotors(
    int minPulse, int maxPulse, int speed, int turn_speed) {
    control.setMotors(L_WHEEL_PIN, R_WHEEL_PIN, minPulse, maxPulse);
    control.setSpeed(speed, turn_speed);
  }

  void setState(Enums::State s) {
    state = s;
  }

  Enums::State getState() {
    return state;
  }

  /* behavior */

  // state Running:
  // follow the black line
  void followTheLine() {

    if (sensors.isMiddleOnBlack()) {
      // on the line
      control.move(Enums::Forward);
      return;
    }

    // outside the line
    if (sensors.isLeftInnerOnBlack()) {
      control.move(Enums::Left);
     // control.rotateLeft();
    } else if (sensors.isRightInnerOnBlack()) {
      control.move(Enums::Right);
      //control.rotateRight();
    } else {
      control.stop();
      rotateUntilOnLine();
    }
  }

  // recovery rotation (outside the line)
  void rotateUntilOnLine() {
    flash();
    while (!sensors.isMiddleOnBlack()) {
      if (sensors.isLeftInnerOnBlack()) {
        control.rotateLeft();
        delay(300);
      } else {
        control.rotateRight();
        delay(300);
      }
    }
  }

  // state BeforeStart:
  // stop
  void stopMotors() {
    control.stop();
  }



  /* utils */

  // flash the LED
  void flash() {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  void testSensors() {
    sensors.printSensors();
  }
};

#endif #
