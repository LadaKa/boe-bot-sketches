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

  /* behaviour */

  // state Running:
  // follow the black line
  void followTheLine() {

    if (sensors.isMiddleOnBlack()) {
      // on the line
      control.move(Enums::Forward);
      return;
    }

    stopMotors();
    return;  // TODO: remove this

    // outside the line
    Enums::Direction last_inner_sensor_side;
    if (sensors.isLeftInnerOnBlack()) {
      last_inner_sensor_side = Enums::Left;
    } else {
      last_inner_sensor_side = Enums::Right;
    }

    while (!sensors.isMiddleOnBlack()) {
      control.moveInOppositeDirection(last_inner_sensor_side);
      if (sensors.isLeftInnerOnBlack()) {
        last_inner_sensor_side = Enums::Left;
      } else {
        last_inner_sensor_side = Enums::Right;
      }
    }
  }


  // state BeforeStart:
  // stop
  void stopMotors() {
    control.stop();
  }

  void testSensors() {
    sensors.printSensors();
  }

  /* utils */

  // flash the LED
  void flash() {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
};

#endif #
