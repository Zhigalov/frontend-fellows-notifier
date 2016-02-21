const int RED = 10;
const int GREEN = 11;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  delay(10);
  while(Serial.available()) {
    String state = Serial.readString();
    
    if(state == "failed") {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
    } else {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
    }
  }
}



