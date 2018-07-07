bool inPeak = false; //Peak tracking


void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(4, INPUT_PULLUP); //Trigger switch input.
  pinMode(5, OUTPUT);       //Mosfet trigger output.
  //Serial.begin(9600);       //Debugging
}

void loop() {
  digitalWrite(5, LOW); //Start with the motor off
  while (digitalRead(4) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(5, HIGH);
   }     
  while (inPeak != true) 
  {
    //Stop the motor at the next lightgate pulse.
    inPeak = full_auto_completion();
  }
  digitalWrite(5, LOW); //Start with the motor off
}


float readLightgate()
{
  float lightgateV = analogRead(A0) * (5.0 / 1023.0);
  return lightgateV;
}

bool full_auto_completion() 
{
  if (readLightgate() > 3.76) //3.76V from the lightsensor.
  { 
    if (!inPeak) {
      inPeak = true;
    }
  }
  else 
    {
      inPeak = false;
    }
    return inPeak; 
}
