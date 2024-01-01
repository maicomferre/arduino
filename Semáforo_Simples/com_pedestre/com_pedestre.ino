/*
 * Simples Sistema de Semáforo com controlador para pedestres e time para o tempo que falta para o vermelho ficar verde
 * Utilizando um: Display de 7 segmentos, algumas protoboard, um arduino Uno, um buzzer e algumas LEDS
 * Controle Noturno, Com um sensor fotoeletrico o o semáforo é desligado durante a "noite" e fica em amarelo piscante
 * @By Maicom Ferreira;]
 * 01/jan/2024
 */



#define PIN_RED                8
#define PIN_YELLOW            13
#define PIN_GREEN             11
#define PIN_GREEN_PEDESTRIAN  12
#define PIN_RED_PEDESTRIAN     9

#define YELLOW_TO_RED 1000
#define RED_TO_GREEN 10000 
#define GREEN_TO_YELLOW 15000
#define SENSOR_LIGHT A0

#define BUZZER_PIN 10

short unsigned int light = 1;
int timemap = 0;


byte tabela_7_seg [16] = {   
B01111110,  // = Digito 0   
B00001100,  // = Digito 1   
B10110110,  // = Digito 2   
B10011110,  // = Digito 3   
B11001100,  // = Digito 4   
B11011010,  // = Digito 5   
B11111010,  // = Digito 6   
B00001110,  // = Digito 7   
B11111110,  // = Digito 8   
B11001110,  // = Digito 9   
B11101110,  // = Digito A   
B11111000,  // = Digito B   
B01110010,  // = Digito C   
B10111100,  // = Digito D   
B11110010,  // = Digito E   
B11100010   // = Digito F

};

int sensor = 1000;

void setup() {
  /*
    Semáforo com segundo para pedestre
  
  */

  Serial.begin(9600);
  
  DDRD = B11111110;
  pinMode(SENSOR_LIGHT, INPUT);
  
  pinMode(PIN_RED,OUTPUT);
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_YELLOW,OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(PIN_YELLOW,HIGH);

  pinMode(PIN_GREEN_PEDESTRIAN, OUTPUT);
  pinMode(PIN_RED_PEDESTRIAN, OUTPUT);
}

void loop() {

  sensor = ((sensor * 10) + (analogRead(SENSOR_LIGHT) * 5)) / 15;

  Serial.println(sensor);
  if(sensor < 10)
  {
    digitalWrite(PIN_YELLOW, digitalRead(PIN_YELLOW) == HIGH ? LOW : HIGH);
    digitalWrite(PIN_GREEN,LOW);
    digitalWrite(PIN_RED,LOW);
    digitalWrite(PIN_RED_PEDESTRIAN, LOW);
    digitalWrite(PIN_GREEN_PEDESTRIAN, LOW);
    PORTD = B00000000;
    delay(500);
    light = 1;
    return;
  }

  switch(light)
  {
    case 0:
      digitalWrite(PIN_RED_PEDESTRIAN, HIGH);
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
      digitalWrite(PIN_RED_PEDESTRIAN, LOW);
      timemap = RED_TO_GREEN;
      light++;
      break;
    case 2:
      if(timemap > 0)
      {
        if( timemap < (RED_TO_GREEN + 1000) / 2)
        {
          digitalWrite(PIN_GREEN_PEDESTRIAN, LOW);
          digitalWrite(PIN_RED_PEDESTRIAN, digitalRead(PIN_RED_PEDESTRIAN) == HIGH ? LOW : HIGH);
          digitalWrite(BUZZER_PIN, digitalRead(BUZZER_PIN) == HIGH ? LOW : HIGH);
        }
        delay(1000);
        
        timemap -= 1000;
      }
      else
      {
        digitalWrite(PIN_RED,LOW);
        digitalWrite(PIN_GREEN,HIGH);
        digitalWrite(BUZZER_PIN, LOW);
        light = 0;
      }
      break;
    default:
      light = 1;
  }
  if(timemap / 1000 > 0 )
   PORTD = tabela_7_seg[timemap / 1000];
  else
    PORTD = B00000000;
}
