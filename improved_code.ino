#include <AccelStepper.h>   //libary to control the stepper motors

//SENSE
int sense = A0;     //senser PIN allocation 
int senseVal = 0;    //sensing variable to calculate the differensial
int CurrentVal = senseVal;  // inital value for LDR value

//LEDs
int ledr = 12;    //red LED pin
int ledg = 13;    //green LED pin

//STEPPER
AccelStepper stepper(AccelStepper::FULL4WIRE,4,5,6,7);    //blade
AccelStepper stepper2(AccelStepper::FULL4WIRE,8,9,10,11);    //claw


void setup()
    
{ 
  Serial.begin(9600);   creating a serial link for debugging
  
  stepper2.setMaxSpeed(2000.0);   
  stepper2.setAcceleration(1000.0);
  stepper.setMaxSpeed(300.0);
  stepper.setAcceleration(300.0);
  

  pinMode(ledr, LOW);   // initialize the digital pin to set the starting LED colours
  pinMode(ledg, 180);
}

void loop()
{

  int CurrentVal = senseVal;      //logs the previous value from the sensor to compare to the new value
  Serial.println("Current Vall is.."); 
  Serial.println(CurrentVal);
  senseVal = analogRead(sense);   //reads senseor value 
  Serial.println(senseVal);  //print value for debugging
  delay(200);

    if (CurrentVal - senseVal >= 20)   //if egg present, by checking the difference in light levels, begin cutting sequence
  {Serial.println("Cutting");

  
  analogWrite(ledr, 180);   //change LEDs to red on
  analogWrite(ledg, LOW);
  delay(1500);

    stepper.runToNewPosition(95);     // closing the claw onto the egg to hold it in position

  
    delay(1000);
    stepper2.runToNewPosition(115);   //instucting blade to cut the egg
    
    delay(10);
    stepper2.runToNewPosition(0);      //returning the blade to the origin
        delay(10);
    stepper2.runToNewPosition(115);   //2nd stroke of the blade
    
    delay(10);
    stepper2.runToNewPosition(0);
     stepper2.runToNewPosition(115);   //3rd stoke of the blade
    
    delay(10);
    stepper2.runToNewPosition(0);         //returning the blade to the origin
    delay(1000);

    
    delay(1000);
    stepper.runToNewPosition(0);      //removing claw from egg so it can be removed

     
    digitalWrite(ledr, LOW);      //returning LEDs to the original configuration as opperation finished
    digitalWrite(ledg, 180);
    delay(5000);
  
}
  else
  {
   digitalWrite(ledr, LOW);     //if no egg sensed, LED remains red and continues to wait for an egg
  digitalWrite(ledg, 180);
  Serial.println("waiting");
  }
}
