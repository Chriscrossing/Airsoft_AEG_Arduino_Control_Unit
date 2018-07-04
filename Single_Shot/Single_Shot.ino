void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor.
  pinMode(4, INPUT_PULLUP); //Trigger switch input.
  pinMode(5, OUTPUT);       //Mosfet trigger output.
  Serial.begin(9600);       //Debugging.
}

void loop() {
  digitalWrite(5, LOW); //Start with the motor off

  while (digitalRead(4) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(5, HIGH);
    
    int  lightgate = analogRead(A0); //Monitor the light sensor.
    float lightgateV = lightgate * (5.0 / 1023.0); //Convert to volts.

    //Catch the sector gear after firing a bb.
    if (lightgateV > 3.3 && lightgateV < 4.5) {   
        digitalWrite(5, LOW);       //Motor off imidiatly.
        Serial.println("Shot");   //Debugging
        Serial.println(lightgateV);
        while(digitalRead(4) == LOW) {  //Loop here until trigger is released.
          delay(1);
        }
     }
  }
}
