/*
 * Line Follower main class: 
 *  - setup of the robot 
 *  - main loop
 *  - button handler
 */
 
#include "Arduino.h"
#include "Config.h"
#include <Servo.h>
#include "Enums.h"
#include "Robot.h"

#define MIN_PULSE  500
#define MAX_PULSE 2500

#define SPEED 200
#define TURN_SPEED 40

Robot robot;

int lastButtonPressTime;

Enums::State start_state;


void setup() {

  Serial.begin(115200);         
  
  //  button setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(BUTTON_PIN), onButtonPressed, FALLING);
  lastButtonPressTime = 0;
  
  //  led setup
  pinMode(LED_PIN, OUTPUT);

  //  robot setup
  robot.setMotors(MIN_PULSE, MAX_PULSE, SPEED, TURN_SPEED);
  robot.setState(Enums::BeforeStart);

  /*Serial.print(digitalRead(A0));
  Serial.print(digitalRead(A1));
  Serial.print(digitalRead(A2));
  Serial.print(digitalRead(A3));
  Serial.println(digitalRead(A4));
  delay(1000);*/
}


void loop() {

  Enums::State state = robot.getState();

  switch (state) {
    
    case Enums::Running:
      robot.followTheLine();
      return;
    
    case Enums::BeforeStart:
      //robot.stopMotors();
      return;
      
    default:
      // never
      return;
  }
}


// button press handler (using interrupt)
void onButtonPressed() {

  //robot.flash();
  
  int currentTime = millis();
  if ((currentTime - lastButtonPressTime) < 1000)
    return;

  //robot.flash();
  lastButtonPressTime = currentTime;

  switch (robot.getState()) {
    
    case Enums::BeforeStart:
      robot.setState(Enums::Running);
      return;
    
    case Enums::Running:
      robot.stopMotors();
      robot.setState(Enums::BeforeStart);
      robot.flash();
      return;
      
    default:
      // never
      return;
  }
}
