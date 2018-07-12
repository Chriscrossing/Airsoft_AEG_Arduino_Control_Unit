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
  Serial.begin(9600);
  //configure switch pins as an input and enable the internal pull-up resistor.
  pinMode(TriggerSwch, INPUT_PULLUP); //Trigger switch input.
  pinMode(GateFet, OUTPUT);       //Mosfet trigger output.

  pinMode(Firemode_swtch, INPUT_PULLUP); //Firemode Switch input.
  //attachInterrupt(digitalPinToInterrupt(Firemode_swtch), readfireselector, CHANGE);
}

void loop() 
{
  if (readfireselector() == HIGH)
  {
    while (digitalRead(TriggerSwch) == LOW) 
    {
      Serial.println("Single-Shot");
    }
  }

  if (readfireselector() == LOW)
  {
    while (digitalRead(TriggerSwch) == LOW) 
    {
      Serial.println("Full-Auto");
    }
  }
  
}

bool readfireselector()
{
  firemode = digitalRead(Firemode_swtch);
  return firemode;
}
