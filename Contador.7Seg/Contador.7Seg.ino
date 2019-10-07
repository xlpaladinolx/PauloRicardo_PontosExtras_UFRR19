const int A = 7;
const int B = 6;
const int C = 4;
const int D = 2;
const int E = 1;
const int F = 9;
const int G = 10;
const int l = 1;
const int d = 0;

const int pinContadorMais = 2;
const int pinContadorMenos = 3;
volatile int val7Seg = 0;

byte Display_7Seg[16][7] = {
  { 1, 1, 1, 1, 1, 1, 0 }, // = Digito 0
  { 0, 1, 1, 0, 0, 0, 0 }, // = Digito 1
  { 1, 1, 0, 1, 1, 0, 1 }, // = Digito 2
  { 1, 1, 1, 1, 0, 0, 1 }, // = Digito 3
  { 0, 1, 1, 0, 0, 1, 1 }, // = Digito 4
  { 1, 0, 1, 1, 0, 1, 1 }, // = Digito 5
  { 1, 0, 1, 1, 1, 1, 1 }, // = Digito 6
  { 1, 1, 1, 0, 0, 0, 0 }, // = Digito 7
  { 1, 1, 1, 1, 1, 1, 1 }, // = Digito 8
  { 1, 1, 1, 0, 0, 1, 1 }  // = Digito 9
};

void Print_7Seg(byte digit)  //Funcao que aciona o display
{
  byte pin = 2;  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount)
  {
    digitalWrite(pin, Display_7Seg[digit][segCount]);
    ++pin;
  }
}

void ContadorMais() {
  if ( val7Seg != 9) {
    ++val7Seg;
  }
}

void ContadorMenos() {
  if ( val7Seg != 0) {
    --val7Seg;
  }
}

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(pinContadorMais, INPUT_PULLUP);
  pinMode(pinContadorMenos, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinContadorMais), ContadorMais, RISING);
  attachInterrupt(digitalPinToInterrupt(pinContadorMenos), ContadorMenos, RISING);
}

void loop() {
  Print_7Seg(val7Seg);
}
