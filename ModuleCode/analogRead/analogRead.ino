#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
int A;
int B;
int C;
int S1_0 = 0;
int S1_1 = 1;
int S1_2 = 2;
int S1_3 = 3;
int S2_0 = 4;
int S2_1 = 5;
int S2_2 = 6;
int S2_3 = 7;
int S3_0 = 8;
int S3_1 = 9;
int S3_2 = 10;
int S3_3 = 11;
int LED_OUT = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("I've Setup!");
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  LED_OUT = 0;
  
  A = analogRead(0);
  B = analogRead(1);
  C = analogRead(2);
  Serial.println(A);
  if (A < 700) {
    mySerial.write(S1_0);
  }
  else if (A < 850) {
    mySerial.write(1);
    LED_OUT = LED_OUT + 1;
  }
  else if (A < 910) {
    mySerial.write(2);
    LED_OUT = LED_OUT + 2;
  }
  else if (A < 960) {
    mySerial.write(3);
    LED_OUT = LED_OUT + 3;
  }
  if (B < 700) {
    mySerial.write(4);
  }
  else if (B < 850) {
    mySerial.write(5);
    LED_OUT = LED_OUT + 1;
  }
  else if (B < 910) {
    mySerial.write(6);
    LED_OUT = LED_OUT + 2;
  }
  else if (B < 960) {
    mySerial.write(7);
    LED_OUT = LED_OUT + 3;
  }
  if (C < 700) {
    mySerial.write(8);
  }
  else if (C < 850) {
    mySerial.write(9);
    LED_OUT = LED_OUT + 1;
  }
  else if (C < 910) {
    mySerial.write(10);
    LED_OUT = LED_OUT + 2;
  }
  else if (C < 960) {
    mySerial.write(11);
    LED_OUT = LED_OUT + 3;
  }
  if (LED_OUT == 1) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  else if (LED_OUT == 2) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  else if (LED_OUT == 3) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  else if (LED_OUT == 4) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  else if (LED_OUT == 5) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
}
