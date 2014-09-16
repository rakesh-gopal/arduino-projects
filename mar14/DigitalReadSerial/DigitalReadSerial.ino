/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 
#define ledPin 0
boolean ledOn = true;

void setup() {
  pinMode(2, INPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(ledPin, HIGH);
}

void loop() {
  int sensorValue = digitalRead(2);
  
  if(sensorValue){
    ledOn = !ledOn;
    if(ledOn)
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
      
    do{
      delay(50);
    } while(digitalRead(2));
  }
  
  delay(50);
}



