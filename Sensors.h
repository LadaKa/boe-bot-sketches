#ifndef Sensors_h
#define Sensors_h

#include "Config.h"

#define BLACK LOW
#define WHITE HIGH

/*_    Front IR sensors:

    [L_OUTER]  [L_INNER][MIDDLE][R_INNER]  [R_OUTER]

*/
class Sensors
{
  public:

    bool isMiddleOnBlack()
    {
      return readSensor(SENSOR_MIDDLE);
    }

    bool isLeftInnerOnBlack()
    {
      return readSensor(SENSOR_L_INNER);
    }

    bool isRightInnerOnBlack()
    {
      return readSensor(SENSOR_R_INNER);
    }

    void printSensors()
    {
      Serial.print(isLeftInnerOnBlack());
      Serial.print(isMiddleOnBlack());
      Serial.println(isRightInnerOnBlack());
    }

  private:

    bool readSensor(int pin)
    {
      return digitalRead(pin) == BLACK; 
    }

    

};
#endif
