#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper doorKnob(stepsPerRevolution, 4,5,6,7);


int doorPin = 8; //hallefect
int unlockPin = 9; //rfid signal USSSALY HIGH
int buttonPin = 2; //exit button

int doorReading;
int unlockReading;
int buttonReading;

int doorWait;

void setup() {

  doorKnob.setSpeed(10); //60 rpm

  Serial.begin(9600);
  Serial.print("BOOTING");
  delay(2000);
  Serial.print("DONE");

  pinMode(doorPin, INPUT);
  pinMode(unlockPin, INPUT);
  pinMode(buttonPin, INPUT);
    
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Starting");
  doorReading = digitalRead(doorPin);
  unlockReading = digitalRead(unlockPin);
  buttonReading = digitalRead(buttonPin);

  if(unlockReading == LOW || buttonReading == HIGH) //LOW MEANS REALY IS OPEN 
  {
    if(unlockReading == HIGH)
      Serial.println("PANEL FAULT");
     else
      Serial.println("BUTTON FAULT"); 
    
    Serial.print("Unlock Sequence");
    
    //do servo opening stuff
    doorKnob.step(50);

    Serial.print("Door Unlocked");

    delay(3000);
    Serial.print("Waiting for Door Closure");

    doorWait = 0;
    while(doorWait == 0)
    {
      doorReading = digitalRead(doorPin);
      delay(500);
      if(doorReading == HIGH) // that means the door has closed
      {
        delay(1000); //wait one sec
        
        Serial.print("Door Closing");
        //do servo closing stuff
        doorKnob.step(-50);
        
        Serial.print("Door Closed");
        doorWait = 1; //break out of loop
      }
    }
    doorWait = 0;
    Serial.print("Done");
  }

  Serial.print("Restarting...");
  delay(500);
  
}
