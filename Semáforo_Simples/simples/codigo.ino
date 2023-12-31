
#define PIN_RED     8
#define PIN_YELLOW  13
#define PIN_GREEN   7

#define YELLOW_TO_RED 1000
#define RED_TO_GREEN 10000 
#define GREEN_TO_YELLOW 10000

short unsigned int light = 1;

void setup() {
  pinMode(PIN_RED,OUTPUT);
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_YELLOW,OUTPUT);
  digitalWrite(PIN_YELLOW,HIGH);
}

void loop() {

  switch(light)
  {
    case 0:
      delay(GREEN_TO_YELLOW);
      digitalWrite(PIN_GREEN,LOW);
      digitalWrite(PIN_YELLOW,HIGH);
      light++;
      break;
    case 1:
      delay(YELLOW_TO_RED);
      digitalWrite(PIN_YELLOW,LOW);
      digitalWrite(PIN_RED,HIGH);
      light++;
      break;
    case 2:
      delay(RED_TO_GREEN);
      digitalWrite(PIN_RED,LOW);
      digitalWrite(PIN_GREEN,HIGH);
      light = 0;
      break;
    default:
      light = 1;
  }
}
