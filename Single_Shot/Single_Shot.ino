//Pins
#define TriggerSwch 4
#define GateFet 5
#define Firemode_swtch 2  //interrupt pin.
#define Lightgate A0

void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor.
  pinMode(TriggerSwch, INPUT_PULLUP); //Trigger switch input.
  pinMode(GateFet, OUTPUT);       //Mosfet trigger output.
}

void loop() 
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

float readLightgate()
{
  float lightgateV = analogRead(Lightgate) * (5.0 / 1023.0);
  return lightgateV;
}
