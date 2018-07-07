//Pins
#define TriggerSwch 4
#define GateFet 5
#define Firemode_swtch 2  //interrupt pin.
#define Lightgate A0


//Variables
int firemode = 0;
int burst;
int counter = 0;   //Keeps track of shots.
bool inPeak = false; //Peak tracking

void setup() {
  //configure switch pins as an input and enable the internal pull-up resistor.
  pinMode(TriggerSwch, INPUT_PULLUP); //Trigger switch input.
  pinMode(GateFet, OUTPUT);       //Mosfet trigger output.

  pinMode(Firemode_swtch, INPUT_PULLUP); //Firemode Switch input.
  //attachInterrupt(digitalPinToInterrupt(Firemode_swtch), readfireselector, CHANGE);
}

void loop() 
{
  while (readfireselector() == HIGH)
  {
    semi_auto();
  }

  while (readfireselector() == LOW)
  {
    three_shot_burst();
  }
  
}

float readLightgate()
{
  float lightgateV = analogRead(Lightgate) * (5.0 / 1023.0);
  return lightgateV;
}

bool readfireselector()
{
  firemode = digitalRead(Firemode_swtch);
  return firemode;
}

void semi_auto()
{
  digitalWrite(GateFet, LOW); //Start with the motor off

  while (digitalRead(TriggerSwch) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(GateFet, HIGH);

    //Catch the sector gear after firing a bb.
    if (readLightgate() > 3.76) {   
        digitalWrite(GateFet, LOW);       //Motor off imidiatly.
        while(digitalRead(TriggerSwch) == LOW) //Loop here until trigger is released.
        {  
          delay(1);
        }
     }
  }
}

void three_shot_burst()
{
  burst = 3; //Shots per burst.
  inPeak = false; //reset to false.
  counter = 0; //Reset to zero.
  
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

void full_auto()
{
  digitalWrite(GateFet, LOW); //Start with the motor off
  
  while (digitalRead(TriggerSwch) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(GateFet, HIGH);
   }     
  
  //Stop the motor at the next lightgate pulse.
  while (readLightgate() < 3.76)
  {
    delay(0.1);
  }
  digitalWrite(GateFet, LOW); //Stop the motor.
}




