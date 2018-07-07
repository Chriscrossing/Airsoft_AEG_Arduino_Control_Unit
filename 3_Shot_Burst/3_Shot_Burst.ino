//Pins
#define TriggerSwch 4
#define GateFet 5
#define Firemode_swtch 2  //interrupt pin.
#define Lightgate A0

//Options
burst = 3; //Shots per burst.
inPeak = false; //reset to false.
counter = 0; //Reset to zero.

void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(TriggerSwch, INPUT_PULLUP); //Trigger switch input.
  pinMode(GateFet, OUTPUT);       //Mosfet trigger output.
}

void loop() 
{
  digitalWrite(GateFet, LOW); //Start with the motor off 

  //When the trigger is pulled, fire 3 shots.
  if (digitalRead(TriggerSwch) == LOW) {   
    digitalWrite(GateFet, HIGH);

    //Loop while counter is less than the burst no.
    //Make sure to only count one lightgate pulse 
    //per shot.
    while(counter != burst) {
      if (readLightgate() > 3.76) 
      { 
          if (!inPeak) {
            counter ++;
            inPeak = true;
          }
      }
      else 
      {
        inPeak = false;
      }
    }   
    
    //Motor off
    digitalWrite(GateFet, LOW); 
    
    //Wait here until trigger is released.
    while(digitalRead(TriggerSwch) == LOW) { 
      delay(1);
    }  
  }
}
