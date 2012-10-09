
#include <SoftwareSerial.h>
#define rxPin 17
#define txPin 16

SoftwareSerial mySerial = SoftwareSerial(rxPin,txPin);

void setup() {
  digitalWrite(txPin,HIGH);
  delay(1000);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  mySerial.begin(9600);
  delay(1000);
}

void loop() {
  mySerial.write(0xFE);
  mySerial.write(128);
  delay(10);
  mySerial.print("HI VITORIA");
  mySerial.write(0xFE);
  mySerial.write(192);
  delay(10);
  mySerial.print("HI RAFAEL");
  while(1);
}
