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

  int leftSpeedDegree = 0;
  int rightSpeedDegree = 0;

public:

  Robot(){
  };

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

    if (sensors.isLeftInnerOnBlack()){
      if (leftSpeedDegree < SPEED_DEGREE_MAX){
        leftSpeedDegree++;
        control.turnLeft(leftSpeedDegree);
      }
    } 
    else if (sensors.isRightInnerOnBlack()) {
      if (rightSpeedDegree < SPEED_DEGREE_MAX){
        rightSpeedDegree++;
        control.turnRight(rightSpeedDegree);
      }
    } 
    else if (sensors.isMiddleOnBlack()) {
      // on the line
      leftSpeedDegree=0;
      rightSpeedDegree=0;
      control.move(Enums::Forward);
    }
    else {
      
      // TODO: spiral
      //control.stop();
      //rotateUntilOnLine();
    }



  }

  // TODO: spiral
  // recovery rotation (outside the line)
  void rotateUntilOnLine() {
    flash();
    while (!sensors.isMiddleOnBlack()) {
      if (sensors.isLeftInnerOnBlack()) {
        control.rotateLeft();
        delay(300);
      } 
      else {
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


