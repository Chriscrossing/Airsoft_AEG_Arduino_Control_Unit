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

int swt_time = 0;
bool second_firemode = false;

void setup() {
  Serial.begin(9600);
  //configure switch pins as an input and enable the internal pull-up resistor.
  pinMode(TriggerSwch, INPUT_PULLUP); //Trigger switch input.
  pinMode(GateFet, OUTPUT);       //Mosfet trigger output.

  pinMode(Firemode_swtch, INPUT_PULLUP); //Firemode Switch input.
  //attachInterrupt(digitalPinToInterrupt(Firemode_swtch), readfireselector, CHANGE);
}

void loop() 
{
  //Serial.println(second_firemode);
  if (readfireselector() == HIGH)
  {
    semi_auto();
  }

  if (readfireselector() == LOW)
  {
    if (second_firemode == 0) 
    {
      three_shot_burst();
    } 
    else if (second_firemode == 1)
    {
      full_auto();
    }
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
  
  if (digitalRead(TriggerSwch) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(GateFet, HIGH);
    swt_time = 0;
    //Catch the sector gear after firing a bb.
    if (readLightgate() > 3.76) 
    {   
        digitalWrite(GateFet, LOW);       //Motor off imidiatly.
        //swt_time = 0;
        while(digitalRead(TriggerSwch) == LOW) //Loop here until trigger is released.
        {  
          swt_time = swt_time + 1;
          delay(1);
        }
    }
    if (swt_time >= 1000) //if held down for 5s switch 2nd firemode.
    {
      if (second_firemode == 1)
      {
        second_firemode = 0;
      }
      else if (second_firemode == 0)
      {
        second_firemode = 1;
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
          if (!inPeak) 
          {
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
  //while (readLightgate() < 3.76)
  //{
  //  delay(0.1);
  //}
  digitalWrite(GateFet, LOW); //Stop the motor.
}




