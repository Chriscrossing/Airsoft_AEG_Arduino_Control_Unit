int burst = 3;
int counter;
float const threshold = 4.55;


void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP); //Trigger switch input.
  pinMode(3, OUTPUT);       //Mosfet trigger output.
  Serial.begin(9600);
}

void loop() {
  digitalWrite(3, LOW); //Start with the motor off
  counter = 0;
  while (digitalRead(2) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(3, HIGH);
    
    int  lightgate = analogRead(A0); //Read the lightsensor.
    float lightgateV = lightgate * (5.0 / 1023.0);

    if (lightgateV >= 2.5 && lightgateV < 2.7) {         //Catch the sector gear after firing a bb.
      Serial.println(lightgateV);
      counter = counter + 1;
     }
    if (counter >= burst) {
      digitalWrite(3, LOW);       //Motor off/
      counter = 0;
      while(digitalRead(2) == LOW) {    //Loop here until trigger is released.
        delay(1);
        }  
    }
  }
}
