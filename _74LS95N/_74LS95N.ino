
#define ds_pin 7
#define clk_pin 6

void setup() {          
  pinMode(ds_pin, OUTPUT);
  pinMode(clk_pin, OUTPUT);
  
  pinMode(13, OUTPUT);     
  digitalWrite(13, HIGH);

  Serial.begin(9600);
}

void loop() {
  for(byte i = 0; i < 0b00001111; i++){
    outToCounter(i);
    delay(800);
  }
}

void outToCounter(byte b){
  
  
  for(byte i = 0 ; i < 4 ; i++){
    int outBit = (b & (1 << i))? HIGH : LOW;
    digitalWrite(ds_pin, outBit);
    delay(80);
    digitalWrite(clk_pin, LOW);
    delay(80);
    Serial.print(outBit);
    digitalWrite(clk_pin, HIGH);
  }
  Serial.println("");
}

