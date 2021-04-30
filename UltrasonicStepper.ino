//note: this will only work on teensy boards below 3.6, 4.x boards will not work.
//libraries
#include "TeensyStep.h"
#include <NewPing.h>

//defining stepper motor pins, change this based on what works for you
Stepper motor_1(6, 7);
Stepper motor_2(8, 9);

//defining the type of stepper controller as a rotate controller
RotateControl controller;

//defining newping trig pin, echo pin, and max distance
NewPing sonar(3, 4, 1000);

void setup()
{
  //serial begin
  Serial.begin(115200);
  
  // defining motor peramiters
  motor_1
  .setMaxSpeed(6000)       
  .setAcceleration(200000); 

  motor_2
  .setMaxSpeed(-6000)       
  .setAcceleration(200000); 
}
void loop()
{
  //read the ultrasonic sensor
                       
  unsigned int uS = sonar.ping(); 
  Serial.print("Ping: ");
  Serial.print(sonar.convert_in(uS)); 
  Serial.println("in");
  int distance = sonar.convert_in(uS);
  
  //check to see if distance is less than greater than 10
  while (distance >= 10){
    motor_2.setMaxSpeed(-6000);
    controller.rotateAsync(motor_1, motor_2);
    break;
  }
  //check to see if distance is less than 10
  while (distance <= 10){
    motor_2.setMaxSpeed(6000);
    controller.rotateAsync(motor_1, motor_2);
    break;
  }
}
