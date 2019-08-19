/*
   Título: Demostração de uma Máquina de Estado
   Autor: Paulo Ricardo Dutra Ribeiro da Silva
   Data: 19/08/2019

   Demonstrates the use a 16x2 LCD display

    The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K resistor:
     ends to +5V and ground
     wiper to LCD VO pin (pin 3)
*/
#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------
const int pinAlarme = 8;
const int pinTrava = 9;
const int LEDTravaVERDE = A0;
const int LEDTravaVERMELHO = A1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//-------------------------------------------------------------------------------
enum State {Locked, Unlocked};
//enum Event {Pass, Coin};
//-------------------------------------------------------------------------------
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//-------------------------------------------------------------------------------

void Unlock() {

  static State s;
  digitalWrite(LEDTravaVERMELHO, LOW);
  digitalWrite(LEDTravaVERDE, HIGH);
  digitalWrite(pinTrava, HIGH);
  s = Unlocked;
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Unlocked");

}

void Lock() {

  static State s;
  digitalWrite(LEDTravaVERDE, LOW);
  digitalWrite(LEDTravaVERMELHO, HIGH);
  digitalWrite(pinTrava, LOW);
  s = Locked;
  lcd.clear();
  lcd.setCursor(0, 4);
  lcd.print("Locked");

}

void Thankyou() {

  lcd.setCursor(1, 2);
  lcd.print("Thank You !");
  delay(3000);
  lcd.setCursor(1, 2);
  lcd.print("           ");

}

void Alarm() {

  lcd.setCursor(1, 0);
  lcd.print("Alarme Disparado");
  for (int i = 0; i <= 3; i++) {
    digitalWrite(pinAlarme, HIGH);
    digitalWrite(LEDTravaVERMELHO, HIGH);
    delay(1000);
    digitalWrite(pinAlarme, LOW);
    digitalWrite(LEDTravaVERMELHO, LOW);
    delay(1000);
  }
  lcd.setCursor(1, 0);
  lcd.print("                ");

}

void Transition(int e) {

  static State s;
  switch (s) {
    case Locked:
      switch (e) {
        case 0:
          s = Unlocked;
          Unlock();
          break;
        case 1:
          Alarm();
          break;
      }
    case Unlocked:
      switch (e) {
        case 0:
          Thankyou();
          break;
        case 1:
          s = Locked;
          Lock();
          break;
      }
      break;
  }

}

String leStringSerial() {
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while (Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n') {
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }

  return conteudo;
}

void setup() {
  //-------------------------------------------------------------------------------
  pinMode(pinAlarme, OUTPUT);
  pinMode(pinTrava, OUTPUT);
  pinMode(LEDTravaVERDE, OUTPUT);
  pinMode(LEDTravaVERMELHO, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  static State s;
  //-------------------------------------------------------------------------------
  digitalWrite(LEDTravaVERDE, HIGH);
  digitalWrite(pinTrava, LOW);
  s = Locked;
  lcd.setCursor(0, 4);
  lcd.print("Locked");
  digitalWrite(LEDTravaVERMELHO, HIGH);
  Lock();

}

void loop() {
int e;
  if (Serial.available() > 0) {
    // Lê toda string recebida
    String recebido = leStringSerial();

    if (recebido == "Coin" && "COIN" && "coin") {
    	e = 0;
      Transition(e);
    }

    if (recebido == "Pass" && "PASS" && "pass") {
    	e = 1;
      Transition(e);
    } else {
      Serial.print("Valor Inválido");
    }
  }
}
