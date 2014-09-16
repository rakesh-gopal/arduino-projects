/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 
#define BTN_THRESHOLD 900

int colPins[] = {9, 8, 7};
int rowPins[] = {A2, A3, A4, A5};

int outPins[] = {10, 11, 12, 13};

byte buttons[3][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {10, 8, 9, 11}
};

void setup() {
  
  for(int i = 0; i < 3; i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
  
  for(int j = 0; j < 4; j++){
    pinMode(outPins[j], OUTPUT);
    digitalWrite(outPins[j], HIGH);
  }
}

void loop() {
  
  int row = -1, col = -1;
  
  for(int i = 0; i < 3; i++){
    digitalWrite(colPins[i], HIGH);
    delay(20);
    
    for(int j = 0; j < 4; j++){
      if(analogRead(rowPins[j]) > BTN_THRESHOLD){
        row = j;
        col = i;
      }
    }
    
    digitalWrite(colPins[i], LOW);
    
    if(row >= 0 && col >= 0) break;
  }

  if(row >= 0 && col >= 0){
    showBits(buttons[col][row]);
  
    delay(300); 
  }
}


void showBits(byte b){
  for(int i = 0; i < 4; i++){
    byte val = (b & (1 << i))? HIGH : LOW;
    digitalWrite(outPins[i], val);
  }
}


