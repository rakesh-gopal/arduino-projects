

#define door_open_led_pin 12
#define door_close_led_pin 13

#define motor_pin1 11
#define motor_pin2 10

#define num_pass_led 4
int pass_led_pins[] = {4, 3, 2, 1};


void setup()  { 

  for( int i = 0; i < num_pass_led; i++ ){
    pinMode(pass_led_pins[i], OUTPUT);
  }
  pinMode(door_open_led_pin, OUTPUT);
  pinMode(door_close_led_pin, OUTPUT);
  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);

  digitalWrite(door_close_led_pin, HIGH);
}

void loop()  { 

  for( int i = 0; i < num_pass_led; i++){
    delay(700);
    digitalWrite(pass_led_pins[i], HIGH);
  }

  for(int i = 0; i < 2; i++){
    digitalWrite(door_open_led_pin, LOW);
    delay(400);
    digitalWrite(door_open_led_pin, HIGH);
    delay(400);
  }
  
  for( int i = 0; i < num_pass_led; i++){
    digitalWrite(pass_led_pins[i], LOW);
  }  

  digitalWrite(door_open_led_pin, HIGH);
  digitalWrite(door_close_led_pin, LOW);

  analogWrite(motor_pin1, 0);
  analogWrite(motor_pin2, 255);
  delay(250);
  analogWrite(motor_pin2, 0);

  delay(3000);

  for(int i = 0; i < 5; i++){
    digitalWrite(door_close_led_pin, LOW);
    delay(400);
    digitalWrite(door_close_led_pin, HIGH);
    delay(400);
  }
  delay(500);

  digitalWrite(door_open_led_pin, LOW);

  analogWrite(motor_pin1, 255);
  analogWrite(motor_pin2, 0);
  delay(250);
  analogWrite(motor_pin1, 0);

  delay(3000);
}

