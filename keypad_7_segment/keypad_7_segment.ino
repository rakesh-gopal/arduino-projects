
#define BTN_THRESHOLD 900

int colPins[] = {13, 12, 11};
int rowPins[] = {2, 3, 4, 5};

int buttons[3][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {10, 8, 9, 11}
};
 
//                    Arduino pin: 2,3,4,5,6,7,8
byte seven_seg_digits[12][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 },   // = 9
                                 { 0,0,1,0,1,1,0 },  // = 10
                                 { 0,1,1,0,1,1,0 },  // = 11
                           };
                           

void setup() {               
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  for(int i = 0; i < 3; i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  int row = -1, col = -1;
  int btnVal = 0;
  
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
    sevenSegWrite(buttons[col][row]);
  
    do{
      delay(300);
    } while(analogRead(rowPins[row]) > BTN_THRESHOLD);
  }
}
