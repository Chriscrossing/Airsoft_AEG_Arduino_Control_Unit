int burst = 3; //Shots per burst
int counter;   //Keeps track of shots


void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(4, INPUT_PULLUP); //Trigger switch input.
  pinMode(5, OUTPUT);       //Mosfet trigger output.
  //Serial.begin(9600);       //Debugging
}

void loop() {
  digitalWrite(5, LOW); //Start with the motor off
  counter = 0; //Start with counter at zero.
  while (digitalRead(4) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(5, HIGH);
    
    int  lightgate = analogRead(A0); //Read the light sensor.
    float lightgateV = lightgate * (5.0 / 1023.0); //Convert to volts.

    //Catch the sector gear after firing a bb.
    //This v range must be fine tuned in order to stop the 
    //motor in the correct position.
    if (lightgateV >= 2 && lightgateV < 2.3) { 
      //Serial.println(lightgateV);
      counter = counter + 1; //Inc counter by 1.
      delay(70); //This just adds a small delay in order for the gears
      //to cach up as the arduino is too fast! 
     }
    if (counter >= burst) {
      digitalWrite(5, LOW); //Motor off
      while(digitalRead(4) == LOW) { //Loop here until trigger is released.
        delay(1);
        }  
    }
  }
}
