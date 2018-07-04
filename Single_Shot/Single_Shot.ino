const int Trigger = 4;
const int FetTriggger = 5;
const int SensorPin = A0;

void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor.
  pinMode(Trigger, INPUT_PULLUP); //Trigger switch input.
  pinMode(FetTrigger, OUTPUT);       //Mosfet trigger output.
  //Serial.begin(9600);       //Debugging.
}

void loop() {
  digitalWrite(FetTrigger, LOW); //Start with the motor off

  while (digitalRead(Trigger) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(FetTrigger, HIGH);
    
    int  lightgate = analogRead(SensorPin); //Monitor the light sensor.
    float lightgateV = lightgate * (5.0 / 1023.0); //Convert to volts.

    //Catch the sector gear after firing a bb.
    if (lightgateV > 3.3 && lightgateV < 4.5) {   
        digitalWrite(FetTrigger, LOW);       //Motor off imidiatly.
        //Serial.println("Shot");   //Debugging
        //Serial.println(lightgateV);
        while(digitalRead(Trigger) == LOW) {  //Loop here until trigger is released.
          delay(1);
        }
     }
  }
}
