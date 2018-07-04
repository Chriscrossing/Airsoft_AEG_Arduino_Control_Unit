//Options
int burst = 3; //Shots per burst
int counter;   //Keeps track of shots

//Periferals
const int Trigger = 4;
const int FetTriggger = 5;
const int SensorPin = A0;


void setup() {
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(Trigger, INPUT_PULLUP); //Trigger switch input.
  pinMode(FetTriggger, OUTPUT);       //Mosfet trigger output.
  //Serial.begin(9600);       //Debugging
}

void loop() {
  digitalWrite(FetTriggger, LOW); //Start with the motor off
  counter = 0; //Start with counter at zero.
  
  while (digitalRead(Trigger) == LOW) {   //While button is pressed turn on the motor.
    digitalWrite(FetTriggger, HIGH);
    
    int  lightgate = analogRead(SensorPin); //Read the light sensor.
    float lightgateV = lightgate * (5.0 / 1023.0); //Convert to volts.

    //Catch the sector gear after firing a bb.
    //This v range must be fine tuned in order to stop the 
    //motor in the correct position.
    if (lightgateV >= 3.3 && lightgateV < 4.5) { 
      //Serial.println(lightgateV);
      counter = counter + 1; //Inc counter by 1.
      //This just adds a small delay in order for the gears
      //to cach up as the arduino is too fast!
      delay(70);  
     }
    if (counter >= burst) {
      digitalWrite(FetTriggger, LOW); //Motor off
      while(digitalRead(Trigger) == LOW) { //Loop here until trigger is released.
        delay(1);
        }  
    }
  }
}
