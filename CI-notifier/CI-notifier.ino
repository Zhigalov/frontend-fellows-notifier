const int RED = 9;
const int GREEN = 10;
const int BLUE = 11;

int stateRed = 0;
int stateGreen = 0;
int stateBlue = 0;
boolean stateBlink = false;

int multiplier = 0;
int multiplierDirection = 1;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  delay(2);

  while(Serial.available()) {
    String state = Serial.readString();

    if(state == "failed") {
      changeState(1, 0, 0, true);
    } else if (state == "passed") {
      changeState(0, 1, 0, false);
    } else {
      changeState(0, 0, 1, true);
    }
  }

  multiplier += multiplierDirection;
  if (multiplier > 254 || multiplier < 1) {
    multiplierDirection *= -1;
  }

  LED();
}

void changeState(int red, int green, int blue, boolean isBlink) {
  stateRed = red;
  stateGreen = green;
  stateBlue = blue;
  stateBlink = isBlink;
}

void LED() {
  int defaultValue = stateBlink ? 0 : 255;
  analogWrite(RED, stateRed * max (defaultValue, multiplier));
  analogWrite(GREEN, stateGreen * max (defaultValue, multiplier));
  analogWrite(BLUE, stateBlue * max (defaultValue, multiplier));
}

