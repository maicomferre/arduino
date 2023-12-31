
#define PIN_RED     8
#define PIN_YELLOW  13
#define PIN_GREEN   7
#define PIN_GREEN_PEDESTRIAN 12
#define PIN_RED_PEDESTRIAN 13

#define YELLOW_TO_RED 1000
#define RED_TO_GREEN 10000 
#define GREEN_TO_YELLOW 15000

short unsigned int light = 1;
int timemap = 0;

void setup() {
  /*
    Semáforo com segundo para pedestre
  
  */
  pinMode(PIN_RED,OUTPUT);
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_YELLOW,OUTPUT);
  pinMode(PIN_PEDESTRIAN, OUTPUT);
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
      digitalWrite(PIN_GREEN_PEDESTRIAN, HIGH);
      timemap = RED_TO_GREEN;
      light++;
      break;
    case 2:
      if(timemap > 0)
      {
        if( timemap < RED_TO_GREEN / 2)
        {
          
        }
        delay(1000);
        
        digitalWrite(PIN_PEDESTRIAN, digitalRead(PIN_PEDESTRIAN) == HIGH ? LOW : HIGH);
        timemap -= 1000;
      }
      else
      {
        digitalWrite(PIN_RED,LOW);
        digitalWrite(PIN_GREEN,HIGH);
        light = 0;
      }
      break;
    default:
      light = 1;
  }
}
