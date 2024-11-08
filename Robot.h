#ifndef Robot_h
#define Robot_h

#include "Control.h"
#include "Sensors.h"
#include "Enums.h"
#define LED 11

/* Robot following the black line (when in "Running" state) */
class Robot

{
  private:
    Control control;
    Sensors sensors;

    Enums::State state; // {BeforeStart, Running}

  public:

    Robot() {};

    /* basic setup */

    void setMotorsAndSpeed(
      int leftPin, int rightPin,
      int minPulse, int maxPulse,
      int speed, int turn_speed) {
      control.setMotors(leftPin, rightPin, minPulse, maxPulse);
      control.setSpeed(speed, turn_speed);
    }

    void setState(Enums::State s)
    {
      state = s;
    }  
        
    Enums::State getState()
    {
      return state;
    }
    
    /* behaviour */

    // state Running:
    // follow the black line
    void followTheLine() {

      if (sensors.getMiddle())
        {
          // on the line
          control.move(Enums::Forward);
          return;
        }
     
      // outside the line
      Enums::Direction last_inner_sensor_side;
          if (sensors.getLeftInnerValue()){
            last_inner_sensor_side = Enums::Left;
          }
          else {
            last_inner_sensor_side = Enums::Right;
          }
          
          while (!sensors.getMiddle()){
            control.moveInOppositeDirection(last_inner_sensor_side);
            if (sensors.getLeftInnerValue()){
              last_inner_sensor_side = Enums::Left;
            }
            else {
              last_inner_sensor_side = Enums::Right;
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
    void flash(){
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
    }

};

#endif#
