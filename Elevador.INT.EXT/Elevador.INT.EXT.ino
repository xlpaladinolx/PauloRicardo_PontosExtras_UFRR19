
#include <Servo.h>

const int pinTerreo = 3;
const int pin1Andar = 4;
const int pin2Andar = 5;

const int valTerreo = 0;
const int valAndar1 = 90;
const int valAndar2 = 180;
Servo servo_9;

void Terreo() {
  servo_9.write(valTerreo);
}

void Andar1() {
  servo_9.write(valAndar1);
}

void Andar2() {
  servo_9.write(valAndar2);
}

void setup()
{
  servo_9.attach(9);
  pinMode(pinTerreo, INPUT_PULLUP);
  pinMode(pin1Andar, INPUT_PULLUP);
  pinMode(pin2Andar, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinTerreo), Terreo, RISING);
  attachInterrupt(digitalPinToInterrupt(pin1Andar), Andar1, RISING);
  attachInterrupt(digitalPinToInterrupt(pin2Andar), Andar2, RISING);
  servo_9.write(Terreo);
}

void loop()
{

}
