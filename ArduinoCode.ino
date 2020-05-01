#include <Servo.h>
#define Dir 12
#define Step 11
#define Taster 10 

#define LED1 1
#define LED2 2

String input;
int steps;
int LEDindex;
int AktuelleSteps;
Servo Motor;
void setup() {
Serial.begin(9600);
pinMode(Dir, OUTPUT);
pinMode(Step, OUTPUT);
Motor.attach(9);
pinMode(Taster, INPUT);

pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);

input = "";
steps = 0;
LEDindex = 0;
AktuelleSteps = 0;
}

void loop() {
  while(Serial.available() == 0);
  input = Serial.readString();
  InputVerarbeiten(input);

}

void Turn (int Steps) {
    if (AktuelleSteps >= Steps) {
        int Steps_to_make = AktuelleSteps - Steps;
        digitalWrite(Dir, LOW);
        for (int i=0; i<Steps_to_make; i++) {
          digitalWrite(Step, HIGH);
          delayMicroseconds(500);
          digitalWrite(Step, LOW);
          delayMicroseconds(500);
        } AktuelleSteps = Steps;
      } else if (AktuelleSteps < Steps) {
        int Steps_to_make = Steps - AktuelleSteps;
        digitalWrite(Dir, LOW);
        for (int i=0; i<Steps_to_make; i++) {
          digitalWrite(Step, HIGH);
          delayMicroseconds(500);
          digitalWrite(Step, LOW);
          delayMicroseconds(500);
        } AktuelleSteps = Steps;
      }
  
}

void InputVerarbeiten(String data) {
  if (data.startsWith("#")) {
    data.remove(0,1);
    steps = data.toInt();
  } else if (data.startsWith("-")) {
    data.remove(0,1);
    LEDindex = data.toInt();
  } else if (data == "start") {
    LedWireOff();
    Turn(steps);
    LedWireOn(LEDindex);
  } else if (data.startsWith("!")) {
    data.remove(0,1);
    int degree = data.toInt();
    steps = degree / 360 *3200;
    LedWireOff();
    Turn(steps);
  } else if (data == "setZero") {
    setNull();
  }
}

void LedWireOn (int Index) {
    switch(Index) {
      case 1:
      digitalWrite(LED1, HIGH);
      break;
      case 2:
      digitalWrite(LED2, HIGH);
      break;
    }
}
void LedWireOff () {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void setNull () {
    Motor.write(180);
    while(digitalRead(Taster) != HIGH) {
       digitalWrite(Step, HIGH);
       delayMicroseconds(500);
       digitalWrite(Step, LOW);
       delayMicroseconds(500);
    }AktuelleSteps = 0;
      Motor.write(0);
}
