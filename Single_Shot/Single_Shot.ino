void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP); //Trigger switch input.
  pinMode(3, OUTPUT);       //Mosfet trigger output.
  Serial.begin(9600);
}

void loop() {
  digitalWrite(3, LOW); //Start with the motor off

  while (digitalRead(2) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(3, HIGH);
    
    int  lightgate = analogRead(A0); //Read the lightsensor.
    float lightgateV = lightgate * (5.0 / 1023.0);

    if (lightgateV > 3.3 && lightgateV < 3.6) {         //Catch the sector gear after firing a bb.
        digitalWrite(3, LOW);       //Motor off/
        //Serial.println("Shot");
        //Serial.println(lightgateV);
        while(digitalRead(2) == LOW) {    //Loop here until trigger is released.
          delay(1);
        }
     }
  }
}
