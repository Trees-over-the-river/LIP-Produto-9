#include <SoftwareSerial.h>


//ASENSOR = Sensor analógico
//BUTTON = Botão
//LED = LED com saída analógica

#define ASENSOR A0
#define LED A1
#define BUTTON 2


SoftwareSerial serial(3, 4);
int analog = 0;
bool button = false;
bool state = true;
int buff = 0;




void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(ASENSOR, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  serial.begin(1000);
}


void loop() {
  if (serial.available()>0) {
    buff = serial.read();
    analogWrite(LED, (buff & 0xfe) * (buff & 1));
  }
  
  
  analog = analogRead(ASENSOR);
  if (digitalRead(BUTTON) != button) {
  	button = !button;
    state = (button == HIGH)? !state : state;
  };
  
  digitalWrite(LED_BUILTIN, state);
  
  serial.write(((analog >> 2) & 0xfe) + state);
  
  delay(100);
}

