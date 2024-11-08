/*
 * Line Follower main class: 
 *  - setup of the robot 
 *  - main loop
 *  - button handler
 */
 
#include "Arduino.h"
#include <Servo.h>
#include "Enums.h"
#include "Robot.h"

#define BUTTON_PIN 2

#define LED_PIN 11

#define L_WHEEL_PIN 12
#define R_WHEEL_PIN 13

#define MIN_PULSE  500
#define MAX_PULSE 2500

#define SPEED 200
#define TURN_SPEED 40

Robot robot;

int lastButtonPressTime;

Enums::State start_state;


void setup() {

  Serial.begin(11960);         
  
  //  button setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
 // attachInterrupt(
 //   digitalPinToInterrupt(BUTTON_PIN), onButtonPressed, FALLING);
  lastButtonPressTime = 0;
  
  //  led setup
  pinMode(LED_PIN, OUTPUT);

  //  robot setup
  robot.setMotorsAndSpeed(
    L_WHEEL_PIN, R_WHEEL_PIN, MIN_PULSE, MAX_PULSE, SPEED, TURN_SPEED);
  robot.setState(Enums::BeforeStart);
}


void loop() {

  Enums::State state = robot.getState();
  
  switch (state) {
    
    case Enums::Running:
      robot.followTheLine();
      return;
    
    case Enums::BeforeStart:
      return;
      
    default:
      // never
      return;
  }
}


// button press handler (using interrupt)
void onButtonPressed() {
  
  int currentTime = millis();
  if ((currentTime - lastButtonPressTime) < 1000)
    return;

  robot.flash();
  lastButtonPressTime = currentTime;
  
  switch (robot.getState()) {
    
    case Enums::BeforeStart:
      robot.setState(Enums::Running);
      return;
    
    case Enums::Running:
      robot.setState(Enums::BeforeStart);
      return;
      
    default:
      // never
      return;
  }
}
