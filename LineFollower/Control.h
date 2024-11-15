#ifndef Control_h
#define Control_h

#include "Motor.h"

/*  Control of robot left and right motors:
    movement forward and turning (rotation or pivot turn)
*/

class Control     
{
  public:

    Enums::Direction lastDirection = Enums::Forward;
    
    Control()
    {};

    void setMotors(int leftPin, int rightPin, int minPulse, int maxPulse)
    {
      centerPulse = (minPulse + maxPulse) / 2;

      _leftMotor.attach(leftPin, minPulse, maxPulse);
      _leftMotor.setCenterPulseAndDirection(centerPulse, false);

      _rightMotor.attach(rightPin, minPulse, maxPulse);
      _rightMotor.setCenterPulseAndDirection(centerPulse, true);

      stop();
    }

    void setSpeed(int speedParam, int turnSpeed)
    {
      speed = speedParam;
      rotationSpeed = turnSpeed;
      insideTurnSpeed = turnSpeed/2;
      outsideTurnSpeed = turnSpeed;
    }

    void move(Enums::Direction direction) {
      lastDirection = direction;
      switch (direction) {
        case Enums::Forward:
          moveForward();
          break;
        case Enums::Left:
          turnLeft();   // pivot turn
          break;
        case Enums::Right:
          turnRight();  // pivot turn
          break;
        default:
          break;
      }
    }

    void turnLeft(int turnSpeed)
    {
      _leftMotor.go(insideTurnSpeed);
      _rightMotor.go(outsideTurnSpeed + turnSpeed);
    }
    
    void turnRight(int turnSpeed)
    {
      _rightMotor.go(insideTurnSpeed);
      _leftMotor.go(outsideTurnSpeed + turnSpeed);
    }

    void rotateLeft()
    {
      _leftMotor.go( -rotationSpeed);
      _rightMotor.go( rotationSpeed);
    }

    void rotateRight()
    {
      _leftMotor.go(  rotationSpeed);
      _rightMotor.go(-rotationSpeed);
    }


    void stop()
    {
      _leftMotor.stop();
      _rightMotor.stop();
    }

  private:

    void moveForward()
    {
      _leftMotor.go(speed);
      _rightMotor.go(speed);
    }

    void turnLeft()
    {
      //_leftMotor.go(insideTurnSpeed);
      _leftMotor.stop();
      _rightMotor.go(outsideTurnSpeed);
    }
    
    void turnRight()
    {
      _rightMotor.stop();
      _leftMotor.go(outsideTurnSpeed);
      
      //_rightMotor.go(insideTurnSpeed);
    }
    

    int speed;
    int rotationSpeed;         
    int insideTurnSpeed;
    int outsideTurnSpeed;
    int centerPulse;
    Motor _leftMotor, _rightMotor;

    
};

#endif
