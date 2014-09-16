

#define door_open_led_pin 12
#define door_close_led_pin 13

#define motor_pin1 11
#define motor_pin2 10

#define num_pass_led 4
int pass_led_pins[] = {5, 4, 3, 2};

#define BTN_THRESHOLD 900

int colPins[] = {7, 8, 9};
int rowPins[] = {A2, A3, A4, A5};

int buttons[3][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {10, 8, 9, 11}
};


void setup()  { 

  for( int i = 0; i < num_pass_led; i++ ){
    pinMode(pass_led_pins[i], OUTPUT);
  }
  pinMode(door_open_led_pin, OUTPUT);
  pinMode(door_close_led_pin, OUTPUT);
  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);
  
  for(int i = 0; i < 3; i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  digitalWrite(door_close_led_pin, HIGH);
}

#define passLen 4
static int passCode[] = {7, 6, 5, 4};
int enteredCode[4] = {0};
int cur = 0;

void loop()  { 
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
    // Button pressed    
    int n = buttons[col][row];
    
    if( cur < passLen ){
      enteredCode[cur] = n;
      
      if(cur < num_pass_led)
        //writeNum(n);
        digitalWrite(pass_led_pins[cur], HIGH);
        
      cur++;
    } 
    
    if( cur >= passLen){
     
      boolean isCodeValid = true;
      
      for(int i = 0; i < passLen; i++)
        if( enteredCode[i] != passCode[i] ){
          isCodeValid = false;
          break;
        }
      
      if( isCodeValid ){
        openDoor();
        delay(4000);
        closeDoor();
      }

      delay(500);
      
      for( int i = 0; i < num_pass_led; i++){
        digitalWrite(pass_led_pins[i], LOW);
      }
      cur = 0;
    }
  
    do{
      delay(300);
    } while(analogRead(rowPins[row]) > BTN_THRESHOLD);
  }
}

void writeNum(int n){
  for(int i = 0; i < 4; i++){
    int b = (n & 1<<i)? HIGH : LOW;
    digitalWrite(pass_led_pins[i], b);
  }
}

#define motor_volt 180

void openDoor(){
  digitalWrite(door_open_led_pin, HIGH);
  digitalWrite(door_close_led_pin, LOW);
  
  analogWrite(motor_pin1, 0);
  analogWrite(motor_pin2, motor_volt);
  delay(1000);
  analogWrite(motor_pin2, 0);
}

void closeDoor(){
  for(int i = 0; i < 5; i++){
    digitalWrite(door_close_led_pin, LOW);
    delay(400);
    digitalWrite(door_close_led_pin, HIGH);
    delay(400);
  }

  digitalWrite(door_open_led_pin, LOW);
  delay(500);

  analogWrite(motor_pin1, motor_volt);
  analogWrite(motor_pin2, 0);
  delay(1000);
  analogWrite(motor_pin1, 0);
}

